// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class ATriggerVolume;

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorOpener.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

/*
* A class that commands doors' opening
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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
	/* Takes care of opening and closing the door.
	*/
	void RunDoorMechanism();
	
	/* Gets the total mass on pressure plate.
	* @return The amount of mass in kg on the plate
	*/
	float GetTotalMassOnPressurePlate() const;

public:
	UPROPERTY(BlueprintAssignable, Category = "Event")
		FDoorEvent onOpenRequest;					// Instance of a class that will be used in blueprint
													// once the door has to open

	UPROPERTY(BlueprintAssignable, Category = "Event")
		FDoorEvent onCloseRequest;					// Instance of a class that will be used in blueprint
													// once the door has to close

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float _minMassKgToOpenDoor = 30.0f;			// Minimum mass in kg necessary to open the door

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		ATriggerVolume* _pressurePlate = nullptr;	// Pressure Plate that will allow actor to open the door
};
