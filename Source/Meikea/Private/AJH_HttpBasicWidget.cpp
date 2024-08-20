// Fill out your copyright notice in the Description page of Project Settings.


#include "AJH_HttpBasicWidget.h"
#include "Components/Image.h"
#include "AJH_HttpPracticeActor.h"
#include "Components/Button.h"

void UAJH_HttpBasicWidget::NativeConstruct()
{
	buttonGetWebImage->OnClicked.AddDynamic(this, &UAJH_HttpBasicWidget::OnMyClickGetWebImage);
}

void UAJH_HttpBasicWidget::OnMyClickGetWebImage()
{
	httpActor->ReqGetWebImage(WebImageURL);
}

void UAJH_HttpBasicWidget::SetWebImage(UTexture2D* newTexture)
{
	webImage->SetBrushFromTexture(newTexture);
}

void UAJH_HttpBasicWidget::SetHttpActor(AAJH_HttpPracticeActor* actor)
{
	httpActor = actor;
}
