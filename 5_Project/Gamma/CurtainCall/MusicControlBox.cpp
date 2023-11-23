#include "GammaEngine.h"
#include "GRX.h"
#include "MusicControlBox.h"
#include "Information.h"
#include "Player.h"

MusicControlBox::MusicControlBox(GameObject* t) : Trigger(t)
{
	std::random_device* rd = new std::random_device();
	gen = new std::mt19937((*rd)());
	dist = new std::uniform_int_distribution<int>(0, 3);
	len = new std::uniform_int_distribution<int>(6, 8);
	progress = 0.0f;
}

void MusicControlBox::Use(Player* p)
{
	Trigger::RegistPlayer(p);
	Tween::Animate(p->transform->position.x, PLAYBACK::ONCE_FORWARD, transform->position.x, EASING::LINEAR, 1);

	qte.clear();
	answer.clear();
	for (int i = 0; i < (* len)(*gen); i++)
	{
		qte.push_back((*dist)(*gen));
	}

	for (int i=0; i < qte.size(); i++)
	{
		switch (qte[i])
		{
		case 0:
			infoList.push_back(Information::Create(L"left_arrow"));
			break;
		case 1:
			infoList.push_back(Information::Create(L"up_arrow"));
			break;
		case 2:
			infoList.push_back(Information::Create(L"right_arrow"));
			break;
		case 3:
			infoList.push_back(Information::Create(L"down_arrow"));
			break;
		default:
			break;
		}
		infoList[i]->transform->parent = this->transform;
		infoList[i]->transform->position = vector2(70 * i, -100);
		infoList[i]->GetComponent<BitmapRenderer>()->SetBrush(vector4(1,1,1,1.0f / (i + 1)));
		infoList[i]->isEnabled=true;
	}	
	
	

	//qte ют╥б
	p->actionSubject.Where([this](PlayerAction x) {
		return ( x.buttonLeft == KeyState::pressed || x.buttonRight == KeyState::pressed || x.buttonUp == KeyState::pressed || x.buttonDown == KeyState::pressed);
	}).Throttle(0.2f).Subscribe([this](PlayerAction x) {
		if (qte[0] == 0)
		{
			if (x.buttonLeft != KeyState::pressed)
			{
				user->state = Player::IDLE;
				useDebug = false;
				user = nullptr;
				for (auto info : infoList)
				{
					Destroy(info);
				}
				infoList.clear();
				return;
			}
		}
		if (qte[0] == 1)
		{
			if (x.buttonUp != KeyState::pressed)
			{
				user->state = Player::IDLE;
				useDebug = false;
				user = nullptr;
				for (auto info : infoList)
				{
					Destroy(info);
				}
				infoList.clear();
				return;
			}
			
		}

		if (qte[0] == 2)
		{
			if (x.buttonRight != KeyState::pressed)
			{
				user->state = Player::IDLE;
				useDebug = false;
				user = nullptr;
				for (auto info : infoList)
				{
					Destroy(info);
				}
				infoList.clear();
				return;
			}
		}

		if (qte[0] == 3)
		{
			if (x.buttonDown != KeyState::pressed)
			{
				user->state = Player::IDLE;
				useDebug = false;
				user = nullptr;
				for (auto info : infoList)
				{
					Destroy(info);
				}
				infoList.clear();
				return;
			}
		}

		answer.push_back(qte[0]);
		Destroy(infoList[0]);
		infoList.erase(infoList.begin());
		qte.erase(qte.begin());
		for (int i = 0; i < infoList.size(); i++)
		{
			infoList[i]->transform->position = vector2(70 * i, -100);
			infoList[i]->GetComponent<BitmapRenderer>()->SetBrush(vector4(1, 1, 1, 1.0f / (i + 1)));
		}
		if (qte.size() == 0)
		{
			SoundSystem::Instance()->PathPlay(L"Resources/Music/bird.wav", 30);
			success = true;
			user->state = Player::IDLE;
			useDebug = false;
			user = nullptr;
			for (auto info : infoList)
			{
				Destroy(info);
			}
			infoList.clear();
		}
	});
}

bool MusicControlBox::CheckStatus(int archIndex, int archDown, int archUp, int sound, int rainRatio, int skyIndex, int skyAppear, int actorDown, int actorUp, int actressDown, int actressUp)
{
	if (sound != -1)
	{
		return success;
	}
	return true;
}

void MusicControlBox::InitSuccess()
{
	success = false;
}

void MusicControlBox::Start()
{

}

void MusicControlBox::Update()
{
	Trigger::Update();
	std::wstring str1;
	for (auto x : qte)
	{
		str1.append(std::to_wstring(x));
		str1.append(L" ");
	}
	str1.append(L"\n");
	for (auto x : answer)
	{
		str1.append(std::to_wstring(x));
		str1.append(L" ");
	}
	Debug::DrawTextToWorld(vector2(300, 100), transform->position, str1, L"Verdana",vector4(1,1,0,1));
}