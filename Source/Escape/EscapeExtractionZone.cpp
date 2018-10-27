#include "EscapeExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"
#include "EscapeGameState.h"

AEscapeExtractionZone::AEscapeExtractionZone() {
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200.f));
	RootComponent = OverlapComp;

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AEscapeExtractionZone::HandleOverlap);

	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComp->DecalSize = FVector(200.f);
	DecalComp->SetupAttachment(OverlapComp);

	bIsActive = true;
}

void AEscapeExtractionZone::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (!bIsActive) return;
	auto PlayerCharacter = Cast<AFPSCharacter>(OtherActor);
	auto GS = Cast<AEscapeGameState>(GetWorld()->GetGameState());
	if (!PlayerCharacter || !GS) return;

	if (GS->TryCompleteLevel(Level)) {
		Deactivate();
	} else {
		UGameplayStatics::PlaySound2D(this, ObjectiveMissingSound);
	}
}

void AEscapeExtractionZone::Deactivate() {
	bIsActive = false;
}
