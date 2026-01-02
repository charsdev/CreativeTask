#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Poolable.generated.h"

UINTERFACE(MinimalAPI)
class UPoolable : public UInterface
{
	GENERATED_BODY()
};

class CREATIVETASK_API IPoolable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnPoolActivated();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnPoolDeactivated();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ReturnToPool();
};