// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "EML_Core_UnrealStyle.h"

class FEML_Core_UnrealCommands : public TCommands<FEML_Core_UnrealCommands>
{
public:

	FEML_Core_UnrealCommands()
		: TCommands<FEML_Core_UnrealCommands>(TEXT("EML_Core_Unreal"), NSLOCTEXT("Contexts", "EML_Core_Unreal", "EML_Core_Unreal Plugin"), NAME_None, FEML_Core_UnrealStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
	TSharedPtr< FUICommandInfo > GenerateEMLProjectStructure;
	TSharedPtr< FUICommandInfo > CodingStyleguide;
	TSharedPtr< FUICommandInfo > ContactInformation;
};