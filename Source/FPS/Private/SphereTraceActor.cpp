// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereTraceActor.h"

// Sets default values
ASphereTraceActor::ASphereTraceActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASphereTraceActor::BeginPlay()
{
	Super::BeginPlay();
	TArray<FHitResult> HitResults;

	FVector ActorLocation = GetActorLocation();

	FCollisionShape ColShape = FCollisionShape::MakeSphere(500.f);
	bool Hits = GetWorld()->SweepMultiByChannel(HitResults, ActorLocation, ActorLocation, FQuat::Identity, ECC_WorldStatic, ColShape);

	DrawDebugSphere(GetWorld(), ActorLocation, ColShape.GetSphereRadius(), 110, FColor::Orange, true);

	//
	int t = 0;
	if (Hits)
	{
		for (auto& Hit : HitResults)
		{
			if (GEngine)
			{

				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Hit Result: %s"),
					*Hit.Actor->GetName()));
				t++;
				UE_LOG(LogTemp, Log, TEXT("++++all!!!  %i"), t);
			}
		}
	}



}

// Called every frame
void ASphereTraceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

