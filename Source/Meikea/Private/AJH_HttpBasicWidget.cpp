// Fill out your copyright notice in the Description page of Project Settings.


#include "AJH_HttpBasicWidget.h"
#include "Components/Image.h"
#include "AJH_HttpPracticeActor.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

void UAJH_HttpBasicWidget::NativeConstruct()
{
	/*buttonGetWebImage->OnClicked.AddDynamic(this, &UAJH_HttpBasicWidget::OnMyClickGetWebImage);
	buttonBackBasicMenu->OnClicked.AddDynamic(this, &UAJH_HttpBasicWidget::OnMyClickBackBasicMenu);*/
}

void UAJH_HttpBasicWidget::OnMyClickGetWebImage()
{
	widgetSwitching->SetActiveWidgetIndex(1);
	httpActor->ReqGetWebImage(WebImageURL);
}

void UAJH_HttpBasicWidget::OnMyClickBackBasicMenu()
{
	widgetSwitching->SetActiveWidgetIndex(0);
}

void UAJH_HttpBasicWidget::SetWebImage(UTexture2D* newTexture)
{
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
