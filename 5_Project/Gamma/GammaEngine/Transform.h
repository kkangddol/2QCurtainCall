#pragma once
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

struct GammaEngineAPI vector2;

/// <summary>
/// ��ġ ũ�� ȸ�� ������ �����ϴ� ������Ʈ
/// </summary>
namespace GammaEngine {
	class GammaEngineAPI Transform : public Component
	{
	public:
		Transform(GameObject* t);
		~Transform();
	public:
		vector2 GetWorldPosition();
		vector2 GetWorldScale(); 
		void SetWorldPosition(vector2 v);
		void SetParent(Transform* t, bool keep = false);
		void SetWorldScale(vector2 v);
		Matrix3x3 GetWorldMatrix();
	public:
		vector2 position;
		float rotation;
		vector2 scale;
		Transform* parent;
	};
}

