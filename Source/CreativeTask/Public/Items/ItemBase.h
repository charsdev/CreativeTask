// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Interactable.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UCLASS()
class CREATIVETASK_API AItemBase : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AItemBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void OnInteract_Implementation(AActor* InteractingActor) override;
	virtual void OnFocus_Implementation() override;
	virtual void OnLoseFocus_Implementation() override;
};