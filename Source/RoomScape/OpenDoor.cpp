// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll the triggerVolumes, if 
	bool open = true;
	if (pleassurePlates.Num() > 0) {
		int32 i = 0;
		while (open && i < pleassurePlates.Num()) {
			ATriggerVolume* plate = pleassurePlates[i];
			open = GetTotalMassOnPlate(plate) >= massToOpen;
			i++;
		}
	} else {
		open = false;
	}

	//Open the door if all the plates of the door were trigering
	if (open) {
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	// Close the door when the time is over
	float currentTime = GetWorld()->GetTimeSeconds();

	if (currentTime - LastDoorOpenTime > closeDoorDelay) {
		CloseDoor();
	}
}

/*
*Opens the door
*/
void UOpenDoor::OpenDoor() {
	// Find the owner
	AActor* owner = GetOwner();

	//Rotate the owner (door) some degrees to open
	FRotator rotation = owner->GetActorRotation();
	rotation.Yaw = openAngle;
	owner->SetActorRotation(rotation);
}


/*
*Close the door
*/
void UOpenDoor::CloseDoor() {
	// Find the owner
	AActor* owner = GetOwner();

	//Rotate the owner (door) some degrees to open
	FRotator rotation = owner->GetActorRotation();
	rotation.Yaw = 0;
	owner->SetActorRotation(rotation);
}

float UOpenDoor::GetTotalMassOnPlate(ATriggerVolume* pleassurePlate) {
	float totalMass = 0;

	//Get actors overlapping with pleassurePlate and sum their mass
	TArray<AActor*> overlappingActors;
	pleassurePlate->GetOverlappingActors(overlappingActors, nullptr);
	for (const AActor* actor : overlappingActors) {
		auto primitiveComponent = actor->FindComponentByClass<UPrimitiveComponent>();
		totalMass += primitiveComponent->GetMass();
	}

	return totalMass;
}
