#include "Widget/InteractPopUp.h"

#include "Components/TextBlock.h"

void UInteractPopUp::SetInteractableText(FText InText)
{
	if (InteractText)
	{
		InteractText->SetText(InText);
	}
}