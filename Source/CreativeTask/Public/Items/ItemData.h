#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemData.generated.h"

class AItemBase;

UCLASS()
class CREATIVETASK_API UItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("Items", GetFName());
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ItemId;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* ItemIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsStackable = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MaxStackSize = 99;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AItemBase> ItemActorClass;
};