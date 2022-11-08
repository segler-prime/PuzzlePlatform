// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "PlatformTrigger.h"
#include "Kismet/GameplayStatics.h"

AMovingPlatform::AMovingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;
    SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        SetReplicates(true); 
        SetReplicateMovement(true);    
    }

    GlobalStartLocation = GetActorLocation();
    GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);

    TArray<AActor*> FoundTriggers;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlatformTrigger::StaticClass(), FoundTriggers);

    for ( int i = 0; i < FoundTriggers.Num(); i++)
    {
        APlatformTrigger* TempTrigger = Cast<APlatformTrigger>(FoundTriggers[i]);
        TempTrigger->TriggerActive.BindUObject(this, &AMovingPlatform::TriggerOn);
        TempTrigger->TriggerInActive.BindUObject(this, &AMovingPlatform::TriggerOff);
    }

}

void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

//    if (HasAuthority())
//    {
    if (!TriggerPlatform || ShouldMove)
    {
        FVector Location = GetActorLocation();
        float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
        float JourneyTravelled = (Location - GlobalStartLocation).Size();
        if (JourneyTravelled >= JourneyLength)
        {
            FVector Swap = GlobalStartLocation;
            GlobalStartLocation = GlobalTargetLocation;
            GlobalTargetLocation = Swap;
        }
        FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
        Location = Location + (MoveRate*DeltaTime*Direction);
        SetActorLocation(Location);
    }
//    }

}

void AMovingPlatform::TriggerOn()
{
    ShouldMove = true;
}

void AMovingPlatform::TriggerOff()
{
    ShouldMove = false;
}

