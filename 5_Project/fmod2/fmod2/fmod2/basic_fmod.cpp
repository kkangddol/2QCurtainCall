
#include "fmod.hpp"
#include "Prev.h"

int main()
{
	// FMOD 시스템 (하나만 선언)
	FMOD::System* system(nullptr);
	// FMOD 사운드 파일을 넣는 사운드 (배열을 이용해 다중 선언)
	FMOD::Sound* sound(nullptr);
	FMOD::Sound* sound2[100];
	// FMOD 재생하는 채널 (배열을 이용해 다중 선언)
	FMOD::Channel* channel(nullptr);
	FMOD::Channel* channel2[100];

	// FMOD 작업결과 확인하는 플래그
	FMOD_RESULT result;

	// FMOD 버전 확인
	unsigned int version;

	void* extradriverdata(nullptr);

	// FMOD 시스템 생성 (무조건 한 번!!)
	FMOD::System_Create(&system);

	// 버전 가져오기
	system->getVersion(&version);
	/*if (result != FMOD_OK)
		return -1;*/
		//cout << version << endl;

		// 시스템 초기화하기
	system->init(200, FMOD_INIT_NORMAL, NULL);

	// 사운드를 생성한다 (FMOD_LOOP_NORMAL, FMOD_LOOP_OFF)
	system->createSound("singing.wav", 1, 0, &sound2[0]);
	system->createSound("wave.mp3", FMOD_LOOP_NORMAL, 0, &sound2[1]);

	// 사운드를 재생한다
	system->playSound(sound2[0], 0, false, &channel2[0]);
	system->playSound(sound2[1], 0, false, &channel2[0]);

	while (true)
	{
		// playSound 함수는 노래가 재생되고 끝나기를 기다리지 않는다.
		// 함수가 실행되자마자 바로 넘어가기때문에 중간에 계속 돌아가는 구문이 필요하다.
	}

	// 시스템을 해제한다
	system->release();
}