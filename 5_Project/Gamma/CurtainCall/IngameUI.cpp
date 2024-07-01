#include "GammaEngine.h"
#include "IngameUI.h"
#include "Information.h"

using namespace GammaEngine;

IngameUI::IngameUI(GameObject* obj)
	: Component(obj),
	type_(UIType::PAUSE),
	index_(0)
{

}

void IngameUI::Start()
{
	if (type_ == UIType::PAUSE)
	{
		selector_->transform->position = vector2(-1 * 200, 0);
	}
	else if (type_ == UIType::CLEAR)
	{
		selector_->transform->position = vector2(-1 * 200, 150);
	}
}

void IngameUI::OnDisable()
{
	selector_->Disable();

	for (auto& obj : scores_)
	{
		obj->Disable();
	}
}

void IngameUI::OnEnable()
{
	selector_->Enable();

	for (auto& obj : scores_)
	{
		obj->Enable();
	}
}

void IngameUI::StartClear(int score)
{
	scoreValue_ = score;
	for (int i = 0; i < scoreValue_; ++i)
	{
		Tween::Animate(scores_[i]->GetComponent<BitmapRenderer>()->material->brush.w, PLAYBACK::ONCE_FORWARD, 1, EASING::INQUART, 10.1f, (i + 1) * 0.3f);
		Tween::Animate(scores_[i]->transform->scale, PLAYBACK::ONCE_FORWARD, vector2(1, 1), EASING::INOUTEXPO, 10.0f, (i + 1) * 0.3f);
	}

	for (int i = 2; scoreValue_ <= i; --i)
	{
		scores_[i]->Disable();
	}
}

void IngameUI::OnLeftInput()
{
	--index_;

	if (index_ < 0)
	{
		index_ = 2;
	}

	if (type_ == UIType::PAUSE)
	{
		selector_->transform->position = vector2((index_ - 1) * 200, 0);
	}
	else if (type_ == UIType::CLEAR)
	{
		selector_->transform->position = vector2((index_ - 1) * 200, 150);
	}
}

void IngameUI::OnRighttInput()
{
	++index_;
	
	if (2 < index_)
	{
		index_ = 0;
	}

	if (type_ == UIType::PAUSE)
	{
		selector_->transform->position = vector2((index_ - 1) * 200, 0);
	}
	else if (type_ == UIType::CLEAR)
	{
		selector_->transform->position = vector2((index_ - 1) * 200, 150);
	}
}

void IngameUI::OnSelectInput()
{
	switch (index_)
	{
		case 0:
		{
			// 메인메뉴로
			Information::RemoveAll();
			SceneManager::LoadScene("titleScene");
			Time::SetTimeScale(1);
		}
		break;
		
		case 1:
		{
			// 씬 다시 로드
			Information::RemoveAll();
			SceneManager::LoadScene("gameScene");
			Time::SetTimeScale(1);
		}
		break;

		case 2:
		{
			// 옵션
			if (type_ == UIType::PAUSE)
			{

			}
			else if (type_ == UIType::CLEAR)
			{
				// 임시로 메인메뉴로..
				Information::RemoveAll();
				SceneManager::LoadScene("titleScene");
				Time::SetTimeScale(1);
			}
		}
		break;

		default:
			break;
	}
}

void IngameUI::SetSelector(GameObject* obj)
{
	selector_ = obj;
}

void IngameUI::SetType(UIType type)
{
	type_ = type;
}

void IngameUI::AddScore(GameObject* score)
{
	scores_.push_back(score);
}
