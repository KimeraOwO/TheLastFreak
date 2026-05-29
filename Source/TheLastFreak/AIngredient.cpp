// Fill out your copyright notice in the Description page of Project Settings.

#include "AIngredient.h"
#include "Components/StaticMeshComponent.h"

AIngredient::AIngredient()
{
    PrimaryActorTick.bCanEverTick = false;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;

    MeshComponent->SetSimulatePhysics(true);
    MeshComponent->SetCollisionProfileName(TEXT("PhysicsActor"));
}

void AIngredient::BeginPlay()
{
    Super::BeginPlay();
}

void AIngredient::UpdateVisualMesh(UStaticMesh* NewMesh)
{
    if (MeshComponent && NewMesh)
    {
        MeshComponent->SetStaticMesh(NewMesh);
    }
}