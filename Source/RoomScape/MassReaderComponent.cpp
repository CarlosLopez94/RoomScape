// Fill out your copyright notice in the Description page of Project Settings.

#include "MassReaderComponent.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values for this component's properties
UMassReaderComponent::UMassReaderComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMassReaderComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMassReaderComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FString UMassReaderComponent::GetTextPercentage() {
	///Calculate the mass on the plate
	float percentage = GetNumberPercentage() * 100;

	///Formating the text
	return FString(FString::FromInt(percentage) +"/100");

}

float UMassReaderComponent::GetNumberPercentage() {
	float overlapingMass = 0;
	if (plate != nullptr) {
		TArray<AActor*> overlappingActors;
		plate->GetOverlappingActors(overlappingActors, nullptr);
		for (const AActor* actor : overlappingActors) {
			auto primitiveComponent = actor->FindComponentByClass<UPrimitiveComponent>();
			overlapingMass += primitiveComponent->GetMass();
		}
	}
	
	return FMath::Min(1.f,(float)overlapingMass/massToOpen);
}

