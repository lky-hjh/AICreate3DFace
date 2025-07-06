using UnrealBuildTool;

public class FaceToonPlugin : ModuleRules
{
	public FaceToonPlugin(ReadOnlyTargetRules target) : base(target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[] {
			"Core",
			"CoreUObject",
			"Engine",
			"ProceduralMeshComponent",
			"ImageWrapper",
			"Json",
			"JsonUtilities"
		});

		bEnableExceptions = true;
		bUseUnity = false;
	}
}