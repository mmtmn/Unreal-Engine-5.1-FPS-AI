#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSAIController.h"

class AFPSCharacter;

class FPSAI : public AActor
{
    GENERATED_BODY()

public:
    FPSAI();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere)
    AFPSCharacter* TargetEnemy;

    UPROPERTY(EditAnywhere)
    float MoveSpeed = 100.0f;

protected:
    UPROPERTY(VisibleAnywhere)
    UFPSAIController* AIController;
};

FPSAI::FPSAI()
{
    PrimaryActorTick.bCanEverTick = true;

    AIController = CreateDefaultSubobject<UFPSAIController>(TEXT("AIController"));
}

void FPSAI::BeginPlay()
{
    Super::BeginPlay();

    // Set the AI controller's target enemy to the one specified in the editor
    AIController->SetTargetEnemy(TargetEnemy);
}

void FPSAI::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Move towards the target enemy
    FVector MoveDirection = TargetEnemy->GetActorLocation() - GetActorLocation();
    MoveDirection.Normalize();
    SetActorLocation(GetActorLocation() + MoveDirection * MoveSpeed * DeltaTime);
}