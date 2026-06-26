using UnrealBuildTool;

public class WeaponSystemBaseEditor : ModuleRules
{
	public WeaponSystemBaseEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"WeaponSystemBase",
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"CoreUObject",
			"Engine",
			"UnrealEd",
			"AssetTools",
			"AmmoSystem",
			"MagazineSystem",
		});
	}
}
