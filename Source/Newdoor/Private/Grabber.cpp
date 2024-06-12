// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#define OUT

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
	UE_LOG(LogTemp, Warning, TEXT("GRABBER reporting for duty!!"))
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPL;
	FRotator PlayerViewPR;

	//Getplayer view point tick
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPL, 
		OUT PlayerViewPR);

	//Ray casting to reach distance
	//UE_LOG(LogTemp, Warning, TEXT("Loc: %s, Pos: %s"),
	//	*PlayerViewPL.ToString(),
	//	*PlayerViewPR.ToString())
	
	float Reach = 200;
	FVector LineTraceEnd = PlayerViewPL + (PlayerViewPR.Vector() * Reach);

	DrawDebugLine(
		GetWorld(),
		PlayerViewPL,
		LineTraceEnd,
		FColor(255, 0 ,0),
		false,
		0.f,
		0.f,
		1.f
	);


	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	FHitResult HitResult;

	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		PlayerViewPL,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters);

	AActor* ActorHit = HitResult.GetActor();
	
	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("You hit %s"), *(ActorHit->GetName()))
	}

}

