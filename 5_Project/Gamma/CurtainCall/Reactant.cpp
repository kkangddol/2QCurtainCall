#include "GammaEngine.h"
#include "Subject.h"
#include "Trigger.h"
#include "Reactant.h"
using namespace GammaEngine;

void Reactant::AttachTrigger(Trigger* t)
{
	trigger_ = t;
}
