#pragma once
using namespace GammaEngine;

class Reactant
{
public:
	void AttachTrigger(Trigger*);
protected:
	Trigger* trigger_;

};

