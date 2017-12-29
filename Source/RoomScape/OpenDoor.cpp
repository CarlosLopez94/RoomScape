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
		onOpen.Broadcast();
	} else {
		onClose.Broadcast();
	}
}

float UOpenDoor::GetTotalMassOnPlate(ATriggerVolume* pleassurePlate) {
	float totalMass = 0;

	//Get actors overlapping with pleassurePlate and sum their mass
	if (pleassurePlate != nullptr) {
		TArray<AActor*> overlappingActors;
		pleassurePlate->GetOverlappingActors(overlappingActors, nullptr);
		for (const AActor* actor : overlappingActors) {
			auto primitiveComponent = actor->FindComponentByClass<UPrimitiveComponent>();
			totalMass += primitiveComponent->GetMass();
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("%s doesnt have any plates"), *GetOwner()->GetName());
	}
	return totalMass;
}
