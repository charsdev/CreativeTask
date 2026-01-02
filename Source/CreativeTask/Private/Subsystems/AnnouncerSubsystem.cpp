#include "Subsystems/AnnouncerSubsystem.h"

#include "Blueprint/UserWidget.h"
#include "Widget/AnnouncerWidget.h"
#include "Engine/Engine.h"

void UAnnouncerSubsystem::ShowMessage(const FText& Message, float Duration)
{
	if (!AnnouncerWidget)
	{
		if (!AnnouncerWidgetClass)
		{
			UE_LOG(LogTemp, Warning, TEXT("AnnouncerSubsystem: Missing WidgetClass"));
			return;
		}

		AnnouncerWidget = CreateWidget<UAnnouncerWidget>(GetWorld(), AnnouncerWidgetClass);
		if (AnnouncerWidget)
			AnnouncerWidget->AddToViewport();
	}

	if (AnnouncerWidget)
	{
		AnnouncerWidget->AddNotification(Message, Duration);
	}
}