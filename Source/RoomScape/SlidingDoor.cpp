// Fill out your copyright notice in the Description page of Project Settings.

#include "SlidingDoor.h"


// Sets default values for this component's properties
USlidingDoor::USlidingDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USlidingDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USlidingDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USlidingDoor::trigerSlide() {
	if (hasBeenSlide) {
		openSlide.Broadcast();
	} else {
		closeSlide.Broadcast();
	}
	hasBeenSlide = !hasBeenSlide;
}