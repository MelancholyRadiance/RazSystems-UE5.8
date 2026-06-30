#include "AmmoManagerComponent.h"
#include "PDACalibreData.h"

UMagazineInstance* UAmmoManagerComponent::CreateAndAddMagazine(UPDAMagazineData* MagData, bool bFull)
{
	UMagazineInstance* Mag = UMagazineInstance::Create(this, MagData, bFull);
	if (Mag)
	{
		MagazineInventory.Add(Mag);
		BroadcastChanged();
	}
	return Mag;
}

void UAmmoManagerComponent::AddMagazine(UMagazineInstance* Mag)
{
	if (Mag)
	{
		MagazineInventory.Add(Mag);
		BroadcastChanged();
	}
}

const TArray<UMagazineInstance*>& UAmmoManagerComponent::GetMagazineInventory() const
{
	// Safe cast: TArray<TObjectPtr<T>> is layout-compatible with TArray<T*>
	return reinterpret_cast<const TArray<UMagazineInstance*>&>(MagazineInventory);
}

void UAmmoManagerComponent::LoadMagazine(UMagazineInstance* Mag)
{
	if (LoadedMagazine)
	{
		MagazineInventory.Add(LoadedMagazine);
	}

	LoadedMagazine = Mag;
	MagazineInventory.Remove(Mag);
	BroadcastChanged();
}

UMagazineInstance* UAmmoManagerComponent::EjectMagazine()
{
	UMagazineInstance* Ejected = LoadedMagazine;
	if (Ejected)
	{
		MagazineInventory.Add(Ejected);
		LoadedMagazine = nullptr;
		BroadcastChanged();
	}
	return Ejected;
}

bool UAmmoManagerComponent::Reload(UPDACalibreData* RequiredCalibre)
{
	UMagazineInstance* Next = nullptr;
	for (UMagazineInstance* Mag : MagazineInventory)
	{
		if (!Mag || Mag->CurrentRounds <= 0) continue;
		if (RequiredCalibre && Mag->MagazineType && Mag->MagazineType->Calibre != RequiredCalibre) continue;
		Next = Mag;
		break;
	}

	if (!Next) return false;

	if (LoadedMagazine)
	{
		MagazineInventory.Add(LoadedMagazine);
	}

	LoadedMagazine = Next;
	MagazineInventory.Remove(Next);
	BroadcastChanged();
	return true;
}

bool UAmmoManagerComponent::ConsumeRound()
{
	if (!LoadedMagazine) return false;
	const bool bHadAmmo = LoadedMagazine->ConsumeRound();
	if (bHadAmmo)
	{
		BroadcastChanged();
	}
	return bHadAmmo;
}

void UAmmoManagerComponent::CheckMagazine()
{
	if (!LoadedMagazine)
	{
		OnMagazineChecked.Broadcast(0, true);
		return;
	}

	bool bIsAccurate = false;
	const int32 Estimate = LoadedMagazine->GetCheckedEstimate(CheckAccuracyCurve, bIsAccurate);
	OnMagazineChecked.Broadcast(Estimate, bIsAccurate);
}

void UAmmoManagerComponent::BroadcastChanged()
{
	OnMagazinesChanged.Broadcast();
}
