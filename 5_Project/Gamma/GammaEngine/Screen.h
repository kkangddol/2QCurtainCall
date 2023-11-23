#pragma once
namespace GammaEngine
{
	/// <summary>
	/// 화면 정보를 저장하는 class
	/// </summary>
	class GammaEngineAPI Screen final : public Singleton<Screen>
	{
	public:
		Screen();
		Screen(int, int);
		~Screen();

	public:
		static void SetSize(int, int);

	public:
		static int width; //현재화면의 너비
		static int height; //현재화면의 높이

	};


}
