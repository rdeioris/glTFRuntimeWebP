// Copyright 2023 Roberto De Ioris

#include "glTFRuntimeWebPFunctionLibrary.h"
THIRD_PARTY_INCLUDES_START
#include "webp/demux.h"
THIRD_PARTY_INCLUDES_END

UTexture2DArray* UglTFRuntimeWebPFunctionLibrary::LoadWebPAnimationAsTexture2DArray(UglTFRuntimeAsset* Asset, int32& NumFrames, float& FPS, FLinearColor& BackgroundColor, int32& LoopCount, const FglTFRuntimeImagesConfig& ImagesConfig)
{
	WebPData ImageData = {};
	ImageData.bytes = Asset->GetParser()->GetBlob().GetData();
	ImageData.size = Asset->GetParser()->GetBlob().Num();

	WebPAnimDecoderOptions DecoderOptions = {};
	DecoderOptions.color_mode = WEBP_CSP_MODE::MODE_BGRA;

	WebPAnimDecoder* Decoder = WebPAnimDecoderNew(&ImageData, &DecoderOptions);
	if (!Decoder)
	{
		return nullptr;
	}

	WebPAnimInfo AnimInfo;
	if (!WebPAnimDecoderGetInfo(Decoder, &AnimInfo))
	{
		WebPAnimDecoderDelete(Decoder);
		return nullptr;
	}

	NumFrames = 0;
	LoopCount = AnimInfo.loop_count;
	BackgroundColor = FLinearColor(FColor(AnimInfo.bgcolor >> 24, (AnimInfo.bgcolor >> 16) & 0xFF, (AnimInfo.bgcolor >> 8) & 0xFF, AnimInfo.bgcolor & 0xFF));

	int32 Timestamp = 0;

	TArray<FglTFRuntimeMipMap> Mips;
	while (WebPAnimDecoderHasMoreFrames(Decoder))
	{
		uint8* BGRA = nullptr;
		if (!WebPAnimDecoderGetNext(Decoder, &BGRA, &Timestamp))
		{
			break;
		}

		FglTFRuntimeMipMap Mip(-1, EPixelFormat::PF_B8G8R8A8, AnimInfo.canvas_width, AnimInfo.canvas_height);
		Mip.Pixels.Append(BGRA, AnimInfo.canvas_width * AnimInfo.canvas_height * 4);

		Mips.Add(MoveTemp(Mip));

		NumFrames++;
	}

	WebPAnimDecoderDelete(Decoder);

	FPS = 1000 / (static_cast<float>(Timestamp) / NumFrames);

	return Asset->GetParser()->BuildTextureArray(Asset, Mips, ImagesConfig, FglTFRuntimeTextureSampler());
}