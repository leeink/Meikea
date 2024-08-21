// Fill out your copyright notice in the Description page of Project Settings.


#include "MNGameMode.h"
#include "HttpModule.h"
#include "AJH_HttpBasicWidget.h"
#include "ImageUtils.h"
#include "Engine/TextureRenderTarget2D.h"


//void AMNGameMode::ReqGetImage(FString url)
//{
//	// Http ����� ����
//	FHttpModule& httpModule = FHttpModule::Get();
//	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();
//
//	// ��û�� ������ ����
//	req->SetURL(url);
//	req->SetVerb(TEXT("GET"));
//	req->SetHeader(TEXT("content-type"), TEXT("image/jpeg"));
//
//	// ������� �Լ��� ����
//	req->OnProcessRequestComplete().BindUObject(this, &AMNGameMode::OnResGetImage);
//	// ������ ��û
//
//	req->ProcessRequest();
//}
//
//void AMNGameMode::OnResGetImage(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
//{
//	if (bConnectedSuccessfully)
//	{
//		TArray<uint8> data = Response->GetContent();
//		FString fileServerURL = "http://192.168.1.88:8080/image/upload";
//		ReqGetImageToServer(fileServerURL, data);
//	}
//	else {
//		// ����
//		UE_LOG(LogTemp, Warning, TEXT("OnResGetWebImage Failed..."));
//	}
//}

//void AMNGameMode::ReqGetImageToServer(FString url, TArray<uint8> resource)
//{
//	
//	FHttpModule& httpModule = FHttpModule::Get();
//	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();
//
//	// ��û�� ������ ����
//	req->SetURL(url);
//	req->SetVerb(TEXT("POST"));
//	req->SetHeader(TEXT("content-type"), TEXT("application/octet-stream"));
//	req->SetContent(resource);
//
//	// ������� �Լ��� ����
//	req->OnProcessRequestComplete().BindUObject(this, &AMNGameMode::OnResGetImageFromServer);
//	// ������ ��û
//
//	req->ProcessRequest();
//}
//
//void AMNGameMode::OnResGetImageFromServer(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
//{
//	if (bConnectedSuccessfully)
//	{
//		TArray<uint8> data = Response->GetContent();
//		FString imagePath = FPaths::ProjectPersistentDownloadDir();
//		FFileHelper::SaveArrayToFile(data, *imagePath);
//		UTexture2D* realTexture = FImageUtils::ImportBufferAsTexture2D(data);
//		httpUI->SetWebImage(realTexture);
//	}
//	else {
//		// ����
//		UE_LOG(LogTemp, Warning, TEXT("OnResGetWebImageFromServer Failed..."));
//	}
//}

void AMNGameMode::ReqImage(FString url)
{
	UE_LOG(LogTemp, Warning, TEXT("123"));
	// Http ����� ����
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

	// ��û�� ������ ����
	req->SetURL(url);
	req->SetVerb(TEXT("GET"));
	req->SetHeader(TEXT("content-type"), TEXT("image/jpeg"));

	// ������� �Լ��� ����
	req->OnProcessRequestComplete().BindUObject(this, &AMNGameMode::OnResImage);
	// ������ ��û

	req->ProcessRequest();
}

void AMNGameMode::OnResImage(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		//TArray<uint8> data = Response->GetContent();
		FString fileServerURL = "http://192.168.1.88:8080/image/upload";
		ReqsendRT(fileServerURL);
	}
	else {
		// ����
		UE_LOG(LogTemp, Warning, TEXT("OnResGetWebImage Failed..."));
	}
}

void AMNGameMode::ReqsendRT(FString url)
{
	UTextureRenderTarget2D* textRT = RT;
	
	FImage image;
	if (!FImageUtils::GetRenderTargetImage(textRT, image))
	{
		return;
	}

	TArray64<uint8> CompressedData;
	if(!FImageUtils::CompressImage(CompressedData, TEXT("JPEG"), image))
	{
		return;
	}

	FString imagePath = FPaths::ProjectPersistentDownloadDir() + "/Render.jpeg";
	FFileHelper::SaveArrayToFile(CompressedData, *imagePath);
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

	req->SetURL(url);
	req->SetVerb(TEXT("POST"));
	req->SetHeader(TEXT("content-type"), TEXT("application/octet-stream"));
	req->SetContent(TArray<uint8>(CompressedData));

	req->OnProcessRequestComplete().BindUObject(this, &AMNGameMode::OnResSendRT);

	req->ProcessRequest();

}

void AMNGameMode::OnResSendRT(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		TArray<uint8> data = Response->GetContent();
		FString imagePath = FPaths::ProjectPersistentDownloadDir() + "/Render.jpg";
		FFileHelper::SaveArrayToFile(data, *imagePath);
		UTexture2D* realTexture = FImageUtils::ImportBufferAsTexture2D(data);
		// httpUI->SetWebImage(realTexture);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed..."));
	}
}
