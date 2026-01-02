#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractPopUp.generated.h"

UCLASS()
class CREATIVETASK_API UInteractPopUp : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetInteractableText(FText InText);
	
private:
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* InteractText;
};