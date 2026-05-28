// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AWorkStationBase.h"
#include "AAssemblyTable.generated.h"

UCLASS()
class THELASTFREAK_API AAssemblyTable : public AWorkStationBase
{
    GENERATED_BODY()

public:
    AAssemblyTable();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadOnly, Category = "Assembly State")
    bool bHasTomato;

    UPROPERTY(BlueprintReadOnly, Category = "Assembly State")
    bool bHasLettuce;

    UPROPERTY(BlueprintReadOnly, Category = "Assembly State")
    bool bHasMeat;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assembly Config")
    TSubclassOf<AIngredient> BurgerClass;

    FTimerHandle BurgerDeliveryTimerHandle;

public:
    virtual void Interact(AChefCharacter* Chef) override;

    void ResetTable();

    void ClearAssembledBurger();
};