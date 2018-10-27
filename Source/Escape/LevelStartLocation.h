#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "Levels.h"
#include "LevelStartLocation.generated.h"


UCLASS()
class ESCAPE_API ALevelStartLocation : public ATargetPoint
{
	GENERATED_BODY()
	
public:	
	ALevelStartLocation();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditInstanceOnly, Category = "Gameplay")
	ELevel Level;

protected:
	virtual void BeginPlay() override;

};
