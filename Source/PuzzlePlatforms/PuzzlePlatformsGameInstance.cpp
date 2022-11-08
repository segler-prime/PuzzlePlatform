// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"


UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance()
{
    UE_LOG(LogTemp, Warning, TEXT("Game Instance - Constructor"));
}
	
void UPuzzlePlatformsGameInstance::Init()
{
    UE_LOG(LogTemp, Warning, TEXT("Game Instance - Init"));
}

void UPuzzlePlatformsGameInstance::Host()
{
    UEngine* Engine = GetEngine();

    Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, TEXT("Hosting"));

}

void UPuzzlePlatformsGameInstance::Join(FString Address)
{
    UEngine* Engine = GetEngine();

    Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, TEXT("Joining"));
    Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Address is: %s"), *Address));

}

