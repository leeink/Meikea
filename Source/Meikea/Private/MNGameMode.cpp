// Fill out your copyright notice in the Description page of Project Settings.


#include "MNGameMode.h"
#include "HttpModule.h"
#include "AJH_HttpBasicWidget.h"
#include "ImageUtils.h"
#include "Engine/TextureRenderTarget2D.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "JsonParseLib.h"


//void AMNGameMode::ReqGetImage(FString url)
//{
//	// Http 모듈을 생성
//	FHttpModule& httpModule = FHttpModule::Get();
//	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();
//
//	// 요청할 정보를 설정
//	req->SetURL(url);
//	req->SetVerb(TEXT("GET"));
//	req->SetHeader(TEXT("content-type"), TEXT("image/jpeg"));
//
//	// 응답받을 함수를 연결
//	req->OnProcessRequestComplete().BindUObject(this, &AMNGameMode::OnResGetImage);
//	// 서버에 요청
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
//		// 실패
//		UE_LOG(LogTemp, Warning, TEXT("OnResGetWebImage Failed..."));
//	}
//}

//void AMNGameMode::ReqGetImageToServer(FString url, TArray<uint8> resource)
//{
//	
//	FHttpModule& httpModule = FHttpModule::Get();
//	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();
//
//	// 요청할 정보를 설정
//	req->SetURL(url);
//	req->SetVerb(TEXT("POST"));
//	req->SetHeader(TEXT("content-type"), TEXT("application/octet-stream"));
//	req->SetContent(resource);
//
//	// 응답받을 함수를 연결
//	req->OnProcessRequestComplete().BindUObject(this, &AMNGameMode::OnResGetImageFromServer);
//	// 서버에 요청
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
//		// 실패
//		UE_LOG(LogTemp, Warning, TEXT("OnResGetWebImageFromServer Failed..."));
//	}
//}

void AMNGameMode::ReqImage(FString url)
{
	UE_LOG(LogTemp, Warning, TEXT("123"));
	// Http 모듈을 생성
	FHttpModule& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

	// 요청할 정보를 설정
	req->SetURL("http://192.168.1.88:8080/image");
	req->SetVerb(TEXT("GET"));
	req->SetHeader(TEXT("content-type"), TEXT("image/jpeg"));

	// 응답받을 함수를 연결
	req->OnProcessRequestComplete().BindUObject(this, &AMNGameMode::OnResImage);
	// 서버에 요청

	req->ProcessRequest();
}

void AMNGameMode::OnResImage(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		//FString fileServerURL = "http://192.168.1.88:8080/image";
		// Response 값 Parsing
		FString res = Response->GetContentAsString();
		FString parsedData = UJsonParseLib::MeikeaJsonParse(res);

		if (parsedData.Contains("null"))
		{
			UE_LOG(LogTemp, Warning, TEXT("Meikea Success %s"), *parsedData);
			UE_LOG(LogTemp, Warning, TEXT("Successed Res: %s"), *Response->GetContentAsString());


		}
	}
	else {
		// 실패
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

	req->SetURL("http://192.168.1.88:8080/image");
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
		UE_LOG(LogTemp, Warning, TEXT("321321"));
		//// 서버에서 응답받은 Content-Type 헤더를 기반으로 이미지 포맷 설정
		FString ContentType = Response->GetHeader("Content-Type");
		EImageFormat ImageFormat = EImageFormat::Invalid;

		if (ContentType == "image/jpeg")
		{
			ImageFormat = EImageFormat::JPEG;
		}
		else if (ContentType == "image/png")
		{
			ImageFormat = EImageFormat::PNG;
		}

		if (ImageFormat == EImageFormat::Invalid)
		{
			UE_LOG(LogTemp, Warning, TEXT("Unsupported image format."));
			return;
		}

		FString fileServerURL = "http://192.168.1.88:8080/image/upload";
		TArray<uint8> data = Response->GetContent();
		UTexture2D* texture = LoadTextureFromData(data, ImageFormat);
		FString imagePath = FPaths::ProjectPersistentDownloadDir() + "/Render.jpg";
		FFileHelper::SaveArrayToFile(data, *imagePath);
		realTexture = texture;
		httpUI->SetWebImage(realTexture);
		//GetWorld()->GetTimerManager().SetTimer(serverHandle, this, &AMNGameMode::ServerTime, 10.0f, false, 10.0f);

		// Response 값 Parsing
		/*FString res = Response->GetContentAsString();
		FString parsedData = UJsonParseLib::MeikeaJsonParse(res);

		if (parsedData.Contains("null"))
		{
			UE_LOG(LogTemp, Warning, TEXT("Meikea Success %s"), *parsedData);
			UE_LOG(LogTemp, Warning, TEXT("Successed Res: %s"), *Response->GetContentAsString());


		}*/
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed..."));
	}
}

void AMNGameMode::ServerTime()
{
	
}

UTexture2D* AMNGameMode::LoadTextureFromData(const TArray<uint8>& ImageData, EImageFormat ImageFormat)
{
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(ImageFormat);

	if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(ImageData.GetData(), ImageData.Num()))
	{
		TArray<uint8> UncompressedData;
		if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedData))
		{
			UTexture2D* Texture = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight());
			if (!Texture)
			{
				return nullptr;
			}

			void* TextureData = Texture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			FMemory::Memcpy(TextureData, UncompressedData.GetData(), UncompressedData.Num());
			Texture->GetPlatformData()->Mips[0].BulkData.Unlock();

			Texture->UpdateResource();

			return Texture;
		}
	}

	UE_LOG(LogTemp, Error, TEXT("Failed to load texture from data."));
	return nullptr;
}
