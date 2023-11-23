#pragma once
#include "Disk.h"

using namespace GammaEngine;

class Arch;

class ArchDisk : public Disk
{
public:
	ArchDisk(GameObject* t);
	virtual void Start() override;
	virtual void Use(Player* p);
	void AttachArch(Arch* ac);

public:
	DiskState state = R;
	Arch* arch;
	GameObject* lb;
	GameObject* rb;
};

