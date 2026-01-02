#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ObjectPoolSubsystem.generated.h"

UCLASS()
class CREATIVETASK_API UObjectPoolSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void InitializePool(TSubclassOf<AActor> Class, int32 Size);
	
	UFUNCTION(BlueprintCallable)
	void ReturnToPool(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	AActor* GetPooledObject(TSubclassOf<AActor> Class);

	UFUNCTION(BlueprintCallable)
	void AddToPool(AActor* Actor);

private:
	UPROPERTY()
	UWorld* CachedWorld;

	TMap<UClass*, TArray<AActor*>> Pools;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};