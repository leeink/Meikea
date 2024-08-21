// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "MNGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MEIKEA_API AMNGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// Button �� ������ �� ��û�� �Լ�
	//void ReqGetImage(FString url);
	//// ������� �Լ�
	//void OnResGetImage(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	// ���̹����� �鿣�� ������ �۽�
	//void ReqGetImageToServer(FString url, TArray<uint8> resource);
	//// ���̹����� �鿣�� �������� ����
	//void OnResGetImageFromServer(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	UPROPERTY()
	class UAJH_HttpBasicWidget* httpUI;

	void ReqImage(FString url);
	void OnResImage(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	void ReqsendRT(FString url);
	void OnResSendRT(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	UPROPERTY(EditDefaultsOnly)
	class UTextureRenderTarget2D* RT;
};
