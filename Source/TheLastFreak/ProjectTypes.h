#pragma once

#include "CoreMinimal.h"
#include "ProjectTypes.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
    None,
    Tomato,
    Lettuce,
    Meat,
    Burger
};

UENUM(BlueprintType)
enum class EItemState : uint8
{
    Raw,
    Processed
};

UENUM(BlueprintType)
enum class EStationType : uint8
{
    None,
    CuttingBoard,
    Oven,
    AssemblyTable
};

USTRUCT(BlueprintType)
struct FIngredientData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ingredient")
    EItemType ItemType = EItemType::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ingredient")
    EItemState ItemState = EItemState::Raw;
};