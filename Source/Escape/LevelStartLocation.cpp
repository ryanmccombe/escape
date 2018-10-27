// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelStartLocation.h"
#include "EscapeGameState.h"
#include "Engine/World.h"


// Sets default values
ALevelStartLocation::ALevelStartLocation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelStartLocation::BeginPlay()
{
	Super::BeginPlay();

	auto GS = Cast<AEscapeGameState>(GetWorld()->GetGameState());

	if (!ensure(GS)) return;

	GS->RegisterStartLocation(this);
}

// Called every frame
void ALevelStartLocation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

