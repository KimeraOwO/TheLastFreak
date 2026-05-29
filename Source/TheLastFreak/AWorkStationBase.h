#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectTypes.h"
#include "AWorkStationBase.generated.h"

class UStaticMeshComponent;
class USceneComponent;
class UNiagaraComponent;
class AIngredient;
class AChefCharacter;

UCLASS()
class THELASTFREAK_API AWorkStationBase : public AActor
{
    GENERATED_BODY()

public:
    AWorkStationBase();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* StationMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USceneComponent* ItemPlacementPoint;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UNiagaraComponent* StationVFX;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Station Properties")
    TSubclassOf<AIngredient> ProcessedIngredientClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Station Config")
    EStationType StationType;

    UPROPERTY(BlueprintReadWrite, Category = "Station State")
    AIngredient* CurrentIngredient;

    UPROPERTY(BlueprintReadWrite, Category = "Station State")
    bool bIsProcessing;

    FTimerHandle ProgressTimerHandle;

public:
    UFUNCTION(BlueprintCallable, Category = "Station Action")
    virtual void Interact(AChefCharacter* Chef);

    UFUNCTION(BlueprintCallable, Category = "Station Action")
    void SetProcessingFalse() { bIsProcessing = false; }

    UFUNCTION(BlueprintImplementableEvent, Category = "Station Action")
    void StartProcessing();

    UFUNCTION(BlueprintImplementableEvent, Category = "Station Action")
    void FinishProcessing();

    EStationType GetStationType() const { return StationType; }
    bool HasItem() const { return CurrentIngredient != nullptr; }

    bool IsProcessing() const { return bIsProcessing; }
    AIngredient* GetCurrentIngredient() const { return CurrentIngredient; }

    void RemoveIngredient() { CurrentIngredient = nullptr; }
};