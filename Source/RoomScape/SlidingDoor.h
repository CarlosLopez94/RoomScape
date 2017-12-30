// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SlidingDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSlidingDoor);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOMSCAPE_API USlidingDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USlidingDoor();

	UPROPERTY(BlueprintAssignable)
	FSlidingDoor openSlide;

	UPROPERTY(BlueprintAssignable)
	FSlidingDoor closeSlide;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void trigerSlide();

private:
	//Controls if the door is going to hide or to recover its original position
	bool hasBeenSlide;
		
	
};
