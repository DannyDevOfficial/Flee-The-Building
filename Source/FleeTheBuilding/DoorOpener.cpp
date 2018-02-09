// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorOpener.h"

#include <Engine/World.h>
#include <GameFramework/PlayerController.h>
#include <Components/PrimitiveComponent.h>


// Sets default values for this component's properties
UDoorOpener::UDoorOpener()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();

	// If there isn't a pressure plate...
	if (!pressurePlate)
		// Log error to output log
		GLog->Log(ELogVerbosity::Error, "No pressure plate in the level!");
}


// Called every frame
void UDoorOpener::TickComponent(float DeltaTime,
								ELevelTick TickType,
								FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Handle door open and close
	RunDoorMechanism();
}

void UDoorOpener::RunDoorMechanism() {
	// If the min amount of mass is on the pressure plate,
	// open the door
	if (GetTotalMassOnPressurePlate() >= minMassToOpenDoor)
		onOpenRequest.Broadcast();
	else
		// Close the door when the weight isn't enough
		onCloseRequest.Broadcast();
}

float UDoorOpener::GetTotalMassOnPressurePlate() const {
	// Get out of here if there is no pressure plate!
	if (!pressurePlate)
		return 0.0f;

	// The mass total that will get returned
	float totalMass = 0.0f;

	// Array where to store all the overlapping actors
	TArray<AActor*> overlappingActors;

	// Get all the overlapping actors and store them in
	// the previously declared array
	pressurePlate->GetOverlappingActors(overlappingActors);

	// Loop throug the overlapping actors
	for (AActor* overlappingActor : overlappingActors) {
		// Get this overlapping actor's mass
		// and add it to the total mass
		totalMass +=
			Cast<UPrimitiveComponent>(overlappingActor->GetRootComponent())->GetMass();
	}

	// Return the total mass
	return totalMass;
}

