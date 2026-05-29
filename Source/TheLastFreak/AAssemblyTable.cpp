#include "AAssemblyTable.h"
#include "AIngredient.h"
#include "AChefCharacter.h"
#include "NiagaraComponent.h"
#include "Components/StaticMeshComponent.h"

AAssemblyTable::AAssemblyTable()
{
    StationType = EStationType::AssemblyTable;
    ResetTable();
}

void AAssemblyTable::BeginPlay()
{
    Super::BeginPlay();
}

void AAssemblyTable::Interact(AChefCharacter* Chef)
{
    if (!Chef || bIsProcessing) return;

    if (CurrentIngredient && CurrentIngredient->GetIngredientData().ItemType == EItemType::Burger)
    {
        return;
    }

    if (Chef->IsHoldingItem())
    {
        AIngredient* HeldItem = Chef->GetCurrentHeldIngredient();
        if (!HeldItem) return;

        FIngredientData Data = HeldItem->GetIngredientData();

        if (Data.ItemState != EItemState::Processed) return;

        bool bItemAccepted = false;

        if (Data.ItemType == EItemType::Tomato && !bHasTomato)
        {
            bHasTomato = true;
            bItemAccepted = true;
        }
        else if (Data.ItemType == EItemType::Meat && !bHasMeat)
        {
            bHasMeat = true;
            bItemAccepted = true;
        }

        if (bItemAccepted)
        {
            Chef->ReleaseItemToStation();
            HeldItem->Destroy();

            if (bHasTomato && bHasMeat)
            {
                bIsProcessing = true;

                if (StationVFX)
                {
                    StationVFX->Activate();
                }

                StartProcessing();

                if (GetWorld() && BurgerClass)
                {
                    FActorSpawnParameters SpawnParams;
                    SpawnParams.Owner = this;
                    SpawnParams.Instigator = GetInstigator();

                    FVector SpawnLocation = ItemPlacementPoint ? ItemPlacementPoint->GetComponentLocation() : GetActorLocation();
                    FRotator SpawnRotation = GetActorRotation();

                    CurrentIngredient = GetWorld()->SpawnActor<AIngredient>(BurgerClass, SpawnLocation, SpawnRotation, SpawnParams);

                    if (CurrentIngredient)
                    {
                        CurrentIngredient->AttachToComponent(ItemPlacementPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

                        UStaticMeshComponent* BurgerMesh = Cast<UStaticMeshComponent>(CurrentIngredient->GetRootComponent());
                        if (BurgerMesh)
                        {
                            BurgerMesh->SetSimulatePhysics(false);
                            BurgerMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
                        }
                    }
                }

                bIsProcessing = false;
                FinishProcessing();
            }
        }
    }
}

void AAssemblyTable::ClearAssembledBurger()
{
    if (CurrentIngredient)
    {
        CurrentIngredient->Destroy();
        CurrentIngredient = nullptr;
    }
    ResetTable();
}

void AAssemblyTable::ResetTable()
{
    bHasTomato = false;
    bHasLettuce = false;
    bHasMeat = false;
    bIsProcessing = false;
}