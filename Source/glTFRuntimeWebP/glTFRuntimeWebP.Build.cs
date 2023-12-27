// Copyright 2023 Roberto De Ioris

using UnrealBuildTool;

public class glTFRuntimeWebP : ModuleRules
{
    public glTFRuntimeWebP(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
				// ... add public include paths required here ...
			}
            );


        PrivateIncludePaths.AddRange(
            new string[] {
				// ... add other private include paths required here ...
			}
            );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
				// ... add other public dependencies that you statically link with here ...
			}
            );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "glTFRuntime"
				// ... add private dependencies that you statically link with here ...	
			}
            );


        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
				// ... add any modules that your module loads dynamically here ...
			}
            );

        string ThirdPartyDirectory = System.IO.Path.Combine(ModuleDirectory, "..", "ThirdParty");

        PrivateIncludePaths.Add(System.IO.Path.Combine(ThirdPartyDirectory, "libwebp", "include"));

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyDirectory, "libwebp", "lib", "libwebp_win_x64.lib"));
            PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyDirectory, "libwebp", "lib", "libwebp_demux_win_x64.lib"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyDirectory, "libwebp", "lib", "libwebp_linux_x64.a"));
            PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyDirectory, "libwebp", "lib", "libwebp_demux_linux_x64.a"));
        }
        else if (Target.Platform == UnrealTargetPlatform.LinuxArm64)
        {
            PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyDirectory, "libwebp", "lib", "libwebp_linux_arm64.a"));
            PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyDirectory, "libwebp", "lib", "libwebp_demux_linux_arm64.a"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyDirectory, "libwebp", "lib", "libwebp_mac_arm64.a"));
            PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyDirectory, "libwebp", "lib", "libwebp_demux_mac_arm64.a"));
        }
        else if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyDirectory, "libwebp", "lib", "libwebp_ios_arm64.a"));
            PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyDirectory, "libwebp", "lib", "libwebp_demux_ios_arm64.a"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyDirectory, "libwebp", "lib", "libwebp_android_arm64.a"));
            PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyDirectory, "libwebp", "lib", "libwebp_demux_android_arm64.a"));
        }
    }
}
