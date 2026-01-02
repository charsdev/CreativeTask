#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interactor.generated.h"

class UInteractPopUp;
class UCameraComponent;

UCLASS( Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CREATIVETASK_API UInteractor : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractor();

protected:

	virtual void BeginPlay() override;
	
public:
	bool PerformTrace(FHitResult& OutHit);
	void HandleFocus(AActor* NewActor);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void InteractWithActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")
	float RadiusHintDetector { 200.f };

	UPROPERTY(EditAnywhere)
	float MaxInteractionDistance { 2000.f };

	UPROPERTY(EditAnywhere)
	float FindRadius { 25.f };
	
	bool HasActorOnFocus;
	
	UPROPERTY(Transient, BlueprintReadOnly, EditAnywhere)
	TObjectPtr<AActor> CurrentActor;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EDrawDebugTrace::Type> DebugTraceType { EDrawDebugTrace::ForOneFrame };
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AActor> LastActor;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInteractPopUp> InteractorWidgetClass;

	UPROPERTY()
	UInteractPopUp* InteractorWidgetInstance;

	UPROPERTY(EditDefaultsOnly)
	float MaxDistance = 200.f;

private:
	UPROPERTY()
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool ValidateDistance(AActor* Actor) const;
	void FindInteractableObject();
	void TogglePopUp();
	void UpdatePopUpPosition();
};