// Fill out your copyright notice in the Description page of Project Settings.

#include "AAssemblyTable.h"
#include "AIngredient.h"
#include "AChefCharacter.h"
#include "NiagaraComponent.h"
#include "Components/StaticMeshComponent.h"

AAssemblyTable::AAssemblyTable()
{
    StationType = EStationType::AssemblyTable;
    ResetTable();
}

void AAssemblyTable::BeginPlay()
{
    Super::BeginPlay();
}

void AAssemblyTable::Interact(AChefCharacter* Chef)
{
    if (!Chef || bIsProcessing) return;

    if (CurrentIngredient && CurrentIngredient->GetIngredientData().ItemType == EItemType::Burger)
    {
        return;
    }

    if (Chef->IsHoldingItem())
    {
        AIngredient* HeldItem = Chef->GetCurrentHeldIngredient();
        if (!HeldItem) return;

        FIngredientData Data = HeldItem->GetIngredientData();

        if (Data.ItemState != EItemState::Processed) return;

        bool bItemAccepted = false;

        if (Data.ItemType == EItemType::Tomato && !bHasTomato)
        {
            bHasTomato = true;
            bItemAccepted = true;
        }
        else if (Data.ItemType == EItemType::Lettuce && !bHasLettuce)
        {
            bHasLettuce = true;
            bItemAccepted = true;
        }
        else if (Data.ItemType == EItemType::Meat && !bHasMeat)
        {
            bHasMeat = true;
            bItemAccepted = true;
        }

        if (bItemAccepted)
        {
            Chef->ReleaseItemToStation();
            HeldItem->Destroy();

            if (bHasTomato && bHasLettuce && bHasMeat)
            {
                StartProcessing();
            }
        }
    }
}

void AAssemblyTable::ClearAssembledBurger()
{
    if (CurrentIngredient)
    {
        CurrentIngredient->Destroy();
        CurrentIngredient = nullptr;
    }
    ResetTable();

}

void AAssemblyTable::ResetTable()
{
    bHasTomato = false;
    bHasLettuce = false;
    bHasMeat = false;
    bIsProcessing = false;
}