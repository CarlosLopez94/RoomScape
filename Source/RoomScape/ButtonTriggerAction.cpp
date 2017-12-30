// Fill out your copyright notice in the Description page of Project Settings.

#include "ButtonTriggerAction.h"
#include "GameFramework/Actor.h"
#include "SlidingDoor.h"


// Sets default values for this component's properties
UButtonTriggerAction::UButtonTriggerAction() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UButtonTriggerAction::BeginPlay() {
	Super::BeginPlay();

	// ...

}


// Called every frame
void UButtonTriggerAction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UButtonTriggerAction::TriggerAction() {
		for (const AActor* actor : actorsToTrigger) {
			if (actor != nullptr) {
				USlidingDoor* slidingDoor = actor->FindComponentByClass<USlidingDoor>();
				if (slidingDoor != nullptr) {
					UE_LOG(LogTemp, Warning, TEXT("Triggering action"));
					slidingDoor->trigerSlide();
				}
			}
		}
}