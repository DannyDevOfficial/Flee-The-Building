// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Engine/TriggerVolume.h>

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorOpener.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

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

public:
	// Instance of a class that will be used in blueprint
	// once the door has to open
	UPROPERTY(BlueprintAssignable)
		FDoorEvent onOpenRequest;

	// Instance of a class that will be used in blueprint
	// once the door has to close
	UPROPERTY(BlueprintAssignable)
		FDoorEvent onCloseRequest;

private:		
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
	// Minimum mass in kg necessary to open the door
	UPROPERTY(EditAnywhere)
		float minMassToOpenDoor = 30.0f;

	// Pressure Plate that will allow actor to open the door
	UPROPERTY(EditAnywhere)
		ATriggerVolume* pressurePlate = nullptr;
};
