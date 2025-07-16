// Fill out your copyright notice in the Description page of Project Settings.


#include "UIGameModeBase.h"
#include "DevilMayCry/UI/HUD/TitleHUD.h"

AUIGameModeBase::AUIGameModeBase()
{
	HUDClass = ATitleHUD::StaticClass();
	DefaultPawnClass = nullptr;
	bUseSeamlessTravel = false; // 이걸 해야 Scene전환 시 게임모드 변경됨
}