#include "Components/Inventory.h"

#include "CreativeTask/DebugHelper.h"
#include "Items/ItemData.h"

UInventory::UInventory()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UInventory::TryAddItemToSlot(UItemData* Item, int32& OutSlotIndex, int32& OutQuantity, int32 Quantity)
{
	OutSlotIndex = -1;
	OutQuantity = 0;
	
	if (!Item || Quantity <= 0)
	{
		return false;
	}

	for (int32 i = 0; i < Slots.Num(); i++)
	{
		FInventoryItem& Slot = Slots[i];
		if (Slot.ItemData == Item && Item->bIsStackable)
		{
			Slot.Quantity = FMath::Clamp(
				Slot.Quantity + Quantity,
				1,
				Item->MaxStackSize
			);

			OutSlotIndex = i;
			OutQuantity = Slot.Quantity;
			OnAddItemToInventory.Broadcast(i, Slot);
			return true;
		}
	}

	const int32 NextEmptySlotIndex = GetEmptySlot();

	if (!Slots.IsValidIndex(NextEmptySlotIndex))
	{
		return false;
	}
	
	FInventoryItem& NextEmptySlot = Slots[NextEmptySlotIndex];
	NextEmptySlot.ItemData = Item;
	NextEmptySlot.Quantity = FMath::Clamp(Quantity, 1, Item->MaxStackSize);;
	OutSlotIndex = NextEmptySlotIndex;
	OutQuantity = NextEmptySlot.Quantity;

	OnAddItemToInventory.Broadcast(NextEmptySlotIndex, NextEmptySlot);
	return true;
}

bool UInventory::TryRemoveFromSlotIndex(int32 SlotIndex, int32 Quantity, FInventoryItem& OutRemovedItem)
{
	OutRemovedItem = FInventoryItem();

	if (!Slots.IsValidIndex(SlotIndex))
	{
		return false;
	}

	FInventoryItem& Slot = Slots[SlotIndex];

	if (!Slot.IsValid())
	{
		return false;
	}

	if (Quantity <= 0)
	{
		return false;
	}

	if (Slot.Quantity < Quantity)
	{
		return false;
	}

	Slot.Quantity = FMath::Clamp(Slot.Quantity - Quantity, 0, Slot.Quantity - Quantity);

	OutRemovedItem.ItemData = Slot.ItemData;
	OutRemovedItem.Quantity = Slot.Quantity;

	if (Slot.Quantity <= 0)
	{
		Slot = FInventoryItem();
	}

	OnRemoveItemFromInventory.Broadcast(SlotIndex, OutRemovedItem);

	return true;
}

bool UInventory::TryRemoveFromSlotItem(UItemData* ItemData, int32 Quantity, FInventoryItem& OutRemovedItem)
{
	OutRemovedItem = FInventoryItem();

	if (Quantity <= 0)
	{
		return false;
	}
	
	for (int32 i = 0; i < Slots.Num(); i++)
	{
		FInventoryItem& Slot = Slots[i];

		if (Slot.ItemData == ItemData)
		{
			if (Slot.Quantity < Quantity)
			{
				return false;
			}

			Slot.Quantity = FMath::Clamp(Slot.Quantity - Quantity, 0, Slot.Quantity - Quantity);
			OutRemovedItem.ItemData = Slot.ItemData;
			OutRemovedItem.Quantity = Slot.Quantity;

			if (Slot.Quantity <= 0)
			{
				Slot = FInventoryItem();
			}

			OnRemoveItemFromInventory.Broadcast(i, OutRemovedItem);
		}
	}
	
	return true;
}

bool UInventory::HasItem(UItemData* Item, int32 Quantity)
{
	for (const FInventoryItem& Entry : Slots)
	{
		if (Entry.ItemData == Item && Entry.Quantity >= Quantity)
		{
			return true;
		}
	}
	
	return false;
}

int32 UInventory::GetEmptySlot() const
{
	for (int32 i = 0; i < Slots.Num(); i++)
	{
		if (Slots[i].ItemData == nullptr)
		{
			return i;
		}
	}

	return -1;
}

void UInventory::BeginPlay()
{
	Slots.SetNum(MaxSlots);
}