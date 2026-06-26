#include "PDAFireModeFullAuto.h"
#include "FireModeLogic_FullAuto.h"

TSubclassOf<UFireModeLogicBase> UPDAFireModeFullAuto::GetLogicClass() const
{
	return UFireModeLogic_FullAuto::StaticClass();
}
