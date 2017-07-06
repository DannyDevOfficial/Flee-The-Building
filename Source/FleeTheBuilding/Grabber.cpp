// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

#include <GameFramework/PlayerController.h>
#include <GameFramework/Controller.h>
#include <Engine/World.h>
#include <DrawDebugHelpers.h>
#include <PhysicsEngine/PhysicsHandleComponent.h>


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// Grab the attached physics handle component
	physicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	
	// Log error to the console in case it wasn't found
	if (!physicsHandler)
		GLog->Log(ELogVerbosity::Error,
				  "No UPhysicsHandleComponent for: " + GetOwner()->GetName());
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Draw the ray
	DrawReachRay();
}

void UGrabber::DrawReachRay() {
	/// Get player's viewpoint and store it in these two variables
	FVector playerLocation;
	FRotator playerRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(playerLocation, playerRotation);

	// Get line trace ending point
	FVector lineTraceEnd = playerLocation + playerRotation.Vector() * reach;

	// Draw debug ray if flag is set to true
	if (drawDebugRay)
		DrawDebugLine(GetWorld(),
					  playerLocation,
					  lineTraceEnd,
					  FColor(255, 0, 0),
					  false,
					  -1.0f,
					  (uint8)'\000',
					  2.0f);

	// Store hit info
	FHitResult hitInfo;

	// Get hit objects in the world and store their info in hit result
	if (GetWorld()->LineTraceSingleByObjectType(hitInfo,
											playerLocation,
											lineTraceEnd,
											FCollisionObjectQueryParams(
												ECollisionChannel::ECC_PhysicsBody
											)))
		// Log hit info to the console if there is any hit
		GLog->Log(hitInfo.GetActor()->GetName());
}

