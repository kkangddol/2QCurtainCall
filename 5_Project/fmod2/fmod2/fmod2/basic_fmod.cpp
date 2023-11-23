
#include "fmod.hpp"
#include "Prev.h"

int main()
{
	// FMOD �ý��� (�ϳ��� ����)
	FMOD::System* system(nullptr);
	// FMOD ���� ������ �ִ� ���� (�迭�� �̿��� ���� ����)
	FMOD::Sound* sound(nullptr);
	FMOD::Sound* sound2[100];
	// FMOD ����ϴ� ä�� (�迭�� �̿��� ���� ����)
	FMOD::Channel* channel(nullptr);
	FMOD::Channel* channel2[100];

	// FMOD �۾���� Ȯ���ϴ� �÷���
	FMOD_RESULT result;

	// FMOD ���� Ȯ��
	unsigned int version;

	void* extradriverdata(nullptr);

	// FMOD �ý��� ���� (������ �� ��!!)
	FMOD::System_Create(&system);

	// ���� ��������
	system->getVersion(&version);
	/*if (result != FMOD_OK)
		return -1;*/
		//cout << version << endl;

		// �ý��� �ʱ�ȭ�ϱ�
	system->init(200, FMOD_INIT_NORMAL, NULL);

	// ���带 �����Ѵ� (FMOD_LOOP_NORMAL, FMOD_LOOP_OFF)
	system->createSound("singing.wav", 1, 0, &sound2[0]);
	system->createSound("wave.mp3", FMOD_LOOP_NORMAL, 0, &sound2[1]);

	// ���带 ����Ѵ�
	system->playSound(sound2[0], 0, false, &channel2[0]);
	system->playSound(sound2[1], 0, false, &channel2[0]);

	while (true)
	{
		// playSound �Լ��� �뷡�� ����ǰ� �����⸦ ��ٸ��� �ʴ´�.
		// �Լ��� ������ڸ��� �ٷ� �Ѿ�⶧���� �߰��� ��� ���ư��� ������ �ʿ��ϴ�.
	}

	// �ý����� �����Ѵ�
	system->release();
}