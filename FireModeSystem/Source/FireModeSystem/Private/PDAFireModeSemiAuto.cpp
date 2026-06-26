#include "PDAFireModeSemiAuto.h"
#include "FireModeLogic_SemiAuto.h"

TSubclassOf<UFireModeLogicBase> UPDAFireModeSemiAuto::GetLogicClass() const
{
	return UFireModeLogic_SemiAuto::StaticClass();
}
