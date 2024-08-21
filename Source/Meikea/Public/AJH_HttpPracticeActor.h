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

	// �������̽��� ���� UI
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> HttpUIFactory;

	UPROPERTY()
	class UAJH_HttpBasicWidget* httpUI;

	// ---------------------- �� �̹��� ��ư �̺�Ʈ start---------------------------
	// ButtonGetWebImage�� ������ �� ��û�� �Լ�
	void ReqGetWebImage(FString url);
	// ������� �Լ�
	void OnResGetWebImage(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	// ���̹����� �鿣�� ������ �۽�
	void ReqGetWebImageToServer(FString url, TArray<uint8> resource);
	// ���̹����� �鿣�� �������� ����
	void OnResGetWebImageFromServer(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	//-----------------------�� �̹��� ��ư �̺�Ʈ end---------------------------------

	//------------------------------- ȸ�� ����-----------------------------

	void POSTMakeIDRequest(const FString url, const FString id, const FString pw);
	void OnPostData(TSharedPtr<IHttpRequest> Request, TSharedPtr<IHttpResponse> Response, bool bConnectedSuccessfully);

};
