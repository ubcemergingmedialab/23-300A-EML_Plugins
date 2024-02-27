// Fill out your copyright notice in the Description page of Project Settings.

#include "EML_Core_BPFL.h"

FString UEML_Core_BPFL::ConvertByteArrayToString(TArray<uint8> ByteArray)
{
    // Create an FString to store the resulting string.
    FString ResultString;

    // Loop through the byte array and append each byte to the string.
    for (uint8 ByteValue : ByteArray)
    {
        // Append each byte to the result string.
        ResultString.AppendChar(static_cast<TCHAR>(ByteValue));
    }

    return ResultString;
}

