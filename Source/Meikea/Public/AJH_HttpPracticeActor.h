// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "AJH_HttpPracticeActor.generated.h"

UCLASS()
class MEIKEA_API AAJH_HttpPracticeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAJH_HttpPracticeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 인터페이스를 위한 UI
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> HttpUIFactory;

	UPROPERTY()
	class UAJH_HttpBasicWidget* httpUI;

	// ---------------------- 웹 이미지 버튼 이벤트 start---------------------------
	// ButtonGetWebImage를 눌렀을 때 요청할 함수
	void ReqGetWebImage(FString url);
	// 응답받을 함수
	void OnResGetWebImage(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	// 웹이미지를 백엔드 서버로 송신
	void ReqGetWebImageToServer(FString url, TArray<uint8> resource);
	// 웹이미지를 백엔드 서버에서 수신
	void OnResGetWebImageFromServer(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	//-----------------------웹 이미지 버튼 이벤트 end---------------------------------

	//------------------------------- 회원 가입-----------------------------

	void POSTMakeIDRequest(const FString url, const FString id, const FString pw);
	void OnPostData(TSharedPtr<IHttpRequest> Request, TSharedPtr<IHttpResponse> Response, bool bConnectedSuccessfully);

};
