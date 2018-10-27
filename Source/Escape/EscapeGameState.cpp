#include "EscapeGameState.h"
#include "PickupActor.h"
#include "Kismet/GameplayStatics.h"
#include "LevelStartLocation.h"
#include "Engine/World.h"

AEscapeGameState::AEscapeGameState() {
	ObjectivesCollected = 0;
	bCanCompleteLevel = false;
}

void AEscapeGameState::CollectObjective(APickupActor* Objective) {
	ObjectivesCollected += 1;
	ObjectiveCountChanged(ObjectivesCollected);

	if (ObjectivesCollected == 3) {
		bCanCompleteLevel = true;
		EnoughObjectivesCollected(true);
		OnEnoughObjectivesCollected.Broadcast(CurrentLevel);
		DeactivateAllObjectivesInCurrentLevel();
	}
}

void AEscapeGameState::SetCurrentLevel(ELevel Level) {
	CurrentLevel = Level;
}

bool AEscapeGameState::TryCompleteLevel(ELevel LevelToComplete) {
	if (bCanCompleteLevel) {
		CompleteLevel();
		return true;
	}

	return false;
}

void AEscapeGameState::CompleteLevel() {
	LevelCompleted();
	ObjectivesCollected = 0;
	ObjectiveCountChanged(ObjectivesCollected);
	EnoughObjectivesCollected(false);
	bCanCompleteLevel = false;
	OnCompleteLevel.Broadcast(CurrentLevel);
}

void AEscapeGameState::DeactivateAllObjectivesInCurrentLevel() {
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(this, APickupActor::StaticClass(), FoundActors);

	for (auto Actor : FoundActors) {
		auto PickupActor = Cast<APickupActor>(Actor);
		if (PickupActor && PickupActor->Level == CurrentLevel) {
			PickupActor->Deactivate();
		}
	}
}

void AEscapeGameState::RegisterStartLocation(ALevelStartLocation* StartLocation) {
	LevelStartLocations.Add(StartLocation->Level, StartLocation);
}

void AEscapeGameState::RestartLevel()
{
	UE_LOG(LogTemp, Log, TEXT("Restarting Level"));
}

FTransform AEscapeGameState::GetCurrentLevelStartTransform()
{
	auto CurrentLevelStartLocation = LevelStartLocations.Find(CurrentLevel);
	if (!ensure(CurrentLevelStartLocation)) return *new FTransform();

	return LevelStartLocations[CurrentLevel]->GetActorTransform();
}

bool AEscapeGameState::CanRestartLevel()
{
	return CurrentLevel == ELevel::Level1 || CurrentLevel == ELevel::Tutorial2;
}

bool AEscapeGameState::CanCompleteLevel() { return bCanCompleteLevel; }

int32 AEscapeGameState::GetObjectiveCount() { return ObjectivesCollected; }
