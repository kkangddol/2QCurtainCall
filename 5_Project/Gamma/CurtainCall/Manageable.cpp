#include "GammaEngine.h"
#include "Manageable.h"
#include "GameManager.h"

Manageable::Manageable()
{
	GameManager::RegistManageable(this);
}
