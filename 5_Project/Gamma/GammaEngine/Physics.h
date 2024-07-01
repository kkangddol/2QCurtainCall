#pragma once
namespace GammaEngine
{
	struct GammaEngineAPI  RaycastResponse { //레이캐스팅 반응, 구조체. 
		bool hit; //가상의 Ray가 물체에 닿았는지 대한 Bool값.
		vector2 position; //Ray가 닿은 위치 저장.
		std::string tag;  //닿은 물체의 태그 저장.
		RaycastResponse() : hit(0),position(vector2()),tag(std::string()){}
	};

	class GammaEngineAPI Physics
	{
	public:
		static RaycastResponse Raycast(vector2 from, vector2 to, std::vector<std::string> tags);
		static RaycastResponse Raycast(vector2 from, vector2 to, std::string tag);
	};
}
