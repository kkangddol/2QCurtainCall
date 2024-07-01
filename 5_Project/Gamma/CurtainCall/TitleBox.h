#pragma once
///������ ������Ʈ�� �����ִ� ������Ʈ�� �ϳ��� �Լ��� ��� �״�� �� �� �ְ� �صδ� ���̴�.
using namespace GammaEngine;
namespace Title {
	//ī�޶�
	GameObject* CreateCamera(Scene* scene);

	GameObject* CreateBackgroundLight(Scene* scene, float x, float y);

	GameObject* CreateBackground(Scene* scene, float x, float y);

	GameObject* CreateManager(Scene* scene, float x, float y);

	GameObject* CreateBGM(Scene*);

	GameObject* CreateBlock(Scene* scene, float x, float y, float sizeX, float sizeY);

	GameObject* CreateControlBox(Scene* scene, float x, float y);
}
