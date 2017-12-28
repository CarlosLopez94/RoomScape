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

	///Find the PhyshicsHandleComponent
	physicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (physicsHandleComponent) {
		UE_LOG(LogTemp, Warning, TEXT("%s has PhyshicsHandleComponent"),*GetOwner()->GetName());
	} else {
		UE_LOG(LogTemp, Error, TEXT("%s DOESNT HAVE any PhyshicsHandleComponent"), *GetOwner()->GetName());
	}

	///Find the PawnInputComponent
	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (inputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("%s has pawnInputComponent"), *GetOwner()->GetName());
		inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		inputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);

	} else {
		UE_LOG(LogTemp, Error, TEXT("%s DOESNT HAVE any pawnInputComponent"), *GetOwner()->GetName());
	}

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed"));

	/// LINE TRACE and reach any actor with physics body collision channel set
	GetFirstBodyInReach();

	///If we hit something then attach a physics handle

	///TODO attach physhics handle

	///TODO release physhics handle

}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Grab Released"));
}

void UGrabber::GetFirstBodyInReach() {
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
	if (hit.Actor != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("%s can grabber %s"), *GetOwner()->GetName(), *hit.Actor->GetName());
	}
}
