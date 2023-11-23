#pragma once
using std::function;

/// <summary>
/// Ÿ�̸� �ڵ鷯�� �����ϴ� class
/// </summary>
namespace GammaEngine
{
	template class GammaEngineAPI std::function<void()>;
	class GammaEngineAPI TimerHandler
	{
	public:
		TimerHandler(float, bool, function<void()>);
		~TimerHandler();

	public:
		void Frame();

	public:
		float accumulation = 0;//deltaTime�� ����
		float delay = 0;//������ �ð� accumulation�� ��
		bool timeOut = false;//�̹� ����� Ÿ�̸Ӵ� true�� ��ȯ
		bool loop;//�ݺ� ����
		function<void()> callback;//callback�Լ�
	private:

	};
}


