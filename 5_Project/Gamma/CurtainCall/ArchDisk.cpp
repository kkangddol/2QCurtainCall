#include "GammaEngine.h"
#include "Arch.h"
#include "Player.h"
#include "Information.h"
#include "ArchDisk.h"


ArchDisk::ArchDisk(GameObject* t) : Disk(t)
{

}

void ArchDisk::AttachArch(Arch* ac)
{
	arch = ac;
	arch->disk = this;
}

void ArchDisk::Use(Player* p)
{
	lb->isEnabled = true;
	lb->transform->parent = transform;
	lb->transform->position = vector2();
	Tween::Animate(lb->transform->position, PLAYBACK::ONCE_FORWARD, vector2(150, -100), OUTBACK, 1);


	rb->isEnabled = true;
	rb->transform->parent = transform;
	rb->transform->position = vector2();
	Tween::Animate(rb->transform->position, PLAYBACK::ONCE_FORWARD, vector2(-150, -100), OUTBACK, 1);

	Trigger::RegistPlayer(p);
	Trigger::Hold();
	Tween::Animate(p->transform->position.x, PLAYBACK::ONCE_FORWARD, transform->position.x, EASING::LINEAR, 1);
	p->actionSubject.Where([this](PlayerAction x) {
		return arch->initialHeight >= arch->transform->position.y;
	}).Where([](PlayerAction x) {
		return x.LeftShoulder == KeyState::pressed;
	}).Throttle(term).Select<DiskState>([this](PlayerAction x) {
		return state;
	}).Subscribe([this](DiskState x) {
		if (x == G)
		{
			state = R;

		}
		else if (x == B)
		{
			state = G;
		}
		else
		{
			state = B;
		}

		progress = state / 2.0f;

	});

	p->actionSubject.Where([this](PlayerAction x) {
		return arch->initialHeight >= arch->transform->position.y;
	}).Where([](PlayerAction x) {
		return x.RightShoulder == KeyState::pressed;
	}).Throttle(term).Select<DiskState>([this](PlayerAction x) {
		return state;
	}).Subscribe([this](DiskState x) {
		if (x == G)
			state = B;
		else if (x == R)
			state = G;
		else
			state = R;

		progress = state / 2.0f;
	});
	
}
void ArchDisk::Start()
{
	lb = Information::Create(L"lb");
	rb = Information::Create(L"rb");
}