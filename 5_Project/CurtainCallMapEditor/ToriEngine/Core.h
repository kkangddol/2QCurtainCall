#pragma once

#include <windows.h>

class SceneSystem;
class TimeSystem;
class InputSystem;
class CollisionSystem;
class RenderSystem;
class ObjectSystem;

/// <summary>
/// 엔진의 코어다.
/// Core에서는 엔진 내의 모든 시스템(Input,Renderer,Time)을 집합시켜 조립한다.
/// 데모 프로젝트에서 엔진에 여러 오브젝트를 등록할 수 있도록 한다.
/// 
/// 2022.12.13 강석원 집
/// </summary>
class Core final
{
public:
	Core();
	~Core();

	void Initialize(const HWND& hWnd, int pScreenWidth, int pScreenHeight);		// 엔진 초기화
	void Finalize();						// 엔진 정리
	void CycleOnce() const;					// 정의된 순서대로 엔진을 1회 싸이클 시킴
	void Resize(int width, int height);

public:
	static int screenWidth;
	static int screenHeight;

private:
	SceneSystem& sceneSystem_;
	TimeSystem& timeSystem_;
	InputSystem& inputSystem_;
	CollisionSystem& collisionSystem_;
	RenderSystem& renderSystem_;
	ObjectSystem& objectSystem_;

	void PhysicsUpdate() const;
	void Input() const;
	void Update() const;
	void Render() const;
};
