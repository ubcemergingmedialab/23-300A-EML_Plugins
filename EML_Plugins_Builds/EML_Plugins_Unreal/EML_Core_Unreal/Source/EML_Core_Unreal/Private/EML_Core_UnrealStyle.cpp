// Copyright Epic Games, Inc. All Rights Reserved.

#include "EML_Core_UnrealStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"


#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FEML_Core_UnrealStyle::StyleInstance = nullptr;

void FEML_Core_UnrealStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FEML_Core_UnrealStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FEML_Core_UnrealStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("EML_Core_UnrealStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FEML_Core_UnrealStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("EML_Core_UnrealStyle"));

	Style->SetContentRoot(IPluginManager::Get().FindPlugin("EML_Core_Unreal")->GetBaseDir() / TEXT("Resources"));

	//This is where icons are assigned for the different dropdown menus
	Style->Set("EML_Core_Unreal.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));

	return Style;
}

void FEML_Core_UnrealStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FEML_Core_UnrealStyle::Get()
{
	return *StyleInstance;
}
