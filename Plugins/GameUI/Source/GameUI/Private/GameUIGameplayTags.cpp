// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUIGameplayTags.h"

namespace GameUIGameplayTags
{
	// Widget Stack
	UE_DEFINE_GAMEPLAY_TAG(GameUI_WidgetStack_Modal,"GameUI.WidgetStack.Modal")
	UE_DEFINE_GAMEPLAY_TAG(GameUI_WidgetStack_GameMenu,"GameUI.WidgetStack.GameMenu")
	UE_DEFINE_GAMEPLAY_TAG(GameUI_WidgetStack_GameHud,"GameUI.WidgetStack.GameHud")
	UE_DEFINE_GAMEPLAY_TAG(GameUI_WidgetStack_FrontEnd,"GameUI.WidgetStack.FrontEnd")

	// Widget
	UE_DEFINE_GAMEPLAY_TAG(GameUI_Widget_PressAnyKey,"GameUI.Widget.PressAnyKey")
	UE_DEFINE_GAMEPLAY_TAG(GameUI_Widget_MainMenu,"GameUI.Widget.MainMenu")
	UE_DEFINE_GAMEPLAY_TAG(GameUI_Widget_ConfirmScreen,"GameUI.Widget.ConfirmScreen")
	UE_DEFINE_GAMEPLAY_TAG(GameUI_Widget_OptionsScreen,"GameUI.Widget.OptionsScreen")
}