// Fill out your copyright notice in the Description page of Project Settings.


#include "AJH_JoinWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "AJH_HttpPracticeActor.h"

void UAJH_JoinWidget::NativeConstruct()
{
	BT_Joinsend->OnClicked.AddDynamic(this, &UAJH_JoinWidget::OnMyClickMakeIDRequest);
	BT_Cancel->OnClicked.AddDynamic(this, &UAJH_JoinWidget::OnMyClickCancel);
}

void UAJH_JoinWidget::OnMyClickMakeIDRequest()
{
	if (!edit_JoinName->GetText().IsEmpty() && !edit_JoinId->GetText().IsEmpty() && !edit_JoinPW->GetText().IsEmpty() && httpReqActor != nullptr)
	{
		FString fullURL;
		fullURL = "http://192.168.155.12:8080/regist";

		httpReqActor->POSTMakeIDRequest(fullURL, edit_JoinName->GetText().ToString(), edit_JoinId->GetText().ToString(), edit_JoinPW->GetText().ToString());
		UE_LOG(LogTemp, Warning, TEXT("Send Request! name : %s, id : %s, pw : %s"), *edit_JoinName->GetText().ToString(), *edit_JoinId->GetText().ToString(), *edit_JoinPW->GetText().ToString());
		UE_LOG(LogTemp, Warning, TEXT("%s"), *fullURL);
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't Send Request! : %d, %d, %d"), edit_JoinName->GetText().IsEmpty(), edit_JoinId->GetText().IsEmpty(), edit_JoinPW->GetText().IsEmpty());
		if (httpReqActor == nullptr) UE_LOG(LogTemp, Warning, TEXT("Null"));
	}

	SetVisibility(ESlateVisibility::Hidden);
}

void UAJH_JoinWidget::OnMyClickCancel()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UAJH_JoinWidget::SetHttpActor(class AAJH_HttpPracticeActor* actor)
{
	httpReqActor = actor;
}
