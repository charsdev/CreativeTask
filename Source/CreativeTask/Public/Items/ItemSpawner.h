#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawner.generated.h"

UCLASS()
class CREATIVETASK_API AItemSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere)
	float TraceDistance = 5000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = true))
	FVector SpawnOffset = FVector::ZeroVector;

	UFUNCTION(BlueprintCallable)
	virtual AActor* Spawn();
};