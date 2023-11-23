#pragma once
///생성한 오브젝트와 속해있는 컴포넌트를 하나의 함수로 묶어서 그대로 쓸 수 있게 해두는 곳이다.
using namespace GammaEngine;
namespace Menu {
	//카메라
	GameObject* CreateCamera(Scene* scene);

	GameObject* CreateBackgroundLight(Scene* scene, float x, float y);

	GameObject* CreateBackground(Scene* scene, float x, float y);

	GameObject* CreateBGM(Scene*);
}
