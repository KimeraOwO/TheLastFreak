// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <GameFramework/Character.h>
#include "ACustomerNPC.generated.h"

UCLASS()
class THELASTFREAK_API ACustomerNPC : public ACharacter
{
    GENERATED_BODY()

public:
    ACustomerNPC();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customer Config")
    float MaxPatienceTime;

    FTimerHandle PatienceTimerHandle;

    FVector ExitLocation;

public:
    void OnPatienceTimeout();

    UFUNCTION(BlueprintCallable, Category = "Customer Actions")
    void ReceiveOrder();

    void LeaveRestaurant();
};