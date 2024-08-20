// Fill out your copyright notice in the Description page of Project Settings.


#include "AJH_HttpPracticeActor.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "ImageUtils.h"
#include "AJH_HttpBasicWidget.h"

// Sets default values
AAJH_HttpPracticeActor::AAJH_HttpPracticeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAJH_HttpPracticeActor::BeginPlay()
{
	Super::BeginPlay();

	// UI�� �����ؼ� ����ϰ�ʹ�.
	httpUI = Cast<UAJH_HttpBasicWidget>(CreateWidget(GetWorld(), HttpUIFactory));
	if (httpUI)
	{
		httpUI->AddToViewport();
		httpUI->SetHttpActor(this);
	}

	auto* pc = GetWorld()->GetFirstPlayerController();
	pc->SetShowMouseCursor(true);
	
}

// Called every frame
void AAJH_HttpPracticeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAJH_HttpPracticeActor::ReqGetWebImage(FString url)
{
	// Http ����� ����
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

	// ��û�� ������ ����
	req->SetURL(url);
	req->SetVerb(TEXT("GET"));
	req->SetHeader(TEXT("content-type"), TEXT("image/jpeg"));

	// ������� �Լ��� ����
	req->OnProcessRequestComplete().BindUObject(this, &AAJH_HttpPracticeActor::OnResGetWebImage);
	// ������ ��û

	req->ProcessRequest();
}

void AAJH_HttpPracticeActor::OnResGetWebImage(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		TArray<uint8> data = Response->GetContent();
		FString fileServerURL = "http://mtvs.helloworldlabs.kr:7771/api/byte";
		ReqGetWebImageToServer(fileServerURL, data);
	}
	else {
		// ����
		UE_LOG(LogTemp, Warning, TEXT("OnResGetWebImage Failed..."));
	}
}

void AAJH_HttpPracticeActor::ReqGetWebImageToServer(FString url, TArray<uint8> resource)
{
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

	// ��û�� ������ ����
	req->SetURL(url);
	req->SetVerb(TEXT("POST"));
	req->SetHeader(TEXT("content-type"), TEXT("application/octet-stream"));
	req->SetContent(resource);

	// ������� �Լ��� ����
	req->OnProcessRequestComplete().BindUObject(this, &AAJH_HttpPracticeActor::OnResGetWebImageFromServer);
	// ������ ��û

	req->ProcessRequest();
}

void AAJH_HttpPracticeActor::OnResGetWebImageFromServer(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		TArray<uint8> data = Response->GetContent();
		FString imagePath = FPaths::ProjectPersistentDownloadDir() + "/Cat.jpg";
		FFileHelper::SaveArrayToFile(data, *imagePath);
		UTexture2D* realTexture = FImageUtils::ImportBufferAsTexture2D(data);
		httpUI->SetWebImage(realTexture);
	}
	else {
		// ����
		UE_LOG(LogTemp, Warning, TEXT("OnResGetWebImageFromServer Failed..."));
	}
}

