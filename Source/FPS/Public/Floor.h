// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallActor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/CoreUObject/Public/UObject/Object.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/Public/TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "Floor.generated.h"

USTRUCT(BlueprintType)
struct FBallSpawnInfo
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		TArray<TSubclassOf<ABallActor>> actors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		TArray<AActor*> spawnedActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		int32 itemCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		float spawnRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		float destroyRadius;
};

UCLASS()
class FPS_API AFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ball")
		TArray<FBallSpawnInfo> BallSpawnInfos;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ball")
		TSubclassOf<AActor> TargetOriginClass;

	UPROPERTY(EditAnywhere, Category = "Ball")
		int32 TotalObject;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trace")
		float RadarDistance = 5000.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trace")
		float RadarHeight = 500.f;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Room, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* Floor;

	AActor* target;
	void SpawnActor(FBallSpawnInfo& si);

	FTimerHandle RadarSweepTimerHandle;
	FTimerHandle hSpawnTimer;

	UFUNCTION()
		void SpawnBall();

	UFUNCTION()
		void DestroyBall();
	
	UFUNCTION()
		void RadarRaycast();
	UFUNCTION()
		void RadarSweepTimer();
};
