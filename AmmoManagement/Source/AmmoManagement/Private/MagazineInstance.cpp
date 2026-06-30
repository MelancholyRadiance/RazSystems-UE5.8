#include "MagazineInstance.h"

UMagazineInstance* UMagazineInstance::Create(UObject* Outer, UPDAMagazineData* Data, bool bFull)
{
	if (!Data) return nullptr;

	UMagazineInstance* Instance = NewObject<UMagazineInstance>(Outer);
	Instance->MagazineType = Data;
	Instance->CurrentRounds = bFull ? Data->Capacity : 0;
	return Instance;
}

float UMagazineInstance::GetFillPercent() const
{
	const int32 Cap = GetCapacity();
	return Cap > 0 ? FMath::Clamp(static_cast<float>(CurrentRounds) / Cap, 0.f, 1.f) : 0.f;
}

int32 UMagazineInstance::GetCapacity() const
{
	return MagazineType ? MagazineType->Capacity : 0;
}

bool UMagazineInstance::ConsumeRound()
{
	if (CurrentRounds <= 0) return false;
	--CurrentRounds;
	return true;
}

int32 UMagazineInstance::GetCheckedEstimate(UCurveFloat* AccuracyCurve, bool& bOutIsAccurate) const
{
	const int32 Cap = GetCapacity();
	if (Cap <= 0)
	{
		bOutIsAccurate = true;
		return 0;
	}

	const float Fill = GetFillPercent();

	float Accuracy;
	if (AccuracyCurve)
	{
		Accuracy = FMath::Clamp(AccuracyCurve->GetFloatValue(Fill), 0.f, 1.f);
	}
	else
	{
		// Exact at the extremes, rough in the middle
		Accuracy = (Fill <= 0.2f || Fill >= 0.8f) ? 1.f : 0.f;
	}

	bOutIsAccurate = (Accuracy >= 1.f);

	if (bOutIsAccurate)
	{
		return CurrentRounds;
	}

	// Round down to the nearest bucket. Accuracy 0 -> bucket of 5. Accuracy 1 -> bucket of 1.
	const int32 Bucket = FMath::Max(1, FMath::RoundToInt(FMath::Lerp(5.f, 1.f, Accuracy)));
	return (CurrentRounds / Bucket) * Bucket;
}
