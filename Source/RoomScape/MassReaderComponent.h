// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "MassReaderComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOMSCAPE_API UMassReaderComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMassReaderComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, Category = "PlateReader")
		float massToOpen;
	UPROPERTY(EditAnywhere, Category = "PlateReader")
		ATriggerVolume* plate;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, Category = "PlateReader")
	FString GetTextPercentage();
	UFUNCTION(BlueprintCallable, Category = "PlateReader")
	float GetNumberPercentage();

};
