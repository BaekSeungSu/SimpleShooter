// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if(AIBehavior != nullptr){
        RunBehaviorTree(AIBehavior);

        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLoctaion"), PlayerPawn->GetActorLocation());
    }

}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
}
