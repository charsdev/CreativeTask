#include "Subsystems/ObjectPoolSubsystem.h"

#include "CreativeTask/DebugHelper.h"
#include "Interfaces/Poolable.h"

void UObjectPoolSubsystem::InitializePool(TSubclassOf<AActor> Class, int32 Size)
{
	TArray<AActor*>& Pool = Pools.FindOrAdd(*Class);

	for (int32 i = 0; i < Size; i++)
	{
		AActor* Obj = CachedWorld->SpawnActor<AActor>(Class);

		Obj->SetActorHiddenInGame(true);
		Obj->SetActorEnableCollision(false);
		Obj->SetActorTickEnabled(false);

		if (IPoolable* Poolable = Cast<IPoolable>(Obj))
		{
			Poolable->OnPoolDeactivated();
		}

		Pool.Add(Obj);
	}
}

void UObjectPoolSubsystem::ReturnToPool(AActor* Actor)
{
	if (!Actor) return;

	Actor->SetActorHiddenInGame(true);
	Actor->SetActorEnableCollision(false);
	Actor->SetActorTickEnabled(false);

	if (IPoolable* Poolable = Cast<IPoolable>(Actor))
	{
		Poolable->OnPoolDeactivated();
	}
}

AActor* UObjectPoolSubsystem::GetPooledObject(TSubclassOf<AActor> Class)
{
	TArray<AActor *>* Pool = Pools.Find(*Class);
	
	if (!Pool) return nullptr;

	for (AActor* Obj : *Pool)
	{
		if (Obj->IsHidden())
		{
			Obj->SetActorHiddenInGame(false);
			Obj->SetActorEnableCollision(true);
			Obj->SetActorTickEnabled(true);
			
			IPoolable::Execute_OnPoolActivated(Obj);

			return Obj;
		}
	}

	return nullptr;
}

void UObjectPoolSubsystem::AddToPool(AActor* Actor)
{
	if (!Actor) return;

	UClass* Class = Actor->GetClass();

	if (!Class) return;

	TArray<AActor*>& Pool = Pools.FindOrAdd(Class);
	Pool.AddUnique(Actor);
}

void UObjectPoolSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CachedWorld = GetWorld();
}