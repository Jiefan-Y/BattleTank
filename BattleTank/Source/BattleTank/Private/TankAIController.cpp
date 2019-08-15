// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::Tick(float Deltatime)
{
	Super::Tick(Deltatime);
	AimTowardPlayerTank();
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto playerTank = GetPlayerTank();
	if (!playerTank) {
		UE_LOG(LogTemp, Warning, TEXT("Can't find player tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI controller found player: %s"), *(playerTank->GetName()));
	}
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!playerPawn) { return nullptr; }
	return Cast<ATank>(playerPawn);
}

void ATankAIController::AimTowardPlayerTank()
{
	if (!GetControlledTank() || !GetPlayerTank()) return;
	FVector PlayerTankLocation = GetPlayerTank()->GetTankLocation();
	GetControlledTank()->AimAt(PlayerTankLocation);
}
