// Copyright @ArvindRawat

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolRoute.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class S05_TESTINGGROUNDS_API UPatrolRoute : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditInstanceOnly, Category = "Patrol Route")
	TArray<AActor*> PatrolPoints;

public:	
	
	TArray<AActor*> GetPatrolPoints() const;
};
