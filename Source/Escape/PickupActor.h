#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Levels.h"
#include "PickupActor.generated.h"

class USphereComponent;

UCLASS()
class ESCAPE_API APickupActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APickupActor();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(EditInstanceOnly, Category = "Gameplay")
	ELevel Level;

	void Deactivate();

protected:
	virtual void BeginPlay() override;

	/// COMPONENTS
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* PickupFX;

	void PlayEffects();

private:
	bool bIsActive;
};
