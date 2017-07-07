// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

#include <GameFramework/PlayerController.h>
#include <GameFramework/Controller.h>
#include <Engine/World.h>
#include <DrawDebugHelpers.h>
#include <PhysicsEngine/PhysicsHandleComponent.h>
#include <Components/PrimitiveComponent.h>


// Sets default values for this component's properties
UGrabber::UGrabber() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay() {
	Super::BeginPlay();

	/// Call methods to set up components
	InitPhysicsHandleComponent();
	SetUpInputComponentAndBindActions();
}

void UGrabber::InitPhysicsHandleComponent() {
	// Grab the attached physics handle component
	physicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	// Log error to the console in case it wasn't found
	if (!physicsHandler)
		GLog->Log(ELogVerbosity::Error,
				  "No UPhysicsHandleComponent for: " + GetOwner()->GetName());
}

void UGrabber::SetUpInputComponentAndBindActions() {
	// Grab the attached input component
	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	// Log error if it can't find it
	if (!inputComponent) {
		GLog->Log(ELogVerbosity::Error,
				  "No UInputComponent for: " + GetOwner()->GetName());
	} else {
		/// Grabbing and releasing input actions
		inputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
		inputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabber::Release);
	}
}

void UGrabber::Grab() {
	// Get hit info
	FHitResult hitResult = DoLineTraceAndGetHitInfo();

	// Try and grab the actor from the hit result
	AActor* grabbedActor = hitResult.GetActor();

	// if there is an actor grabbed
	if (grabbedActor) {
		// Get actor related to hit result
		UPrimitiveComponent* componentToGrab = hitResult.GetComponent();

		// if there is a physics handle attached then
		// grab component
		if (physicsHandler)
			physicsHandler->GrabComponent(componentToGrab,
										  NAME_None,
										  componentToGrab->GetOwner()->GetActorLocation(),
										  true);
	}
}

void UGrabber::Release() {
	// if there is a physics handle
	if (physicsHandler)
		// if there is a grabbed component
		if (physicsHandler->GrabbedComponent)
			// Release it
			physicsHandler->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if there is a physics handle attached
	if (physicsHandler)
		// if there is a grabbed component
		if (physicsHandler->GrabbedComponent) {
			/// Get player's viewpoint and store it in these two variables
			FVector playerLocation;
			FRotator playerRotation;

			GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(playerLocation, playerRotation);

			// Get line trace ending point
			FVector lineTraceEnd = playerLocation + playerRotation.Vector() * reach;

			// Set grabbed component location every frame
			physicsHandler->SetTargetLocation(lineTraceEnd);
		}
}

FHitResult UGrabber::DoLineTraceAndGetHitInfo() {
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
	GetWorld()->LineTraceSingleByObjectType(hitInfo,
											playerLocation,
											lineTraceEnd,
											FCollisionObjectQueryParams(
												ECollisionChannel::ECC_PhysicsBody
											));

	// return hit info
	return hitInfo;
}