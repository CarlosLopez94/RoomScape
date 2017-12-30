// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ButtonTriggerAction.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOMSCAPE_API UButtonTriggerAction : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPROPERTY(EditAnywhere, Category = "Action")
		bool isEnable;
	// Sets default values for this component's properties
	UButtonTriggerAction();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void TriggerAction();

private:
	UPROPERTY(EditAnywhere, Category = "Action")
		TArray<AActor*> actorsToTrigger;

	
};
