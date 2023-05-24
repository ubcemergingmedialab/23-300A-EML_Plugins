// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "AssetToolsModule.h"
#include "EngineUtils.h"
#include "UObject/Object.h"
#include "UObject/Interface.h"
#include "UObject/ScriptMacros.h"
#include "Engine/Blueprint.h"
#include "Engine/BlueprintGeneratedClass.h"


class FToolBarBuilder;
class FMenuBuilder;


class FEML_Core_UnrealModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	
private:

	void RegisterMenus();
	void RegisterEMLMenus();
	
	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

	//EML Actions
	void GenerateEMLProjectStructure();
	void CodingStyleguide();
	void ContactInformation();
	void CreateGameInstance();
	void SetGameInstanceToEMLGameInstance();


private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
