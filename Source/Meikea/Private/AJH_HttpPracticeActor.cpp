// Fill out your copyright notice in the Description page of Project Settings.


#include "AJH_HttpPracticeActor.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "ImageUtils.h"
#include "AJH_HttpBasicWidget.h"
#include "JsonParseLib.h"
#include "AJH_JoinWidget.h"
#include "AJH_LoginWidget.h"
#include "Kismet/GameplayStatics.h"

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

	//// UI를 생성해서 기억하고싶다.
	//httpUI = Cast<UAJH_HttpBasicWidget>(CreateWidget(GetWorld(), HttpUIFactory));
	//if (httpUI)
	//{
	//	httpUI->AddToViewport();
	//	httpUI->SetHttpActor(this);
	//}

	loginUI = Cast<UAJH_LoginWidget>(CreateWidget(GetWorld(), HttpUIFactory));
	if (loginUI)
	{
		loginUI->AddToViewport();
		loginUI->SetHttpActor(this);
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

void AAJH_HttpPracticeActor::POSTMakeIDRequest(const FString url, const FString name, const FString id, const FString pw)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("nickName", name);
	RequestObj->SetStringField("userName", id);
	RequestObj->SetStringField("password", pw);

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	UE_LOG(LogTemp, Warning, TEXT("pass : %s"), *pw);
	Request->SetURL("http://192.168.155.12:8080/regist");
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	UE_LOG(LogTemp, Warning, TEXT("RequestBody : %s"), *RequestBody);
	Request->SetContentAsString(RequestBody);
	Request->OnProcessRequestComplete().BindUObject(this, &AAJH_HttpPracticeActor::OnPostData);
	Request->ProcessRequest();
}

void AAJH_HttpPracticeActor::OnPostData(TSharedPtr<IHttpRequest> Request, TSharedPtr<IHttpResponse> Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		UE_LOG(LogTemp, Warning, TEXT("Successed SingIn : %s"), *Response->GetContentAsString());
		// Response 값 Parsing
		FString res = Response->GetContentAsString();
		FString parsedData = UJsonParseLib::JsonParse(res);

		if (parsedData.Contains("null")) 
		{
			return;
		}
		else
		{
			// 로그인 실패
			UE_LOG(LogTemp, Warning, TEXT("Signin Failed %s"), *parsedData);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed"));


	}
}

void AAJH_HttpPracticeActor::POSTVerifyIDRequest(const FString url, const FString id, const FString pw)
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("userName", id);
	RequestObj->SetStringField("password", pw);

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->SetURL("http://192.168.155.12:8080/login");
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	UE_LOG(LogTemp, Warning, TEXT("RequestBody : %s"), *RequestBody);
	Request->SetContentAsString(RequestBody);
	Request->OnProcessRequestComplete().BindUObject(this, &AAJH_HttpPracticeActor::OnPostVerifySignIn);
	Request->ProcessRequest();
}

void AAJH_HttpPracticeActor::OnPostVerifySignIn(TSharedPtr<IHttpRequest> Request, TSharedPtr<IHttpResponse> Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		// Response 값 Parsing
		FString res = Response->GetContentAsString();
		FString parsedData = UJsonParseLib::JsonParse(res);

		// 로그인 성공
		if (parsedData.Contains("null")) {
			UE_LOG(LogTemp, Warning, TEXT("Login Success %s"), *parsedData);
			UE_LOG(LogTemp, Warning, TEXT("Successed Verify Login: %s"), *Response->GetContentAsString());
			UGameplayStatics::OpenLevel(GetWorld(), FName("NewLevel"));
			return;
		}
		else
		{
			// 로그인 실패
			UE_LOG(LogTemp, Warning, TEXT("Login Failed %s"), *parsedData);
		}

	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed"));

	}
}

