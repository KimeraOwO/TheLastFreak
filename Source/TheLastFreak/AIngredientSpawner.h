// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectTypes.h"
#include "AIngredientSpawner.generated.h"

class UBoxComponent;
class AIngredient;

UCLASS()
class THELASTFREAK_API AIngredientSpawner : public AActor
{
    GENERATED_BODY()

public:
    AIngredientSpawner();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UBoxComponent* SpawnVolume;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Config")
    EItemType IngredientToSpawn;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Config")
    TSubclassOf<AIngredient> IngredientClass;

    UPROPERTY()
    TArray<AIngredient*> ActiveIngredients;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner Config")
    float SpawnRadius;

public:
    UFUNCTION(BlueprintCallable, Category = "Spawner")
    void SpawnSingleIngredient();

    UFUNCTION(BlueprintCallable, Category = "Spawner")
    void CheckAndReplenish();

    FTimerHandle ReplenishTimerHandle;
};