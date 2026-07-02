#pragma once

#include "Factories/Factory.h"
#include "RazInputActionsEditor.h"
#include "RazIMC.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "InputModifiers.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Misc/PackageName.h"
#include "Factory_RazInputActions.generated.h"

UCLASS()
class UFactory_RazInputActions : public UFactory
{
	GENERATED_BODY()
public:
	UFactory_RazInputActions()
	{
		bCreateNew = true;
		bEditAfterNew = true;
		SupportedClass = URazIMC::StaticClass();
	}

	virtual FText GetDisplayName() const override
	{
		return NSLOCTEXT("RazInputActionsEditor", "RazInputFactory", "Input Context");
	}

	virtual uint32 GetMenuCategories() const override { return RazSystemsCategory; }

	virtual const TArray<FText>& GetMenuCategorySubMenus() const override
	{
		static const TArray<FText> SubMenus = { NSLOCTEXT("RazInputActionsEditor", "InputActionsSubMenu", "InputActions") };
		return SubMenus;
	}

	virtual FString GetDefaultNewAssetName() const override { return TEXT("IMC_Player_"); }

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override
	{
		URazIMC* IMC = NewObject<URazIMC>(InParent, InClass, InName, Flags);

		const FString BasePath  = FPackageName::GetLongPackagePath(InParent->GetOutermost()->GetName());
		const FString SubFolder = BasePath / TEXT("InputActions");
		const FString Prefix    = InName.ToString();

		// Axis2D actions with default bindings
		UInputAction* MoveAction = MakeAction(SubFolder, Prefix, TEXT("Move"), Flags, EInputActionValueType::Axis2D);
		BindMove(IMC, MoveAction);

		UInputAction* LookAction = MakeAction(SubFolder, Prefix, TEXT("Look"), Flags, EInputActionValueType::Axis2D);
		IMC->MapKey(LookAction, EKeys::Mouse2D);

		// Digital actions with default keys
		MakeAndMap(SubFolder, Prefix, TEXT("Jump"),          IMC, Flags, EKeys::SpaceBar);
		MakeAndMap(SubFolder, Prefix, TEXT("Sprint"),        IMC, Flags, EKeys::LeftShift);
		MakeAndMap(SubFolder, Prefix, TEXT("Crouch"),        IMC, Flags, EKeys::LeftControl);
		MakeAndMap(SubFolder, Prefix, TEXT("Prone"),         IMC, Flags, EKeys::C);
		MakeAndMap(SubFolder, Prefix, TEXT("Aim"),           IMC, Flags, EKeys::RightMouseButton);
		MakeAndMap(SubFolder, Prefix, TEXT("Fire"),          IMC, Flags, EKeys::LeftMouseButton);
		MakeAndMap(SubFolder, Prefix, TEXT("AltFire"),       IMC, Flags, EKeys::MouseScrollDown);
		MakeAndMap(SubFolder, Prefix, TEXT("Reload"),        IMC, Flags, EKeys::R);
		MakeAndMap(SubFolder, Prefix, TEXT("CheckMagazine"), IMC, Flags, EKeys::T);
		MakeAndMap(SubFolder, Prefix, TEXT("CycleFireMode"), IMC, Flags, EKeys::B);

		return IMC;
	}

	static uint32 RazSystemsCategory;

private:
	static UInputAction* MakeAction(const FString& FolderPath, const FString& Prefix, const FString& Suffix, EObjectFlags Flags, EInputActionValueType ValueType = EInputActionValueType::Boolean)
	{
		UInputAction* Action = MakeAsset<UInputAction>(FolderPath, Prefix + TEXT("_") + Suffix, Flags);
		if (Action) Action->ValueType = ValueType;
		return Action;
	}

	static void MakeAndMap(const FString& FolderPath, const FString& Prefix, const FString& Suffix, UInputMappingContext* IMC, EObjectFlags Flags, FKey DefaultKey = FKey())
	{
		UInputAction* Action = MakeAction(FolderPath, Prefix, Suffix, Flags);
		if (IMC && Action)
		{
			IMC->MapKey(Action, DefaultKey);
		}
	}

	// Binds WASD to a 2D Move action using swizzle/negate modifiers.
	// D=+X, A=-X, W=+Y (forward), S=-Y (backward).
	static void BindMove(UInputMappingContext* IMC, UInputAction* Action)
	{
		if (!IMC || !Action) return;

		// D - Right (+X), no modifiers needed
		IMC->MapKey(Action, EKeys::D);

		// A - Left (-X)
		FEnhancedActionKeyMapping& AMap = IMC->MapKey(Action, EKeys::A);
		UInputModifierNegate* NegA = NewObject<UInputModifierNegate>(IMC);
		NegA->bX = true; NegA->bY = false; NegA->bZ = false;
		AMap.Modifiers.Add(NegA);

		// W - Forward (+Y): YXZ swizzle moves the bool from X onto Y
		FEnhancedActionKeyMapping& WMap = IMC->MapKey(Action, EKeys::W);
		UInputModifierSwizzleAxis* SwW = NewObject<UInputModifierSwizzleAxis>(IMC);
		SwW->Order = EInputAxisSwizzle::YXZ;
		WMap.Modifiers.Add(SwW);

		// S - Backward (-Y): swizzle then negate Y
		FEnhancedActionKeyMapping& SMap = IMC->MapKey(Action, EKeys::S);
		UInputModifierSwizzleAxis* SwS = NewObject<UInputModifierSwizzleAxis>(IMC);
		SwS->Order = EInputAxisSwizzle::YXZ;
		UInputModifierNegate* NegS = NewObject<UInputModifierNegate>(IMC);
		NegS->bX = false; NegS->bY = true; NegS->bZ = false;
		SMap.Modifiers.Add(SwS);
		SMap.Modifiers.Add(NegS);
	}

	template<typename T>
	static T* MakeAsset(const FString& FolderPath, const FString& AssetName, EObjectFlags Flags)
	{
		UPackage* Pkg = CreatePackage(*(FolderPath / AssetName));
		T* Obj = NewObject<T>(Pkg, T::StaticClass(), *AssetName, Flags | RF_Public | RF_Standalone);
		FAssetRegistryModule::AssetCreated(Obj);
		Pkg->MarkPackageDirty();
		return Obj;
	}
};
