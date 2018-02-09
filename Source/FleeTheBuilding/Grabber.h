// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UPhysicsHandleComponent;

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

/*
* Handles the grabbing of physics elements
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FLEETHEBUILDING_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime,
							   ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

private:	
	/* Sets up input component and bind actions to it.
	*/
	void SetUpInputComponentAndBindActions();

	/* Grabs a physics object.
	*/
	void Grab();

	/* Releases a physics object.
	*/
	void Release();
			
	/* Gets the player viewpoint and performs a line trace.
	* @return The hit objects's info
	*/
	FHitResult DoLineTraceAndGetHitInfo();
	
	/* Gets the line trace start.
	* @return The line trace starting vector (player's location)
	*/
	FVector GetLineTraceStart();
	
	/* Gets the line trace end.
	* @return The line trace ending vector (player's look at vector)
	*/
	FVector GetLineTraceEnd();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float _reachCm = 120.0f;							// How far ahead of the player we can _reachCm in cm

	UPROPERTY(EditDefaultsOnly, Category = "Debug")
		bool _bDrawDebugRay = false;						// Whether or not it should draw a debug ray
	
	UPhysicsHandleComponent* _physicsHandler = nullptr;	// Physics handle for handling physics (Duh!)
	UInputComponent* _inputComponent = nullptr;			// Input component to handle input (Duh!)
};
