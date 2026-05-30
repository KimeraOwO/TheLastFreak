// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AMainGameMode.generated.h"

class ACustomerNPC;

UCLASS()
class THELASTFREAK_API AMainGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMainGameMode();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Flow")
    TSubclassOf<ACustomerNPC> CustomerClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Flow")
    FVector CustomerSpawnLocation;

public:
    UFUNCTION(BlueprintCallable, Category = "Game Flow")
    void SpawnNewCustomer();
};