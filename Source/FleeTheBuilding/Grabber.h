// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
class UPhysicsHandleComponent;
#include "Grabber.generated.h"

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
		
	/// <summary>
	/// Draws the ray to detect objects we hit.
	/// </summary>
	void DrawReachRay();
	
	/// <summary>
	/// Grabs a physics object.
	/// </summary>
	void Grab();
	
	/// <summary>
	/// Releases a physics object.
	/// </summary>
	void Release();

private:

	// How far ahead of the player we can reach in cm
	UPROPERTY(EditAnywhere)
		float reach = 100.0f;

	// Whether or not it should draw a debug ray
	UPROPERTY(EditAnywhere)
		bool drawDebugRay = false;
	
	// Physics handle for handling physics (Duh!)
	UPhysicsHandleComponent* physicsHandler = nullptr;

	// Input component to handle input (Duh!)
	UInputComponent* inputComponent = nullptr;
};
