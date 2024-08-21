// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MNPlayerController.generated.h"

/**
 * 
 */

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class MEIKEA_API AMNPlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_MouseLeftClick;

	// Stat Variables
	UPROPERTY()
	AActor* SelectActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = SelectActor, meta = (AllowPrivateAccess = "true"))
	bool bIsSelecting = false;

	FVector CursorLocation;
	
	int SelectIndex = 0;

	// SpawnActorClasses
	UPROPERTY()
	TArray<TSubclassOf<AActor>> SpawnActorClasses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = SpawnActorClass, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> SpawnActorClass1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = SpawnActorClass, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> SpawnActorClass2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = SpawnActorClass, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> SpawnActorClass3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = SpawnActorClass, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> SpawnActorClass4;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = SpawnActorClass, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> SpawnActorClass5;

public:
	AMNPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

public:
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;

	void OnMouseLeftClick(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void SetSelectIndex(int NewIndex);
	
	UFUNCTION(BlueprintCallable)
	void SetIsSelect(bool NewIsSelecting);
	
	UFUNCTION(BlueprintCallable)
	void SetSelectActor();
};
