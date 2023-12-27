# glTFRuntimeWebP
EXT_texture_webp for glTFRuntime

## Supported platforms

* Linux X86-64
* Linux Arm64
* Windows X86-64
* Mac Arm64
* iOS Arm64
* Android Arm64

## Usage

Just add the plugin to the project Plugins directory: it will automatically registers as a new glTF image processor

## Animations
WebP animations are supported by generating a Texture2DArray (each slice is a frame) using the LoadWebPAnimationAsTexture2DArray UFunction:

![image](https://github.com/rdeioris/glTFRuntimeWebP/assets/2234592/4ae296fc-6d35-44b1-8f19-c86018dbaba5)

You can eventually switch frames directly from a material:

![image](https://github.com/rdeioris/glTFRuntimeWebP/assets/2234592/e31b4477-f5e3-4049-b082-c0de84886739)

(FPS and NumberOfFrames can be set directly from the output of LoadWebPAnimationAsTexture2DArray)

