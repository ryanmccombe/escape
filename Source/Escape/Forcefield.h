#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Forcefield.generated.h"

UCLASS()
class ESCAPE_API AForcefield : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AForcefield();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void Open();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void Close();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;
};
