#include "GammaEngine.h"
#include "Player.h"
#include "MainCamera.h"
#include "GameManager.h"

using namespace GammaEngine;

MainCamera::MainCamera(GameObject* t) : Component(t)
{

}

MainCamera::~MainCamera()
{

}

void MainCamera::Start()
{

}

void MainCamera::Update()
{
	std::wstring debug;

	if (GameManager::player[0] && GameManager::player[1])
	{
		vector2 midPoint = (GameManager::player[0]->transform->position + GameManager::player[1]->transform->position) / 2;
		float distance = vector2::Distance(GameManager::player[0]->transform->position, GameManager::player[1]->transform->position);
		
		float ortho = GetComponent<Camera>()->orthoScale;
		GetComponent<Camera>()->transform->position = midPoint;
		if (maxPositionX < transform->position.x + Screen::width / 2 * ortho)
		{
			GetComponent<Camera>()->transform->position.x = maxPositionX - Screen::width / 2 * ortho;
		}
		else if (-maxPositionX > transform->position.x - Screen::width / 2 * ortho)
		{
			GetComponent<Camera>()->transform->position.x = -maxPositionX + Screen::width / 2 * ortho;
		}
			
		
		if (maxPositionY < transform->position.y + Screen::height / 2 * ortho)
		{
			GetComponent<Camera>()->transform->position.y = maxPositionY - Screen::height / 2 * ortho;
		}
		else if (-maxPositionY > transform->position.y - Screen::height / 2 * ortho)
		{
			GetComponent<Camera>()->transform->position.y = -maxPositionY + Screen::height / 2 * ortho;
		}
			
		debug.append(std::to_wstring((ortho)));
		debug.append(L" \n  \n");
		debug.append(std::to_wstring((distance * coefficient)));
		Debug::DrawTextToWorld(vector2(100, 100), transform->position, debug, L"Verdana");
		
		if (distance * coefficient > ortho+padding)
		{
			GetComponent<Camera>()->orthoScale += zoomStep;
		}
		else if (distance * coefficient < ortho -padding)
		{
			if(GetComponent<Camera>()->orthoScale >minScale)
				GetComponent<Camera>()->orthoScale -= zoomStep;
		}


		if (maxPositionX < transform->position.x + Screen::width / 2 * ortho)
		{
			GetComponent<Camera>()->orthoScale -= zoomStep;
		}
		else if (-maxPositionX > transform->position.x - Screen::width / 2 * ortho)
		{
			GetComponent<Camera>()->orthoScale -= zoomStep;
		}
		else if (maxPositionY < transform->position.y + Screen::height / 2 * ortho)
		{
			GetComponent<Camera>()->orthoScale -= zoomStep;
		}
		else if (-maxPositionY > transform->position.y - Screen::height / 2 * ortho)
		{
			GetComponent<Camera>()->orthoScale -= zoomStep;
		}

		

	}
	else if (GameManager::player[0])
	{

	}
}


