#pragma once
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif
#include "Render.h"

namespace GammaEngine
{
	class GammaEngineAPI Letter
	{
	public:
		class Transform
		{
		public:
			Transform()
				: position(0, 0), rotation(0), scale(1, 1)
			{
			}

			Transform(float x, float y, float rot, float scaleX, float scaleY)
				: position(x, y), rotation(rot), scale(scaleX, scaleY)
			{
			}

		public:
			void SetTransform(float x, float y, float eulerAngle, float scaleX, float scaleY)
			{
				position.x = x;
				position.y = y;
				rotation = eulerAngle;
				scale.x = scaleX;
				scale.y = scaleY;
			}

			void Translate(float x, float y)
			{
				position.x += x;
				position.y += y;
			}

			void Rotate(float eulerAngle)
			{
				rotation += eulerAngle;
			}

			void Scale(float x, float y)
			{
				if (x < 0 || y < 0)
				{
					return;
				}

				scale.x *= x;
				scale.y *= y;
			}

		public:
			Matrix3x3 GetLocalMatrix()
			{
				Matrix3x3 localMatrix;
				localMatrix = Matrix3x3::Scale(scale.x, scale.y) * Matrix3x3::Rotate(rotation) * Matrix3x3::Translation(position.x, position.y);
				return localMatrix;
			}

		public:
			vector2 position;
			float rotation;
			vector2 scale;
		};

	public:
		Letter(wchar_t value);
		~Letter();
		wchar_t value;
		Transform transform;
		Material material;
	private:

	};

}


