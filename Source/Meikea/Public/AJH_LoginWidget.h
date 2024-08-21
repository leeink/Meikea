// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AJH_LoginWidget.generated.h"

/**
 * 
 */
UCLASS()
class MEIKEA_API UAJH_LoginWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* BT_JOIN;
	UFUNCTION()
	void OnMyClickJoinPage();

	UPROPERTY(meta = (BindWidget))
	class UButton* BT_Login;
	UFUNCTION()
	void OnMyClickLoginRequest();
	UPROPERTY(meta = (BindWidget))
	class UEditableText* edit_loginID;
	UPROPERTY(meta = (BindWidget))
	class UEditableText* edit_loginPW;

	UPROPERTY()
	class UAJH_JoinWidget* joinWidget;
	// 인터페이스를 위한 UI
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> joinPageFactory;

	UPROPERTY()
	class AAJH_HttpPracticeActor* httpReqActor;
	void SetHttpActor(class AAJH_HttpPracticeActor* actor);

};
