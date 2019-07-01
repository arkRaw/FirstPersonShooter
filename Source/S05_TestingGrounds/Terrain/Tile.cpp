// Copyright @ArvindRawat


#include "Tile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "../ActorPool.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


void ATile::SetPool(UActorPool * InPool)
{
	Pool = InPool;

	PositionNavMeshBoundsVolume();
}

void ATile::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = Pool->Checkout();
	if (NavMeshBoundsVolume == nullptr)
	{
		return;
	}
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation());
}




// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

	MinExtent = FVector(0.f, -2000.f, 0.f);

	MaxExtent = FVector(4000.f, 2000.f, 0.f);


}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (NavMeshBoundsVolume != nullptr)
	{
		Pool->Return(NavMeshBoundsVolume);
	}
	
	NavMeshBoundsVolume = nullptr;
}


void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn, int32 MaxSpawn, float Radius, float MinScale, float MaxScale)
{
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	for (size_t i = 0; i < NumberToSpawn; ++i)
	{
		FVector SpawnPoint;
		
		float RandomScale = FMath::RandRange(MinScale, MaxScale);
		bool bFound = FindEmptyLocation(SpawnPoint, Radius*RandomScale);

		if (bFound)
		{
			float RandomRotation = FMath::RandRange(-180.f, 180.f);
			
			PlaceActor(ToSpawn, SpawnPoint, RandomRotation, RandomScale);
		}
	}
}


void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float Rotation, float Scale)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn, SpawnPoint, SpawnPoint.Rotation());
	Spawned->SetActorRelativeLocation(SpawnPoint);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRotation(FRotator(0, Rotation, 0));
	Spawned->SetActorScale3D(FVector(Scale));
}

bool ATile::FindEmptyLocation(FVector& OutLocation ,float Radius)
{
	FBox Bounds(MinExtent, MaxExtent);

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

	return !bHasHit;
}


// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
