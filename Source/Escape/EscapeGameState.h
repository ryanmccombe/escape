#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Levels.h"
#include "EscapeGameState.generated.h"

class ALevelStartLocation;
class APickupActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnoughObjectivesCollected, ELevel, Level);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCompleteLevel, ELevel, Level);

UCLASS()
class ESCAPE_API AEscapeGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AEscapeGameState();

	void CollectObjective(APickupActor* Objective);
	void SetCurrentLevel(ELevel Level);

	UPROPERTY(BlueprintAssignable, Category = "GameMode")
	FOnEnoughObjectivesCollected OnEnoughObjectivesCollected;

	UPROPERTY(BlueprintAssignable, Category = "GameMode")
	FOnCompleteLevel OnCompleteLevel;

	UFUNCTION(BlueprintCallable, Category = "GameState")
	int32 GetObjectiveCount();

	UFUNCTION(BlueprintCallable, Category = "GameState")
	bool TryCompleteLevel(ELevel Level);

	UFUNCTION(BlueprintCallable, Category = "GameState")
	bool CanCompleteLevel();

	void RegisterStartLocation(ALevelStartLocation* StartLocation);

	void RestartLevel();

	FTransform GetCurrentLevelStartTransform();

	bool CanRestartLevel();

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "GameState")
	void ObjectiveCountChanged(int32 ObjectiveCount);

	UFUNCTION(BlueprintImplementableEvent, Category = "GameState")
	void EnoughObjectivesCollected(bool bEnoughObjectivesCollected);

	UFUNCTION(BlueprintImplementableEvent, Category = "GameState")
	void LevelCompleted();
	
private:
	int32 ObjectivesCollected;
	bool bCanCompleteLevel;
	ELevel CurrentLevel;

	void CompleteLevel();

	void DeactivateAllObjectivesInCurrentLevel();

	TMap<ELevel, ALevelStartLocation*> LevelStartLocations;
};
