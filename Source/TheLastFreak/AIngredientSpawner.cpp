// Fill out your copyright notice in the Description page of Project Settings.

#include "AIngredientSpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "AIngredient.h"

AIngredientSpawner::AIngredientSpawner()
{
    PrimaryActorTick.bCanEverTick = false;

    SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
    RootComponent = SpawnVolume;
    SpawnVolume->SetCollisionProfileName(TEXT("NoCollision"));

    IngredientToSpawn = EItemType::Tomato;
    SpawnRadius = 120.f;
}

void AIngredientSpawner::BeginPlay()
{
    Super::BeginPlay();

    for (int32 i = 0; i < 3; i++)
    {
        SpawnSingleIngredient();
    }

    GetWorld()->GetTimerManager().SetTimer(ReplenishTimerHandle, this, &AIngredientSpawner::CheckAndReplenish, 1.0f, true);
}

void AIngredientSpawner::SpawnSingleIngredient()
{
    if (!GetWorld() || !IngredientClass) return;

    FVector SpawnerLocation = GetActorLocation();
    FVector RandomOffset = UKismetMathLibrary::RandomPointInBoundingBox(SpawnerLocation, FVector(SpawnRadius, SpawnRadius, 0.f));
    RandomOffset.Z = SpawnerLocation.Z + 10.f;

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;

    AIngredient* NewItem = GetWorld()->SpawnActor<AIngredient>(IngredientClass, RandomOffset, FRotator::ZeroRotator, SpawnParams);

    if (NewItem)
    {
        FIngredientData FreshData;
        FreshData.ItemType = IngredientToSpawn;
        FreshData.ItemState = EItemState::Raw;
        NewItem->SetIngredientData(FreshData);

        ActiveIngredients.Add(NewItem);
    }
}

void AIngredientSpawner::CheckAndReplenish()
{
    for (int32 i = ActiveIngredients.Num() - 1; i >= 0; --i)
    {
        if (!ActiveIngredients[i] || !ActiveIngredients[i]->IsValidLowLevel() || ActiveIngredients[i]->GetAttachParentActor() != nullptr)
        {
            ActiveIngredients.RemoveAt(i);
        }
    }

    if (ActiveIngredients.Num() < 3)
    {
        SpawnSingleIngredient();
    }
}