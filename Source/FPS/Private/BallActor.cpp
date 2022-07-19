// Fill out your copyright notice in the Description page of Project Settings.


#include "BallActor.h"
#include "Floor.h"
#include "Components/SphereComponent.h"

// Sets default values
ABallActor::ABallActor()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("BallProjectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ABallActor::OnHit);

	RootComponent = CollisionComp;
}



void ABallActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		//OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		/*OtherActor->Destroy(true, true);
		Destroy();
		AFloor flor;
		flor.TotalObject++;*/
		Destroy();
		UE_LOG(LogTemp, Log, TEXT("Destroyed %i"));

	}
}

