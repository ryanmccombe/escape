#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Levels.h"
#include "CurrentLevelVolume.generated.h"

class UBoxComponent;

UCLASS()
class ESCAPE_API ACurrentLevelVolume : public AActor
{
	GENERATED_BODY()
	
public:
	ACurrentLevelVolume();

	UPROPERTY(EditInstanceOnly, Category = "Gameplay")
	ELevel Level;

protected:
	/// COMPONENTS
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* OverlapComp;

	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
