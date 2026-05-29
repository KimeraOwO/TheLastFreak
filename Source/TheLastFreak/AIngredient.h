// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectTypes.h"
#include "AIngredient.generated.h"

class UStaticMeshComponent;

UCLASS()
class THELASTFREAK_API AIngredient : public AActor
{
    GENERATED_BODY()

public:
    AIngredient();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* MeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ingredient Properties", meta = (AllowPrivateAccess = "true"))
    FIngredientData IngredientData;

public:
    UFUNCTION(BlueprintCallable, Category = "Ingredient")
    FIngredientData GetIngredientData() const { return IngredientData; }

    UFUNCTION(BlueprintCallable, Category = "Ingredient")
    void SetIngredientData(FIngredientData NewData) { IngredientData = NewData; }

    UFUNCTION(BlueprintCallable, Category = "Ingredient")
    void SetIngredientState(EItemState NewState) { IngredientData.ItemState = NewState; }

    UFUNCTION(BlueprintCallable, Category = "Ingredient")
    void UpdateVisualMesh(UStaticMesh* NewMesh);
};