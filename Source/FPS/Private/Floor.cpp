// Fill out your copyright notice in the Description page of Project Settings.


#include "Floor.h"


// Sets default values
AFloor::AFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorComponent"));
	SetRootComponent(Floor);

}

// Called when the game starts or when spawned
void AFloor::BeginPlay()
{
	Super::BeginPlay();
	
	RadarSweepTimer();
	
	
}

// Called every frame
void AFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TotalObject == 0)
		SpawnBall();
	if (TotalObject == 10)
		DestroyBall();
	
}

void AFloor::SpawnActor(FBallSpawnInfo& si)
{
	float XCoordinate = FMath::FRandRange(-1000.f, 1000.f);
	float YCoordinate = FMath::FRandRange(-1000.f, 1000.f);

	float Yaw = FMath::FRandRange(0.f, 360.f);

	if (si.actors.Num()) {
		UClass* c = si.actors[0];
		if (c)
		{
			FVector Location(XCoordinate, YCoordinate, 300.f);
			FRotator Rotatoin(0.f, Yaw, 0.f);
			FActorSpawnParameters p;
			p.Owner = this;

			AActor* a = GetWorld()->SpawnActor(si.actors[0], &Location, &Rotatoin, p);

			int idx = si.spawnedActors.Add(a);

			UE_LOG(LogTemp, Log, TEXT("Spawned %p %d %s"), a, a->GetUniqueID(), *a->GetFName().ToString());
		}
	}
}

void AFloor::SpawnBall()
{
	for (auto& ins : BallSpawnInfos) {

		for (int i = 0; i < ins.spawnedActors.Num(); i++) {
			AActor* a = ins.spawnedActors[i];
		}

		if (ins.spawnedActors.Num() < ins.itemCount) {
			SpawnActor(ins);
		}
	}
	}

void AFloor::DestroyBall()
{
	TArray<AActor*> deletes;
	for (auto& ins : BallSpawnInfos) {

		for (int i = 0; i < ins.spawnedActors.Num(); i++) {
			AActor* a = ins.spawnedActors[i];
				deletes.Add(a);

				a->Destroy();
				UE_LOG(LogTemp, Log, TEXT("Destroyed %p %d %s"), a, a->GetUniqueID(), *a->GetFName().ToString());
		}
		ins.itemCount = 20;
	}
	TotalObject = 0;
	
}
	


void AFloor::RadarRaycast()
{
	//hold a reference to all the objects returned from our radar sweep
	TArray<FHitResult> RadarHitsArray;

	//use the ship location as the end location on the sphere, also set the height to be the radar height.
	FVector ShipLocation = GetActorLocation();
	//ShipLocation.Z += RadarHeight;

	FVector EndLocation = FVector(ShipLocation.X + 45.f, ShipLocation.Y, ShipLocation.Z);

	//Collision Shape is Spherical and range is 1km
	FCollisionShape RadarSphere = FCollisionShape::MakeSphere(RadarDistance);

	//Debug lines
	DrawDebugSphere(GetWorld(), ShipLocation, RadarDistance, 6, FColor::Yellow, true, 3.0f, 0U, 0.5f);

	//Now see what it hits	
	check(GetWorld() != NULL);
	bool isHit = GetWorld()->SweepMultiByChannel(RadarHitsArray,
		ShipLocation,
		ShipLocation,
		FQuat::Identity,
		ECC_WorldStatic,
		RadarSphere);
	TotalObject = 0;
	if (isHit)
	{
		
		for (auto& Hit : RadarHitsArray)
		{
			
			AActor* actor = Cast<AActor>(Hit.Actor);
			
			if (GEngine)
			{
				for (auto& ins : BallSpawnInfos)
					for (int i = 0; i < ins.spawnedActors.Num(); i++)
					{
						AActor* a = ins.spawnedActors[i];

						if (actor && *actor->GetName() == a->GetFName())
						{
							TotalObject++;
						}
						
					}
			}
			
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("TotalObjekt  %i"), TotalObject);
	
}


void AFloor::RadarSweepTimer()
{
	GetWorld()->GetTimerManager().SetTimer(RadarSweepTimerHandle, this, &AFloor::RadarRaycast, 2.f, true, 0.5f);
}

