#include "AChefCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "AIngredient.h"
#include "AWorkStationBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AChefCharacter::AChefCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->bUsePawnControlRotation = false;
    CameraBoom->TargetArmLength = 800.f;
    CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));

    CameraBoom->bInheritPitch = false;
    CameraBoom->bInheritYaw = false;
    CameraBoom->bInheritRoll = false;

    TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
    TopDownCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    TopDownCamera->bUsePawnControlRotation = false;

    HoldingPoint = CreateDefaultSubobject<USceneComponent>(TEXT("HoldingPoint"));
    HoldingPoint->SetupAttachment(RootComponent);
    HoldingPoint->SetRelativeLocation(FVector(70.f, 0.f, 20.f));

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);

    InteractionDistance = 150.f;
    CurrentHeldIngredient = nullptr;
}

void AChefCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            if (DefaultMappingContext)
            {
                Subsystem->AddMappingContext(DefaultMappingContext, 0);
            }
        }
    }
}

void AChefCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (MoveAction)
        {
            EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AChefCharacter::EnhancedMove);
        }
    }

    PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AChefCharacter::InteractAction);
    PlayerInputComponent->BindAction("Drop", IE_Pressed, this, &AChefCharacter::DropAction);
}

void AChefCharacter::EnhancedMove(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(ForwardDirection, MovementVector.Y);
        AddMovementInput(RightDirection, MovementVector.X);
    }
}

void AChefCharacter::InteractAction()
{
    if (!GetWorld()) return;

    FVector StartLocation = GetActorLocation();
    FVector ForwardVector = GetActorForwardVector();
    FVector EndLocation = StartLocation + (ForwardVector * InteractionDistance);

    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);

    float TraceRadius = 40.f;
    FCollisionShape CollisionShape = FCollisionShape::MakeSphere(TraceRadius);

    bool bHit = GetWorld()->SweepSingleByChannel(
        HitResult,
        StartLocation,
        EndLocation,
        FQuat::Identity,
        ECC_Visibility,
        CollisionShape,
        QueryParams
    );

    if (bHit && HitResult.GetActor())
    {
        AWorkStationBase* Station = Cast<AWorkStationBase>(HitResult.GetActor());
        if (Station)
        {
            if (!IsHoldingItem() && Station->HasItem() && !Station->IsProcessing())
            {
                CurrentHeldIngredient = Station->GetCurrentIngredient();
                Station->RemoveIngredient();

                UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(CurrentHeldIngredient->GetRootComponent());
                if (MeshComp)
                {
                    MeshComp->SetSimulatePhysics(false);
                    MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
                }
                CurrentHeldIngredient->AttachToComponent(HoldingPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
                return;
            }

            Station->Interact(this);
            return;
        }

        if (!IsHoldingItem())
        {
            AIngredient* GroundIngredient = Cast<AIngredient>(HitResult.GetActor());
            if (GroundIngredient)
            {
                if (GroundIngredient->GetIngredientData().ItemType == EItemType::Burger) return;

                CurrentHeldIngredient = GroundIngredient;

                UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(CurrentHeldIngredient->GetRootComponent());
                if (MeshComp)
                {
                    MeshComp->SetSimulatePhysics(false);
                    MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
                }
                CurrentHeldIngredient->AttachToComponent(HoldingPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
            }
        }
    }
}

void AChefCharacter::ReleaseItemToStation()
{
    CurrentHeldIngredient = nullptr;
}

void AChefCharacter::DropAction()
{
    if (!CurrentHeldIngredient) return;

    CurrentHeldIngredient->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

    UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(CurrentHeldIngredient->GetRootComponent());
    if (MeshComp)
    {
        MeshComp->SetSimulatePhysics(true);
        MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    }

    CurrentHeldIngredient = nullptr;
}