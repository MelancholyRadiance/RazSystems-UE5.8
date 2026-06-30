using UnrealBuildTool;

public class AmmoManagement : ModuleRules
{
	public AmmoManagement(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"UMG",
			"MagazineSystem",
			"AmmoSystem",
		});
	}
}
