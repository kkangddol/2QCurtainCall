#pragma once

#include <windows.h>

class SceneSystem;
class TimeSystem;
class InputSystem;
class CollisionSystem;
class RenderSystem;
class ObjectSystem;

/// <summary>
/// ������ �ھ��.
/// Core������ ���� ���� ��� �ý���(Input,Renderer,Time)�� ���ս��� �����Ѵ�.
/// ���� ������Ʈ���� ������ ���� ������Ʈ�� ����� �� �ֵ��� �Ѵ�.
/// 
/// 2022.12.13 ������ ��
/// </summary>
class Core final
{
public:
	Core();
	~Core();

	void Initialize(const HWND& hWnd, int pScreenWidth, int pScreenHeight);		// ���� �ʱ�ȭ
	void Finalize();						// ���� ����
	void CycleOnce() const;					// ���ǵ� ������� ������ 1ȸ ����Ŭ ��Ŵ
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
