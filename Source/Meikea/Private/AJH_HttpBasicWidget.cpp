// Fill out your copyright notice in the Description page of Project Settings.


#include "AJH_HttpBasicWidget.h"
#include "Components/Image.h"
#include "AJH_HttpPracticeActor.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "MNGameMode.h"
#include "Kismet/GameplayStatics.h"

void UAJH_HttpBasicWidget::NativeConstruct()
{
	buttonGetWebImage->OnClicked.AddDynamic(this, &UAJH_HttpBasicWidget::OnMyClickGetWebImage);
	httpGameMode = Cast<AMNGameMode>(UGameplayStatics::GetGameMode(this));
}

void UAJH_HttpBasicWidget::OnMyClickGetWebImage()
{

	httpGameMode->ReqsendRT(WebImageURL);
	// UE_LOG(LogTemp, Warning, TEXT("Successed"));
}

void UAJH_HttpBasicWidget::OnMyClickBackBasicMenu()
{
	
}

void UAJH_HttpBasicWidget::SetWebImage(UTexture2D* newTexture)
{
	
	UE_LOG(LogTemp, Warning, TEXT("null"));


	webImage->SetBrushFromTexture(newTexture);
}

void UAJH_HttpBasicWidget::SetHttpActor(AAJH_HttpPracticeActor* actor)
{
	httpActor = actor;
}
// 첫번째 가구 UI 버튼
void UAJH_HttpBasicWidget::OnMyClickFirstButton()
{
	MouseCusorPosition();
}

void UAJH_HttpBasicWidget::MouseCusorPosition()
{
	FVector mouseWorldLocation;
	FVector mouseWorldDirection;
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	if (pc)
	{
		pc->DeprojectMousePositionToWorld(mouseWorldLocation, mouseWorldDirection);
	}
	FHitResult hitResult;
	FVector start = mouseWorldLocation;
	FVector end = start + (mouseWorldDirection * 10000.f);

	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECC_Visibility))
	{
		FVector spawnLocation = hitResult.Location;
		FRotator spawnRotation = FRotator::ZeroRotator;
		FActorSpawnParameters param;
		GetWorld()->SpawnActor<AActor>(firstFurnitureFactory, spawnLocation, spawnRotation, param);
	}
}
