// Copyright @ArvindRawat

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Mannequin.generated.h"

UCLASS()
class S05_TESTINGGROUNDS_API AMannequin : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

public:
	// Sets default values for this character's properties
	AMannequin();

	/** Gun class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<class AGun> GunBlueprint;

	/** Fires a projectile. */
	UFUNCTION(BlueprintCallable, Category = "Input")
	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	
	class AGun* Gun = nullptr;
};
