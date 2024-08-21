// Fill out your copyright notice in the Description page of Project Settings.


#include "AJH_JoinWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "AJH_HttpPracticeActor.h"

void UAJH_JoinWidget::NativeConstruct()
{
	BT_Joinsend->OnClicked.AddDynamic(this, &UAJH_JoinWidget::OnMyClickMakeIDRequest);
}

void UAJH_JoinWidget::OnMyClickMakeIDRequest()
{
	if (!edit_JoinId->GetText().IsEmpty() && !edit_JoinPW->GetText().IsEmpty() && httpReqActor != nullptr)
	{
		FString fullURL;
		fullURL = " ";

		httpReqActor->POSTMakeIDRequest(fullURL, edit_JoinId->GetText().ToString(), edit_JoinPW->GetText().ToString());
		UE_LOG(LogTemp, Warning, TEXT("Send Request! id : %s, pw : %s"), *edit_JoinId->GetText().ToString(), *edit_JoinPW->GetText().ToString());
		UE_LOG(LogTemp, Warning, TEXT("%s"), *fullURL);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't Send Request! : %d, %d"), edit_JoinId->GetText().IsEmpty(), edit_JoinPW->GetText().IsEmpty());
		if (httpReqActor == nullptr) UE_LOG(LogTemp, Warning, TEXT("Null"));
	}
}
