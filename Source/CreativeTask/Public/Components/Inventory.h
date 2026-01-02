#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

class UItemData;

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UItemData* ItemData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity = 0;

	bool IsValid() const { return ItemData != nullptr && Quantity > 0; }
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAddItemToInventory, int32, Index, FInventoryItem, InventoryItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRemoveItemFromInventory, int32, Index, FInventoryItem, InventoryItem);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CREATIVETASK_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventory();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FInventoryItem> Slots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxSlots = 3;

	UFUNCTION(BlueprintCallable)
	bool TryAddItemToSlot(UItemData* Item, int32& OutSlotIndex, int32& OutQuantity, int32 Quantity = 1);

	UFUNCTION(BlueprintCallable)
	bool TryRemoveFromSlotIndex(int32 SlotIndex, int32 Quantity, FInventoryItem& OutRemovedItem);

	UFUNCTION(BlueprintCallable)
	bool TryRemoveFromSlotItem(UItemData* ItemData, int32 Quantity, FInventoryItem& OutRemovedItem);
	
	UFUNCTION(BlueprintCallable)
	bool HasItem(UItemData* Item, int32 Quantity = 1);

	int32 GetEmptySlot() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 CurrentItemIndex = 0;
	
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite)
	FOnAddItemToInventory OnAddItemToInventory;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite)
	FOnRemoveItemFromInventory OnRemoveItemFromInventory;
};