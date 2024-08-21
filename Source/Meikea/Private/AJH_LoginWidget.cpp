// Fill out your copyright notice in the Description page of Project Settings.


#include "AJH_LoginWidget.h"
#include "AJH_JoinWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "AJH_HttpPracticeActor.h"
#include "Kismet/GameplayStatics.h"

void UAJH_LoginWidget::NativeConstruct()
{
	BT_Login->OnClicked.AddDynamic(this, &UAJH_LoginWidget::OnMyClickLoginRequest);
}

void UAJH_LoginWidget::OnMyClickJoinPage()
{
	
}

void UAJH_LoginWidget::OnMyClickLoginRequest()
{
	if (!edit_loginID->GetText().IsEmpty() && !edit_loginPW->GetText().IsEmpty() && httpReqActor != nullptr)
	{
		FString fullURL;
		fullURL = "http://192.168.155.12:8080/login";

		httpReqActor->POSTVerifyIDRequest(fullURL, edit_loginID->GetText().ToString(), edit_loginPW->GetText().ToString());
		UE_LOG(LogTemp, Warning, TEXT("Send Request! id : %s, pw : %s"), *edit_loginID->GetText().ToString(), *edit_loginPW->GetText().ToString());
		UE_LOG(LogTemp, Warning, TEXT("%s"), *fullURL);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Clicked, But not work"));
	}
	// CreateWidget<UAJH_JoinWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->AddToViewport();

}

void UAJH_LoginWidget::SetHttpActor(class AAJH_HttpPracticeActor* actor)
{
	httpReqActor = actor;
}
