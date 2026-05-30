// Fill out your copyright notice in the Description page of Project Settings.

#include "AMainGameMode.h"
#include "ACustomerNPC.h"

AMainGameMode::AMainGameMode()
{
    CustomerSpawnLocation = FVector(500.f, 0.f, 100.f);
}

void AMainGameMode::BeginPlay()
{
    Super::BeginPlay();

    SpawnNewCustomer();
}

void AMainGameMode::SpawnNewCustomer()
{
    if (!GetWorld() || !CustomerClass) return;

    FActorSpawnParameters SpawnParams;

    GetWorld()->SpawnActor<ACustomerNPC>(CustomerClass, CustomerSpawnLocation, FRotator::ZeroRotator, SpawnParams);

    UE_LOG(LogTemp, Log, TEXT("A new customer has entered the restaurant!"));
}