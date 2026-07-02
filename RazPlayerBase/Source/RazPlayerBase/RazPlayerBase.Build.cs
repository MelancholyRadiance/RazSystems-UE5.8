using UnrealBuildTool;

public class RazPlayerBase : ModuleRules
{
	public RazPlayerBase(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore",
			"EnhancedInput",
			"MovementSystem",
			"AmmoManagement",
			"RazInputActions"
		});
	}
}
