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

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    class UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    class UInputAction* MoveAction;

    void EnhancedMove(const struct FInputActionValue& Value);

public:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


    void InteractAction();
    void DropAction();

    UFUNCTION(BlueprintCallable, Category = "Chef")
    bool IsHoldingItem() const { return CurrentHeldIngredient != nullptr; }

    UFUNCTION(BlueprintCallable, Category = "Chef")
    void SetCurrentHeldIngredient(AIngredient* NewIngredient) { CurrentHeldIngredient = NewIngredient; }

    UFUNCTION(BlueprintCallable, Category = "Chef")
    AIngredient* GetCurrentHeldIngredient() const { return CurrentHeldIngredient; }

    UFUNCTION(BlueprintCallable, Category = "Chef")
    void ReleaseItemToStation();

    USceneComponent* GetHoldingPoint() const { return HoldingPoint; }
};