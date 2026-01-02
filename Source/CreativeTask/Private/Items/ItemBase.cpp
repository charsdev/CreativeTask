#include "Items/ItemBase.h"
#include "../DebugHelper.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();
}

void AItemBase::OnInteract_Implementation(AActor* InteractingActor)
{
	IInteractable::OnInteract_Implementation(InteractingActor);
}

void AItemBase::OnFocus_Implementation()
{
	IInteractable::OnFocus_Implementation();
}

void AItemBase::OnLoseFocus_Implementation()
{
	IInteractable::OnLoseFocus_Implementation();
}


