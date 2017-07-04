// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorOpener.h"

#include <Engine/World.h>
#include <GameFramework/PlayerController.h>


// Sets default values for this component's properties
UDoorOpener::UDoorOpener()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();

	// If there isn't a pressure plate...
	if (!pressurePlate)
		// Log error to output log
		GLog->Log("No pressure plate in the level!");

	// Get the actor that opens
	actorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

	// If the actor wasn't initialized
	if (!actorThatOpens)
		// Log error to output log
		GLog->Log("No actor in the level!");
	
	// Get time since last open
	timeSinceLastOpen = GetWorld()->GetTimeSeconds();
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

void UDoorOpener::Open() {
	// Open the door by setting its rotation to open angle
	GetOwner()->SetActorRotation(FRotator(0.0f, openAngle, 0.0f));
	// Set time since last open to now
	timeSinceLastOpen = GetWorld()->GetTimeSeconds();
}

void UDoorOpener::Close() {
	// Close the door by setting its rotation back to 0
	GetOwner()->SetActorRotation(FRotator(0.0f, -openAngle, 0.0f));
}

void UDoorOpener::RunDoorMechanism() {
	// If the actor is on pressure plate, open the door
	if (pressurePlate->IsOverlappingActor(actorThatOpens))
		Open();

	// Close the door when more than the given amount of secs have passed since
	// the door was last open
	if (GetWorld()->GetTimeSeconds() - timeSinceLastOpen > timeBeforeClosing)
		Close();
}

