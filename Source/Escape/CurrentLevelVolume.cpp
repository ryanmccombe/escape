#include "CurrentLevelVolume.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "EscapeGameState.h"


// Sets default values
ACurrentLevelVolume::ACurrentLevelVolume()
{
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200.f));
	RootComponent = OverlapComp;

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &ACurrentLevelVolume::HandleOverlap);
}

void ACurrentLevelVolume::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto GS = Cast<AEscapeGameState>(GetWorld()->GetGameState());

	if (GS) {
		UE_LOG(LogTemp, Log, TEXT("You changed level"));
		GS->SetCurrentLevel(Level);
	}
}
