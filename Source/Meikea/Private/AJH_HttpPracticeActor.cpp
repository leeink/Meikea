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

	// UI를 생성해서 기억하고싶다.
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
	// Http 모듈을 생성
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

	// 요청할 정보를 설정
	req->SetURL(url);
	req->SetVerb(TEXT("GET"));
	req->SetHeader(TEXT("content-type"), TEXT("image/jpeg"));

	// 응답받을 함수를 연결
	req->OnProcessRequestComplete().BindUObject(this, &AAJH_HttpPracticeActor::OnResGetWebImage);
	// 서버에 요청

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
		// 실패
		UE_LOG(LogTemp, Warning, TEXT("OnResGetWebImage Failed..."));
	}
}

void AAJH_HttpPracticeActor::ReqGetWebImageToServer(FString url, TArray<uint8> resource)
{
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

	// 요청할 정보를 설정
	req->SetURL(url);
	req->SetVerb(TEXT("POST"));
	req->SetHeader(TEXT("content-type"), TEXT("application/octet-stream"));
	req->SetContent(resource);

	// 응답받을 함수를 연결
	req->OnProcessRequestComplete().BindUObject(this, &AAJH_HttpPracticeActor::OnResGetWebImageFromServer);
	// 서버에 요청

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
		// 실패
		UE_LOG(LogTemp, Warning, TEXT("OnResGetWebImageFromServer Failed..."));
	}
}

