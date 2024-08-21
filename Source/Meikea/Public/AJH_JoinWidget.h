// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AJH_JoinWidget.generated.h"

/**
 * 
 */
UCLASS()
class MEIKEA_API UAJH_JoinWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UEditableText* edit_JoinId;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UEditableText* edit_JoinPW;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BT_Joinsend;
	void OnMyClickMakeIDRequest();
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	class UButton* BT_Cancel;
	
	UPROPERTY()
	class AAJH_HttpPracticeActor* httpReqActor;

};
