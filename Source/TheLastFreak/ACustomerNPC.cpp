// Fill out your copyright notice in the Description page of Project Settings.


#include "ACustomerNPC.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

ACustomerNPC::ACustomerNPC()
{
    PrimaryActorTick.bCanEverTick = false;
    MaxPatienceTime = 180.0f;
    ExitLocation = FVector(-500.f, 0.f, 100.f);
}

void ACustomerNPC::BeginPlay()
{
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(PatienceTimerHandle, this, &ACustomerNPC::OnPatienceTimeout, MaxPatienceTime, false);
}

void ACustomerNPC::OnPatienceTimeout()
{
    UE_LOG(LogTemp, Warning, TEXT("Customer lost patience and left!"));
    LeaveRestaurant();
}

void ACustomerNPC::ReceiveOrder()
{
    GetWorld()->GetTimerManager().ClearTimer(PatienceTimerHandle);

    UE_LOG(LogTemp, Log, TEXT("Customer received burger and is happy!"));

    FTimerHandle LeaveDelayHandle;
    GetWorld()->GetTimerManager().SetTimer(LeaveDelayHandle, this, &ACustomerNPC::LeaveRestaurant, 1.0f, false);
}

void ACustomerNPC::LeaveRestaurant()
{
    Destroy();
}