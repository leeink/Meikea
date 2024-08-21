// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AJH_HttpBasicWidget.generated.h"

/**
 * 
 */
UCLASS()
class MEIKEA_API UAJH_HttpBasicWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY()
	class AAJH_HttpPracticeActor* httpActor;
	UPROPERTY()
	class AMNGameMode* httpGameMode;

	// ----------------------------통신----------------------------------------
	// ------------서버 통신 버튼--------------------
	UPROPERTY(meta=(BindWidget))
	class UButton* buttonGetWebImage;
	UPROPERTY(meta=(BindWidget))
	class UButton* buttonBackBasicMenu;
	UPROPERTY(meta=(BindWidget))
	class UWidgetSwitcher* widgetSwitching;

	// ------------웹 이미지--------------
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	class UImage* webImage;
	UFUNCTION()
	void OnMyClickGetWebImage();
	UFUNCTION()
	void OnMyClickBackBasicMenu();

	void SetWebImage(class UTexture2D* newTexture);

	void SetHttpActor(class AAJH_HttpPracticeActor* actor);

	FString ServerURL = "http://mtvs.helloworldlabs.kr:7771/api/json";

	FString WebImageURL = "https://t1.daumcdn.net/news/202105/25/koreadognews/20210525045023050wquu.jpg";

	//---------------------------------------로컬---------------------------------- 
	// ----첫번째 가구 UI 버튼--------
	UPROPERTY(meta = (BindWidget))
	class UButton* BT_firstButton;
	UFUNCTION()
	void OnMyClickFirstButton();
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AActor> firstFurnitureFactory;

	void MouseCusorPosition();

};
