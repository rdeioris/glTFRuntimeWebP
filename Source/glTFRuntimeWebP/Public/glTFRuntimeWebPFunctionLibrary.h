// Copyright 2023 Roberto De Ioris

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "glTFRuntimeAsset.h"
#include "glTFRuntimeWebPFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GLTFRUNTIMEWEBP_API UglTFRuntimeWebPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "ImagesConfig"), Category="glTFRuntime|WebP")
	static UTexture2DArray* LoadWebPAnimationAsTexture2DArray(UglTFRuntimeAsset* Asset, int32& NumFrames, float& FPS, FLinearColor& BackgroundColor, int32& LoopCount, const FglTFRuntimeImagesConfig& ImagesConfig);
	
};
