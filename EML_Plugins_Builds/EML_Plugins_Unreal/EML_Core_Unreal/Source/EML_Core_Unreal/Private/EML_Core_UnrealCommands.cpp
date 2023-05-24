// Copyright Epic Games, Inc. All Rights Reserved.

#include "EML_Core_UnrealCommands.h"

#define LOCTEXT_NAMESPACE "FEML_Core_UnrealModule"

void FEML_Core_UnrealCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "EML_Core_Unreal", "Bring up EML_Core_Unreal window", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(GenerateEMLProjectStructure, "Generate EML Project Structure", "Generates folders and files required for Emerging Media Lab UBC projects.", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(CodingStyleguide, "EML Coding Styleguide", "Read more about the coding styleguide for Emerging Media Lab UBC Projects.", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(ContactInformation, "Contact Information", "Click here to see how you can contact us directly.", EUserInterfaceActionType::Button, FInputChord());
	
}

#undef LOCTEXT_NAMESPACE
