// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Public/DrawDebugHelpers.h"
#include "Public/Math/Color.h"


// Sets default values for this component's properties
UGrabber::UGrabber() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay() {
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber Component says MURRAY!"));

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	///Get player view point this tick
	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(playerViewPointLocation,
		playerViewPointRotation);


	///Draw a red trace in the world
	FVector lineTraceEnd = playerViewPointLocation + playerViewPointRotation.Vector()*reach;
	DrawDebugLine(GetWorld(), playerViewPointLocation, lineTraceEnd, FColor::Red, false, 0.f, 0.f, 10.f);

	///Setup query parameters
	FCollisionQueryParams traceParameters = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());

	///Line-trace: Ray-cast out the reach distance
	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(
		hit,
		playerViewPointLocation,
		lineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		traceParameters);

	///See what we hit
	if (hit.Actor!=nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("%s can grabber %s"),*GetOwner()->GetName(),*hit.Actor->GetName());
	}

}

