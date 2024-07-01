#pragma once
class Player;
class IInteractable
{
public:
	virtual void Use(Player* user) abstract;

};