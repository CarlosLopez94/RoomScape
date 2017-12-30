// Fill out your copyright notice in the Description page of Project Settings.

#include "PictureComponent.h"
#include "ButtonTriggerAction.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"


// Sets default values for this component's properties
UPictureComponent::UPictureComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPictureComponent::BeginPlay() {
	Super::BeginPlay();

	// ...

}


// Called every frame
void UPictureComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//Enable physchis to this actor and enables actorToEnable
void UPictureComponent::Trigger() {
	//Enable physchics for this object
	UStaticMeshComponent* staticMeshComponent = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	staticMeshComponent->SetSimulatePhysics(true);

}