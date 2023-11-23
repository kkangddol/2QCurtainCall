#pragma once
namespace GammaEngine
{
	class UITextSegment
	{
	public:
		UITextSegment();
		~UITextSegment();
		void Render(Matrix3x3);
	
	public:
		vector2 size;
		vector2 position;
		float rotation;
		vector2 scale;
		std::wstring* text;
		std::wstring* font;
		Material* material;
	};
}

