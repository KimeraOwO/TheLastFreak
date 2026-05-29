#include "AWorkStationBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "NiagaraComponent.h" 
#include "AIngredient.h"
#include "AChefCharacter.h"

AWorkStationBase::AWorkStationBase()
{
    PrimaryActorTick.bCanEverTick = false;

    StationMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StationMesh"));
    RootComponent = StationMesh;

    ItemPlacementPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ItemPlacementPoint"));
    ItemPlacementPoint->SetupAttachment(RootComponent);

    StationVFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("StationVFX"));
    StationVFX->SetupAttachment(RootComponent);
    StationVFX->bAutoActivate = false;

    StationType = EStationType::None;
    CurrentIngredient = nullptr;
    bIsProcessing = false;
}

void AWorkStationBase::BeginPlay()
{
    Super::BeginPlay();
}

void AWorkStationBase::Interact(AChefCharacter* Chef)
{
    if (!Chef) return;

    if (HasItem() && !Chef->IsHoldingItem() && !bIsProcessing)
    {
        Chef->SetCurrentHeldIngredient(CurrentIngredient);

        if (Chef->GetCurrentHeldIngredient())
        {
            UStaticMeshComponent* IngredientMesh = Cast<UStaticMeshComponent>(Chef->GetCurrentHeldIngredient()->GetRootComponent());
            if (IngredientMesh)
            {
                IngredientMesh->SetSimulatePhysics(false);
                IngredientMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            }

            Chef->GetCurrentHeldIngredient()->AttachToComponent(
                Chef->GetHoldingPoint(),
                FAttachmentTransformRules::SnapToTargetNotIncludingScale
            );
        }

        CurrentIngredient = nullptr;
        return;
    }

    if (!HasItem() && Chef->IsHoldingItem())
    {
        CurrentIngredient = Chef->GetCurrentHeldIngredient();

        if (CurrentIngredient)
        {
            Chef->ReleaseItemToStation();

            UStaticMeshComponent* IngredientMesh = Cast<UStaticMeshComponent>(CurrentIngredient->GetRootComponent());
            if (IngredientMesh)
            {
                IngredientMesh->SetSimulatePhysics(false);
                IngredientMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            }

            CurrentIngredient->AttachToComponent(ItemPlacementPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

            switch (StationType)
            {
            case EStationType::CuttingBoard:
            case EStationType::Oven:
            {
                bIsProcessing = true;

                if (StationVFX)
                {
                    StationVFX->Activate();
                }

                StartProcessing();
            }
            break;

            default:
                break;
            }
        }
        return;
    }
}