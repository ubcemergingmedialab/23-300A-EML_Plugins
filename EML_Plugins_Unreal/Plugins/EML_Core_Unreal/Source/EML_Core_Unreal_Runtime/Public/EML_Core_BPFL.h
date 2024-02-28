// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Modules/ModuleManager.h"
#include "EML_Core_BPFL.generated.h"

#ifndef UEML_Core_Unreal_Runtime_API
#define UEML_Core_Unreal_Runtime_API
#endif

/**
 * 
 */

class FEML_Core_Unreal_RuntimeModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

UCLASS()
class UEML_Core_Unreal_Runtime_API UEML_Core_BPFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "EML Functions")
	static FString ConvertByteArrayToString(TArray<uint8> ByteArray);
	
};
