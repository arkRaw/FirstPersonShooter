// Copyright @ArvindRawat

#pragma once

#include "CoreMinimal.h"
#include "S05_TestingGroundsGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

class ANavMeshBoundsVolume;
class UActorPool;

/**
 * 
 */
UCLASS()
class S05_TESTINGGROUNDS_API AInfiniteTerrainGameMode : public AS05_TestingGroundsGameMode
{
	GENERATED_BODY()

public:

	AInfiniteTerrainGameMode();

	UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
	void PopulateBoundsVolumePool();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pool")
	UActorPool* NavMeshBoundsVolumePool = nullptr;

private:

	void AddToPool(ANavMeshBoundsVolume* VolumeToAdd);
};