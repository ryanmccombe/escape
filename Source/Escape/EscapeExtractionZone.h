#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Levels.h"
#include "EscapeExtractionZone.generated.h"

class UBoxComponent;

UCLASS()
class ESCAPE_API AEscapeExtractionZone : public AActor
{
	GENERATED_BODY()
	
public:	
	AEscapeExtractionZone();

	UPROPERTY(EditInstanceOnly, Category = "Gameplay")
	ELevel Level;

protected:
	/// COMPONENTS
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* OverlapComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UDecalComponent* DecalComp;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* ObjectiveMissingSound;

	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void Deactivate();
	bool bIsActive;
};
