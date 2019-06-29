// Copyright @ArvindRawat


#include "Tile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();


}


void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn,int32 MinSpawn,int32 MaxSpawn,float Radius)
{
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (size_t i = 0; i < NumberToSpawn; ++i)
	{
		FVector SpawnPoint;
		bool bFound = FindEmptyLocation(SpawnPoint, Radius);
		if (bFound)
		{
			PlaceActor(ToSpawn, SpawnPoint);
		}
	}
}


void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn, SpawnPoint, SpawnPoint.Rotation());
	Spawned->SetActorRelativeLocation(SpawnPoint);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
}

bool ATile::FindEmptyLocation(FVector& OutLocation ,float Radius)
{
	FVector Min(0.f, -2000.f, 0.f);
	FVector Max(4000.f, 2000.f, 0.f);
	FBox Bounds(Min, Max);

	const int MAX_ATTEMPTS = 100;

	for (size_t i = 0; i < MAX_ATTEMPTS; i++)
	{
		FVector CandidatePoint = FMath::RandPointInBox(Bounds);
		if (CanSpawnAtLocation(CandidatePoint,Radius))
		{
			OutLocation = CandidatePoint;
			return true;
		}
	}

	return false;
}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius)
{
	FHitResult HitResult;

	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);

	bool bHasHit = GetWorld()->SweepSingleByChannel
	(
		HitResult,
		GlobalLocation,
		GlobalLocation + 0.001f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius)
	);


	FColor ResultColor = bHasHit ? FColor::Red : FColor::Green;

	DrawDebugCapsule(GetWorld(), GlobalLocation, 0, Radius, FQuat::Identity, ResultColor, true, 100);
	return !bHasHit;
}


// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}