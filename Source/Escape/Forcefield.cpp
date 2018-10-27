#include "Forcefield.h"
#include "Components/StaticMeshComponent.h"

AForcefield::AForcefield() {
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
}

void AForcefield::Open() {
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// TODO: Update Material
}

void AForcefield::Close() {
	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	// TODO: Update Material
}
