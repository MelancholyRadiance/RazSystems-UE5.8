#include "PDAFireModeBurst.h"
#include "FireModeLogic_Burst.h"

TSubclassOf<UFireModeLogicBase> UPDAFireModeBurst::GetLogicClass() const
{
	return UFireModeLogic_Burst::StaticClass();
}
