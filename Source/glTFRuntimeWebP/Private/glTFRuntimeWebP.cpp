// Copyright Roberto De Ioris

#include "glTFRuntimeWebP.h"
#include "glTFRuntimeParser.h"
THIRD_PARTY_INCLUDES_START
#include "webp/decode.h"
THIRD_PARTY_INCLUDES_END

#define LOCTEXT_NAMESPACE "FglTFRuntimeWebPModule"

void FglTFRuntimeWebPModule::StartupModule()
{
	// extract the right ImageIndex
	FglTFRuntimeParser::OnTextureImageIndex.AddLambda([](TSharedRef<FglTFRuntimeParser> Parser, TSharedRef<FJsonObject> JsonTextureObject, int64& ImageIndex)
		{
			// check for used extensions
			if (!Parser->ExtensionsUsed.Contains("EXT_texture_webp"))
			{
				return;
			}
	ImageIndex = Parser->GetJsonExtensionObjectIndex(JsonTextureObject, "EXT_texture_webp", "source", INDEX_NONE);
		});

	FglTFRuntimeParser::OnTexturePixels.AddLambda([](TSharedRef<FglTFRuntimeParser> Parser, TSharedRef<FJsonObject> JsonImageObject, const TArray64<uint8>& CompressedPixels, int32& Width, int32& Height, EPixelFormat& PixelFormat, TArray64<uint8>& UncompressedPixels, const FglTFRuntimeImagesConfig& ImagesConfig)
		{
			// skip if already processed
			if (UncompressedPixels.Num() > 0)
			{
				return;
			}

	// check for used extensions
	if (!Parser->ExtensionsUsed.Contains("EXT_texture_webp"))
	{
		return;
	}

	const FString MimeType = Parser->GetJsonObjectString(JsonImageObject, "mimeType", "");
	// skip non webp mimeType (can be empty)
	if (MimeType != "" && MimeType != "image/webp")
	{
		return;
	}

	uint8* Pixels = WebPDecodeBGRA(CompressedPixels.GetData(), CompressedPixels.Num(), &Width, &Height);
	if (!Pixels)
	{
		return;
	}

	PixelFormat = EPixelFormat::PF_B8G8R8A8;

	UncompressedPixels.Append(Pixels, Width * Height * 4);
	WebPFree(Pixels);

		});
}

void FglTFRuntimeWebPModule::ShutdownModule()
{

}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FglTFRuntimeWebPModule, glTFRuntimeWebP)