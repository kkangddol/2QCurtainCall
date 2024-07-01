#pragma once
namespace GammaEngine
{
	struct GammaEngineAPI  RaycastResponse { //����ĳ���� ����, ����ü. 
		bool hit; //������ Ray�� ��ü�� ��Ҵ��� ���� Bool��.
		vector2 position; //Ray�� ���� ��ġ ����.
		std::string tag;  //���� ��ü�� �±� ����.
		RaycastResponse() : hit(0),position(vector2()),tag(std::string()){}
	};

	class GammaEngineAPI Physics
	{
	public:
		static RaycastResponse Raycast(vector2 from, vector2 to, std::vector<std::string> tags);
		static RaycastResponse Raycast(vector2 from, vector2 to, std::string tag);
	};
}
