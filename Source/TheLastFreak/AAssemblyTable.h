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

    UPROPERTY(BlueprintReadWrite, Category = "Assembly State")
    bool bHasTomato;

    UPROPERTY(BlueprintReadWrite, Category = "Assembly State")
    bool bHasLettuce;

    UPROPERTY(BlueprintReadWrite, Category = "Assembly State")
    bool bHasMeat;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assembly Config")
    TSubclassOf<AIngredient> BurgerClass;

    FTimerHandle BurgerDeliveryTimerHandle;

public:
    virtual void Interact(AChefCharacter* Chef) override;

    UFUNCTION(BlueprintCallable, Category = "Assembly Actions")
    void ResetTable();

    UFUNCTION(BlueprintCallable, Category = "Assembly Actions")
    void ClearAssembledBurger();
};