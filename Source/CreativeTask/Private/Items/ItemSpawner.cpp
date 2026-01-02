#include "Items/ItemSpawner.h"

AItemSpawner::AItemSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

AActor* AItemSpawner::Spawn()
{
	if (!ActorToSpawn) return nullptr;

	FVector Start = GetActorLocation();
	FVector End = Start - FVector(0, 0, TraceDistance);

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECC_WorldStatic,
		Params
	);

	FVector SpawnLocation = bHit ? Hit.Location : Start;

	SpawnLocation += SpawnOffset;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	return GetWorld()->SpawnActor<AActor>(
		ActorToSpawn,
		SpawnLocation,
		GetActorRotation(),
		SpawnParams
	);
}


