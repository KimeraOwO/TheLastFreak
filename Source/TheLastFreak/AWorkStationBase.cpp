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

}