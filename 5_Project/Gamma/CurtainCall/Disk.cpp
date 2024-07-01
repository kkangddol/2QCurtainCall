#include "GammaEngine.h"
#include "GRX.h"
#include "Disk.h"
#include "Player.h"

Disk::Disk(GameObject* t) : Trigger(t)
{

}

void Disk::Use(Player* p)
{
	Trigger::RegistPlayer(p);
	Trigger::Hold();
	Tween::Animate(p->transform->position.x, PLAYBACK::ONCE_FORWARD, transform->position.x, EASING::LINEAR, 1);
	p->actionSubject.Throttle(term)
	.Where([](PlayerAction x) {
		return x.ThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	}).Select<DiskState>([this](PlayerAction x) {
		return state;
	}).Subscribe([this](DiskState x) {
		if (x == G)
			state = R;
		else if (x == B)
			state = G;
		else
			state = B;

		progress = state / 2.0f;
	});

	p->actionSubject
		.Throttle(term)
		.Where([](PlayerAction x) {
		return x.ThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	})
		.Select<DiskState>([this](PlayerAction x) {
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

void Disk::Update()
{
	
	Trigger::Update();
	if (useDebug)
	{
		Debug::DrawTextToWorld(vector2(100, 100), transform->position + vector2::Up * 100, L"원판 사용중", L"Verdana");
		Debug::DrawTextToWorld(vector2(100, 100), transform->position, std::to_wstring(progress * 100), L"Verdana");
	}
	else
	{
		Debug::DrawTextToWorld(vector2(100, 100), transform->position + vector2::Up * 100, L"원판 사용중아님", L"Verdana");
		Debug::DrawTextToWorld(vector2(100, 100), transform->position, std::to_wstring(progress * 100), L"Verdana");
	}


}