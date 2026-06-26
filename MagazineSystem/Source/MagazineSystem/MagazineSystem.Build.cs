using UnrealBuildTool;

public class MagazineSystem : ModuleRules
{
	public MagazineSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"AmmoSystem",
		});
	}
}
