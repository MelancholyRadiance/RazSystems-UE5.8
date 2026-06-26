using UnrealBuildTool;

public class WeaponSystemBase : ModuleRules
{
	public WeaponSystemBase(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"AmmoSystem",
			"MagazineSystem",
		});
	}
}
