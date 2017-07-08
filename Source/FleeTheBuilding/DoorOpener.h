// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Engine/TriggerVolume.h>

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorOpener.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
/// <summary>
/// A class that commands doors' opening
/// </summary>
/// <seealso cref="UActorComponent" />
class FLEETHEBUILDING_API UDoorOpener: public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpener();

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
	/// Opens this instance of the door.
	/// </summary>
	void Open();
	
	/// <summary>
	/// Closes this instance of the door.
	/// </summary>
	void Close();
	
	/// <summary>
	/// Takes care of opening and closing the door.
	/// </summary>
	void RunDoorMechanism();
	
	/// <summary>
	/// Gets the total mass on pressure plate.
	/// </summary>
	/// <returns>The amount of mass in kg on the plate</returns>
	float GetTotalMassOnPressurePlate() const;

private:
	// Angle at which a door will open
	UPROPERTY(EditAnywhere)
		float openAngle = 90.0f;

	// Minimum mass in kg necessary to open the door
	UPROPERTY(EditAnywhere)
		float minMassToOpenDoor = 30.0f;

	// Time to wait before door closes
	UPROPERTY(EditAnywhere)
		float timeBeforeClosing = 2.0f;

	// Pressure Plate that will allow actor to open the door
	UPROPERTY(EditAnywhere)
		ATriggerVolume* pressurePlate = nullptr;

	// Time passed since the door was last open
	float timeSinceLastOpen = 0.0f;

	// Offset for openAngle to account for initial rotation
	float openAngleOffset = 90.0f;
};
