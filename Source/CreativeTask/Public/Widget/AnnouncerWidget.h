#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AnnouncerWidget.generated.h"

UCLASS()
class CREATIVETASK_API UAnnouncerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void AddNotification(const FText& Message, float Duration);
};