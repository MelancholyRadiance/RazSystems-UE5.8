// Copyright Epic Games, Inc. All Rights Reserved.

#include "PDANamingConventionValidator.h"

#include "AssetRegistry/AssetData.h"
#include "Internationalization/Regex.h"
#include "Misc/DataValidation.h"

#define LOCTEXT_NAMESPACE "PDANamingConventionValidator"

namespace PDANaming
{
	/** All PDA data assets share this prefix. */
	static const FString Prefix = TEXT("PDA_");

	/** One field in a name (everything between the underscores after the type). */
	struct FTokenSpec
	{
		const TCHAR* Pattern;   // Anchored regex the token must match in full.
		const TCHAR* Describe;  // Human readable description used in error messages.
	};

	/** A complete naming rule for a single asset type. */
	struct FRule
	{
		const TCHAR* Type;      // Type token that follows "PDA_", e.g. TEXT("Mag").
		const TCHAR* Display;   // Friendly name for messages, e.g. TEXT("Magazine").
		const TCHAR* Template;  // Expected layout shown to the user.
		const TCHAR* Example;   // A valid example name.
		TArray<FTokenSpec> Tokens; // Ordered specs for the parts after PDA_<Type>_.
	};

	// Common token patterns reused across rules.
	static const TCHAR* CalibrePattern = TEXT("^[0-9]+x[0-9]+$");
	static const TCHAR* NamePattern    = TEXT("^[A-Za-z0-9]+$");
	static const TCHAR* IntPattern     = TEXT("^[0-9]+$");
	static const TCHAR* Capacity3      = TEXT("^[0-9]{3}$");

	/**
	 * The rules table. To support a new PDA type, add another FRule here.
	 */
	static const TArray<FRule>& GetRules()
	{
		static const TArray<FRule> Rules =
		{
			{
				TEXT("Calibre"), TEXT("Calibre"),
				TEXT("PDA_Calibre_<NNxNN>"),
				TEXT("PDA_Calibre_556x45"),
				{
					{ CalibrePattern, TEXT("a calibre in NNxNN format (digits, x, digits), e.g. 556x45 or 9x19") },
				}
			},
			{
				TEXT("Mag"), TEXT("Magazine"),
				TEXT("PDA_Mag_<Calibre>_<Capacity>_<Name>"),
				TEXT("PDA_Mag_556x45_030_Stanag"),
				{
					{ CalibrePattern, TEXT("a calibre in NNxNN format (digits, x, digits), e.g. 556x45 or 9x19") },
					{ Capacity3,      TEXT("a 3-digit zero-padded round capacity, e.g. 030") },
					{ NamePattern,    TEXT("an alphanumeric name, e.g. Stanag or 6LG1") },
				}
			},
			{
				TEXT("Ammo"), TEXT("Ammo"),
				TEXT("PDA_Ammo_<Calibre>_<Damage>_<Penetration>_<Name>"),
				TEXT("PDA_Ammo_556x45_46_28_M855"),
				{
					{ CalibrePattern, TEXT("a calibre in NNxNN format (digits, x, digits), e.g. 556x45 or 9x19") },
					{ IntPattern,     TEXT("a whole-number damage value, e.g. 46") },
					{ IntPattern,     TEXT("a whole-number penetration value, e.g. 28") },
					{ NamePattern,    TEXT("an alphanumeric name, e.g. M855 or 6LG1") },
				}
			},
			{
				TEXT("Weapon"), TEXT("Weapon"),
				TEXT("PDA_Weapon_<Calibre>_<FireRate>_<Name>"),
				TEXT("PDA_Weapon_556x45_800_M4A1"),
				{
					{ CalibrePattern, TEXT("a calibre in NNxNN format (digits, x, digits), e.g. 556x45 or 9x19") },
					{ IntPattern,     TEXT("a whole-number fire rate in RPM, e.g. 800") },
					{ NamePattern,    TEXT("an alphanumeric name, e.g. M4A1") },
				}
			},
		};
		return Rules;
	}

	/** Finds the rule whose type token matches (case sensitive), or null. */
	static const FRule* FindRule(const FString& TypeToken)
	{
		for (const FRule& Rule : GetRules())
		{
			if (TypeToken.Equals(Rule.Type, ESearchCase::CaseSensitive))
			{
				return &Rule;
			}
		}
		return nullptr;
	}

	/** Returns true if Token matches the anchored Pattern in full. */
	static bool TokenMatches(const TCHAR* Pattern, const FString& Token)
	{
		FRegexPattern Compiled(Pattern);
		FRegexMatcher Matcher(Compiled, Token);
		return Matcher.FindNext();
	}

	/** Comma separated list of the known type tokens, for warnings. */
	static FString KnownTypes()
	{
		TArray<FString> Names;
		for (const FRule& Rule : GetRules())
		{
			Names.Add(Rule.Type);
		}
		return FString::Join(Names, TEXT(", "));
	}
}

UPDANamingConventionValidator::UPDANamingConventionValidator()
{
	bIsEnabled = true;
}

bool UPDANamingConventionValidator::CanValidateAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) const
{
	// Only concerned with the project's PDA data assets.
	return InAssetData.AssetName.ToString().StartsWith(PDANaming::Prefix, ESearchCase::CaseSensitive);
}

EDataValidationResult UPDANamingConventionValidator::ValidateLoadedAsset_Implementation(const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& Context)
{
	const FString AssetName = InAssetData.AssetName.ToString();

	TArray<FString> Parts;
	AssetName.ParseIntoArray(Parts, TEXT("_"), /*InCullEmpty*/ false);

	// Parts[0] is guaranteed to be "PDA" by CanValidateAsset. Parts[1] is the type.
	const FString TypeToken = Parts.IsValidIndex(1) ? Parts[1] : FString();
	const PDANaming::FRule* Rule = PDANaming::FindRule(TypeToken);

	if (Rule == nullptr)
	{
		// Looks like a PDA asset but the type is not one we know about. Warn rather
		// than fail so unrelated PDA_ assets are not blocked.
		AssetWarning(InAsset, FText::FromString(FString::Printf(
			TEXT("'%s' starts with PDA_ but '%s' is not a known asset type. Known types: %s. If this name is intentional you can ignore this warning."),
			*AssetName, *TypeToken, *PDANaming::KnownTypes())));
		AssetPasses(InAsset);
		return EDataValidationResult::Valid;
	}

	const int32 ExpectedNum = 2 + Rule->Tokens.Num(); // PDA + Type + fields.

	if (Parts.Num() != ExpectedNum)
	{
		AssetFails(InAsset, FText::FromString(FString::Printf(
			TEXT("%s name '%s' has %d part(s) but the convention needs %d.\nExpected format: %s\nExample: %s"),
			Rule->Display, *AssetName, Parts.Num(), ExpectedNum, Rule->Template, Rule->Example)));
		return EDataValidationResult::Invalid;
	}

	bool bAllValid = true;
	for (int32 i = 0; i < Rule->Tokens.Num(); ++i)
	{
		const FString& Token = Parts[2 + i];
		const PDANaming::FTokenSpec& Spec = Rule->Tokens[i];
		if (!PDANaming::TokenMatches(Spec.Pattern, Token))
		{
			bAllValid = false;
			AssetFails(InAsset, FText::FromString(FString::Printf(
				TEXT("%s name '%s': part %d ('%s') is invalid - expected %s.\nFull format: %s\nExample: %s"),
				Rule->Display, *AssetName, i + 1, *Token, Spec.Describe, Rule->Template, Rule->Example)));
		}
	}

	if (bAllValid)
	{
		AssetPasses(InAsset);
		return EDataValidationResult::Valid;
	}

	return EDataValidationResult::Invalid;
}

#undef LOCTEXT_NAMESPACE
