#include "Components/Interactor.h"

#include "Interfaces/Interactable.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/InteractPopUp.h"
#include "GameFramework/Actor.h"

UInteractor::UInteractor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractor::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (!Owner) return;
	
	CameraComponent = Cast<UCameraComponent>(GetOwner()->GetComponentByClass(UCameraComponent::StaticClass()));

	 if (InteractorWidgetClass)
	 {
		 InteractorWidgetInstance = CreateWidget<UInteractPopUp>(GetWorld(), InteractorWidgetClass);
		
		 if (InteractorWidgetInstance)
		 {
		 	InteractorWidgetInstance->AddToViewport();
		}
	 }
}

bool UInteractor::PerformTrace(FHitResult& OutHit)
{
	const FVector Start = GetOwner()->GetActorLocation();
	const FVector End = Start + CameraComponent->GetForwardVector() * MaxInteractionDistance;
	
	return UKismetSystemLibrary::SphereTraceSingle(
		this,
		Start,
		End,
		FindRadius,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,
		{ GetOwner() },
		DebugTraceType,
		OutHit,
		true
	);
}

void UInteractor::HandleFocus(AActor* NewActor)
{
	if (NewActor != LastActor)
	{
		if (LastActor)
		{
			IInteractable::Execute_OnFocus(LastActor);
		}

		if (NewActor)
		{
			IInteractable::Execute_OnLoseFocus(NewActor);
		}

		LastActor = NewActor;
		CurrentActor = NewActor;
	}

	HasActorOnFocus = (CurrentActor != nullptr);
}

void UInteractor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FHitResult Hit;
	AActor* NewActor = nullptr;

	if (PerformTrace(Hit))
	{
		AActor* HitActor = Hit.GetActor();

		if (HitActor &&
			HitActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()) &&
			ValidateDistance(HitActor))
		{
			NewActor = HitActor;
		}
	}

	HandleFocus(NewActor);
	
	 TogglePopUp();
	 UpdatePopUpPosition();
}

void UInteractor::InteractWithActor()
{
	if (CurrentActor && ValidateDistance(CurrentActor))
	{
		IInteractable::Execute_OnInteract(CurrentActor, GetOwner());
	}
}

void UInteractor::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor)
	{
		return;
	}

	if (OtherActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
	{
		IInteractable::Execute_OnFocus(OtherActor);
	}
	
}

void UInteractor::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor)
	{
		return;
	}

	if (OtherActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
	{
		IInteractable::Execute_OnLoseFocus(OtherActor);
	}
}

bool UInteractor::ValidateDistance(AActor* Actor) const
{
	if (!Actor) return false;

	const FBox Bounds = Actor->GetComponentsBoundingBox(true);

	const FVector ClosestPoint = Bounds.GetClosestPointTo(GetOwner()->GetActorLocation());

	const float DistSq = FVector::DistSquared(
		GetOwner()->GetActorLocation(),
		ClosestPoint
	);

	return DistSq <= MaxDistance * MaxDistance;
}

void UInteractor::FindInteractableObject()
{
	const FVector Start = CameraComponent->GetComponentLocation();
	const FVector End = Start + CameraComponent->GetForwardVector() * MaxInteractionDistance;
	
	FHitResult HitResult;
	AActor* NewActor = nullptr;

	const bool bHit = UKismetSystemLibrary::SphereTraceSingle(
		this,
		Start,
		End,
		FindRadius,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,
		 {},
		DebugTraceType,
		HitResult,
		true
	);

	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor && HitActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()) &&
			ValidateDistance(HitActor))
		{
			NewActor = HitActor;
		}
	}
	
	if (NewActor != LastActor)
	{
		if (LastActor)
		{
			IInteractable::Execute_OnLoseFocus(LastActor);
		}

		if (NewActor)
		{
			IInteractable::Execute_OnFocus(NewActor);
		}

		LastActor = NewActor;
		CurrentActor = NewActor;
	}
	
	HasActorOnFocus = (CurrentActor != nullptr);
}

void UInteractor::TogglePopUp()
{
	if (InteractorWidgetInstance)
	{
		InteractorWidgetInstance->SetVisibility(HasActorOnFocus ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}

void UInteractor::UpdatePopUpPosition()
{
	if (!HasActorOnFocus || !InteractorWidgetInstance || !CurrentActor)
	{
		return;
	}

	const APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC)
	{
		return;
	}

	FVector Origin, BoxExtent;
	CurrentActor->GetActorBounds(false, Origin, BoxExtent);

	FVector2D ScreenPosition;
	if (UGameplayStatics::ProjectWorldToScreen(PC, Origin, ScreenPosition))
	{
		InteractorWidgetInstance->SetPositionInViewport(ScreenPosition, true);
	}
}