// Copyright Epic Games, Inc. All Rights Reserved.

#include "EML_Core_Unreal.h"
#include "EML_Core_UnrealStyle.h"
#include "EML_Core_UnrealCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "ObjectTools.h"
#include "AssetToolsModule.h"
#include "AssetRegistryModule.h"


#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Engine/Blueprint.h"
#include "Engine/BlueprintGeneratedClass.h"



static const FName EML_Core_UnrealTabName("EML_Core_Unreal");

#define LOCTEXT_NAMESPACE "FEML_Core_UnrealModule"

void FEML_Core_UnrealModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FEML_Core_UnrealStyle::Initialize();
	FEML_Core_UnrealStyle::ReloadTextures();

	FEML_Core_UnrealCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FEML_Core_UnrealCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FEML_Core_UnrealModule::PluginButtonClicked),
		FCanExecuteAction());

	PluginCommands->MapAction(
		FEML_Core_UnrealCommands::Get().GenerateEMLProjectStructure,
		FExecuteAction::CreateRaw(this, &FEML_Core_UnrealModule::GenerateEMLProjectStructure),
		FCanExecuteAction());

	PluginCommands->MapAction(
		FEML_Core_UnrealCommands::Get().CodingStandards,
		FExecuteAction::CreateRaw(this, &FEML_Core_UnrealModule::CodingStandards),
		FCanExecuteAction());

	PluginCommands->MapAction(
		FEML_Core_UnrealCommands::Get().ContactInformation,
		FExecuteAction::CreateRaw(this, &FEML_Core_UnrealModule::ContactInformation),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FEML_Core_UnrealModule::RegisterMenus));

	FEML_Core_UnrealModule::RegisterEMLMenus();

}

void FEML_Core_UnrealModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FEML_Core_UnrealStyle::Shutdown();

	FEML_Core_UnrealCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(EML_Core_UnrealTabName);
}

TSharedRef<SDockTab> FEML_Core_UnrealModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FEML_Core_UnrealModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("EML_Core_Unreal.cpp"))
	);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
			.Text(WidgetText)
		]
		];
}

void FEML_Core_UnrealModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(EML_Core_UnrealTabName);
}

void FEML_Core_UnrealModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);
}

/// <summary>
/// Registering the EML menu to the main menu
/// </summary>
void FEML_Core_UnrealModule::RegisterEMLMenus()
{
	// Grabbing all tool menus
	UToolMenus* ToolMenus = UToolMenus::Get();

	// Extending the MainMenu - This is the one with file, edit, window, build etc
	UToolMenu* MenuBar = ToolMenus->ExtendMenu("MainFrame.MainMenu");
	MenuBar->AddSubMenu(
		"MainMenu",
		NAME_None,
		"EML",
		LOCTEXT("EMLMenu", "EML"),	// The second parameter is what the submenu will be called in the engine
		LOCTEXT("EMLMenu_ToolTip", "Open the EML menu")
	);

	UToolMenu* EMLMenu = UToolMenus::Get()->RegisterMenu("MainFrame.MainMenu.EML"); // Registering the menu so it's accessible and editable

	FToolMenuSection& Section = EMLMenu->AddSection("EML", LOCTEXT("EMLHeading", "Emerging Media Lab")); // Adding a named section to the EML menu

	// Adding entries to the SubMenu
	// When using default icons, we have to override the FSlateIcon here
	Section.AddMenuEntryWithCommandList(FEML_Core_UnrealCommands::Get().GenerateEMLProjectStructure,
		PluginCommands,
		TAttribute<FText>(),
		TAttribute<FText>(),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "MainFrame.NewProject")
	);
	// If we use custom icons, the icons can be defined in the EML_Core_UnrealStyle.cpp file instead, and sections can be added with a single line like this
	// Section.AddMenuEntryWithCommandList(FEML_Core_UnrealCommands::Get().GenerateEMLProjectStructure, PluginCommands);

	Section.AddMenuEntryWithCommandList(FEML_Core_UnrealCommands::Get().CodingStandards,
		PluginCommands,
		TAttribute<FText>(),
		TAttribute<FText>(),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "MessageLog.Docs")
	);

	Section.AddMenuEntryWithCommandList(FEML_Core_UnrealCommands::Get().ContactInformation,
		PluginCommands,
		TAttribute<FText>(),
		TAttribute<FText>(),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Help")
	);
}

void FEML_Core_UnrealModule::GenerateEMLProjectStructure()
{
	// First we make a prompt to ask the user if they want to continue
	FText Info = FText::FromString("Are you sure you want to generate an EML project structure?\nEditor will restart when this process is completed.");
	if (FMessageDialog::Open(EAppMsgType::YesNo, Info) == EAppReturnType::Yes)
	{
		// User clicked "Yes" - continue with the action
		
	}
	else
	{
		// User clicked "No" - cancel the action
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Generating EML Project Structure"));

	FString contentPath = FPaths::ProjectContentDir();

	// Project structure
	TArray<FString> DirectoryNames;
	DirectoryNames.Add("EML");
	DirectoryNames.Add("EML/AI");
	DirectoryNames.Add("EML/Art");
	DirectoryNames.Add("EML/Art/Materials");
	DirectoryNames.Add("EML/Art/Meshes");
	DirectoryNames.Add("EML/Art/Models");
	DirectoryNames.Add("EML/Art/Textures");
	DirectoryNames.Add("EML/Art/Sprites");
	DirectoryNames.Add("EML/Animations");
	DirectoryNames.Add("EML/Audio");
	DirectoryNames.Add("EML/Audio/Music");
	DirectoryNames.Add("EML/Audio/Sound");
	DirectoryNames.Add("EML/Cinematics"); 
	DirectoryNames.Add("EML/Databases");
	DirectoryNames.Add("EML/Effects");
	DirectoryNames.Add("EML/Fonts");
	DirectoryNames.Add("EML/Maps");
	DirectoryNames.Add("EML/Misc");
	DirectoryNames.Add("EML/Media");
	DirectoryNames.Add("EML/OOP");
	DirectoryNames.Add("EML/OOP/Actors");
	DirectoryNames.Add("EML/OOP/Actors/NPCs");
	DirectoryNames.Add("EML/OOP/Actors/Pawns");
	DirectoryNames.Add("EML/OOP/Actors/Objects");
	DirectoryNames.Add("EML/OOP/Code");
	DirectoryNames.Add("EML/OOP/Controllers");
	DirectoryNames.Add("EML/OOP/Data");
	DirectoryNames.Add("EML/OOP/Environment");
	DirectoryNames.Add("EML/OOP/UI");
	DirectoryNames.Add("EML/Network");
	DirectoryNames.Add("EML/Network/GameModes");
	DirectoryNames.Add("EML/Network/GameStates");
	DirectoryNames.Add("EML/Network/PlayerStates");
	DirectoryNames.Add("ThirdParty");
	//DirectoryNames.Add("Sandbox"); // We use 'Developers' folder instead of Sandbox

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	// Go through all directory names and see if directories exist
	for (size_t i = 0; i < DirectoryNames.Num(); i++)
	{
		FString DirectoryPath = *contentPath + DirectoryNames[i];
		// Directory Exists?
		if (!PlatformFile.DirectoryExists(*DirectoryPath))
		{
			UE_LOG(LogTemp, Log, TEXT("Creating Directory: %s"), *DirectoryPath);
			PlatformFile.CreateDirectory(*DirectoryPath);
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Attempting to create new GameInstance"));
	CreateGameInstance();

}

void FEML_Core_UnrealModule::CodingStandards()
{
	// Got to our coding standards URL
	UE_LOG(LogTemp, Log, TEXT("Redirecting to Coding Standards URL"));
	FString url = "https://eml.ubc.ca";
	FPlatformProcess::LaunchURL(*url, nullptr, nullptr);
}

void FEML_Core_UnrealModule::ContactInformation()
{
	// Got to our contact information URL
	FString url = "https://eml.ubc.ca";
	UE_LOG(LogTemp, Log, TEXT("Redirecting to Contact Information URL"));
	FPlatformProcess::LaunchURL(*url, nullptr, nullptr);
}

void FEML_Core_UnrealModule::CreateGameInstance()
{
	// Get the content directory
	FString ContentDir = FPaths::ProjectContentDir();
	
	// Create the package name
	FString PackageName = TEXT("/Game/EML/EML_GameInstance");

	// Check if GameInstance already exists - We don't want to overwrite anything
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	FString PackageFileName = ContentDir + TEXT("/EML/EML_GameInstance") + FPackageName::GetAssetPackageExtension();
	
	// Directory Exists?
	if (PlatformFile.FileExists(*PackageFileName))
	{
		UE_LOG(LogTemp, Warning, TEXT("EML GameInstance already exists, returning"), *PackageFileName);
		return;
	}	

	// Create the package
	UPackage* Package = CreatePackage(NULL, *PackageName);

	// Create the GameInstance blueprint
	UBlueprint* Blueprint = FKismetEditorUtilities::CreateBlueprint(UGameInstance::StaticClass(), Package, TEXT("EML_GameInstance"), EBlueprintType::BPTYPE_Normal, UBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass());

	// Cast the generated class to a UBlueprintGeneratedClass
	UBlueprintGeneratedClass* GeneratedClass = Cast<UBlueprintGeneratedClass>(Blueprint->GeneratedClass);

	// Set the standalone flag so our GameInstance isn't dependent on other objects
	GeneratedClass->SetFlags(RF_Standalone | RF_Public);

	// Save the package
	bool bSaved = UPackage::SavePackage(Package, GeneratedClass, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *PackageFileName);
	if (bSaved)
	{
		// Add the package to the asset registry
		FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
		AssetRegistryModule.AssetCreated(GeneratedClass);
		FString PackagePath = FPackageName::GetLongPackagePath(PackageName);
		AssetRegistryModule.Get().AddPath(PackagePath);
		UE_LOG(LogTemp, Log, TEXT("EML_GameInstance created successfully"));

		UE_LOG(LogTemp, Log, TEXT("Attempting to set active GameInstance to EML_GameInstance"));
		SetGameInstanceToEMLGameInstance();
	}
}

void FEML_Core_UnrealModule::SetGameInstanceToEMLGameInstance()
{
	// Load the config file
	GConfig->LoadGlobalIniFile(GEngineIni, TEXT("Engine"));

	// Set the game instance class
	GConfig->SetString(TEXT("/Script/EngineSettings.GameMapsSettings"), TEXT("GameInstanceClass"), TEXT("/Game/EML/EML_GameInstance.EML_GameInstance_C"), GEngineIni);

	// Save the config file
	GConfig->Flush(false, GEngineIni);

	UE_LOG(LogTemp, Log, TEXT("GameInstance changed in global ini file. Will show correctly next time project is launched."));

	FUnrealEdMisc::Get().RestartEditor(false);

}


	

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FEML_Core_UnrealModule, EML_Core_Unreal)