#pragma once
///������ ������Ʈ�� �����ִ� ������Ʈ�� �ϳ��� �Լ��� ��� �״�� �� �� �ְ� �صδ� ���̴�.
using namespace GammaEngine;
namespace Menu {
	//ī�޶�
	GameObject* CreateCamera(Scene* scene);

	GameObject* CreateBackgroundLight(Scene* scene, float x, float y);

	GameObject* CreateBackground(Scene* scene, float x, float y);

	GameObject* CreateBGM(Scene*);
}
