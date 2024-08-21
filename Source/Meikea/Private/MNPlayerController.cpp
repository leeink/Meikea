// Fill out your copyright notice in the Description page of Project Settings.


#include "MNPlayerController.h"

#include "AJH_HttpBasicWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetInteractionComponent.h"

AMNPlayerController::AMNPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMNPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DefaultMappingContext is null when trying to add mapping context!"));
	}
}

void AMNPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SpawnActorClasses.Add(SpawnActorClass1);
	SpawnActorClasses.Add(SpawnActorClass2);
	SpawnActorClasses.Add(SpawnActorClass3);
	SpawnActorClasses.Add(SpawnActorClass4);
	SpawnActorClasses.Add(SpawnActorClass5);

	SelectActor = GetWorld() -> SpawnActor<AActor>(SpawnActorClasses[SelectIndex], FVector::ZeroVector, FRotator::ZeroRotator);

	bShowMouseCursor = true;
}

void AMNPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	bool bHit = GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, HitResult);
	
	if(bHit && bIsSelecting)
	{
		CursorLocation = HitResult.Location;
		SelectActor->SetActorLocation(CursorLocation + FVector(0.f, 0.f, 50.f));
	}
}

void AMNPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(IA_MouseLeftClick, ETriggerEvent::Started, this, &AMNPlayerController::OnMouseLeftClick);
	}
}

void AMNPlayerController::OnMouseLeftClick(const FInputActionValue& Value)
{
	// Handle the mouse left click input
	bool value = Value.Get<bool>();
	if (value && bIsSelecting)
	{
		GetWorld() -> SpawnActor<AActor>(SpawnActorClasses[SelectIndex], CursorLocation + FVector(0.f,0.f,50.f), FRotator::ZeroRotator);
		SetIsSelect(false);
	}
	else
	{
		// Do something else
	}
}

void AMNPlayerController::SetSelectIndex(int NewIndex)
{
	SelectIndex = NewIndex;
}

void AMNPlayerController::SetIsSelect(bool bNewSelecting)
{
	bIsSelecting = bNewSelecting;
	bShowMouseCursor = !bIsSelecting;
}

void AMNPlayerController::SetSelectActor()
{
	SelectActor = nullptr;

	SelectActor = GetWorld()->SpawnActor<AActor>(SpawnActorClasses[SelectIndex], FVector::ZeroVector, FRotator::ZeroRotator);
}