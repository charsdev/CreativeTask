#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AnnouncerSubsystem.generated.h"

class UAnnouncerWidget;

UCLASS(Abstract, Blueprintable)
class CREATIVETASK_API UAnnouncerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void ShowMessage(const FText& Message, float Duration = 3.0f);

protected:

	UPROPERTY()
	UAnnouncerWidget* AnnouncerWidget;

	UPROPERTY(EditAnywhere, Category="Announcer", meta=(AllowPrivateAccess=true), BlueprintReadWrite)
	TSubclassOf<UUserWidget> AnnouncerWidgetClass;
};