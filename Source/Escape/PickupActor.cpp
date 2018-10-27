#include "PickupActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"
#include "Engine/World.h"
#include "EscapeGameState.h"

APickupActor::APickupActor() {
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetupAttachment(MeshComp);

	bIsActive = true;
}

void APickupActor::BeginPlay() {
	Super::BeginPlay();

	PlayEffects();
}

void APickupActor::NotifyActorBeginOverlap(AActor* OtherActor) {
	Super::NotifyActorBeginOverlap(OtherActor);

	if (!bIsActive) return;

	PlayEffects();

	const auto PlayerCharacter = Cast<AFPSCharacter>(OtherActor);

	if (PlayerCharacter) {
		PlayerCharacter->bIsCarryingObjective = true;
		auto GS = Cast<AEscapeGameState>(GetWorld()->GetGameState());

		if (GS) {
			GS->CollectObjective(this);
		}

		Destroy();
	}
}

void APickupActor::PlayEffects() {
	UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());

}

void APickupActor::Deactivate() {
	bIsActive = false;
}
