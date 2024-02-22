// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EML_Core_BPFL.generated.h"

/**
 * 
 */
UCLASS()
class EML_CORE_UNREAL_API UEML_Core_BPFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "EML Functions")
	static FString ConvertByteArrayToString(TArray<uint8> ByteArray);
	
};
