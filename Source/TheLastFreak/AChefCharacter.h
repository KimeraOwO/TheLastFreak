// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AChefCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USceneComponent;
class AIngredient;

UCLASS()
class THELASTFREAK_API AChefCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AChefCharacter();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    UCameraComponent* TopDownCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
    USceneComponent* HoldingPoint;

    UPROPERTY(BlueprintReadWrite, Category = "Chef State")
    AIngredient* CurrentHeldIngredient;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    float InteractionDistance;

public:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void MoveForward(float Value);
    void MoveRight(float Value);

    void InteractAction();
    void DropAction();

    UFUNCTION(BlueprintCallable, Category = "Chef")
    bool IsHoldingItem() const { return CurrentHeldIngredient != nullptr; }

    UFUNCTION(BlueprintCallable, Category = "Chef")
    AIngredient* GetCurrentHeldIngredient() const { return CurrentHeldIngredient; }

    UFUNCTION(BlueprintCallable, Category = "Chef")
    void ReleaseItemToStation();
};