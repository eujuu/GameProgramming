//#include "fmod.h"  // c-context
#include "fmod.hpp"
#include <iostream>
#include <conio.h>

/*
	fmod api documentation
	https://www.fmod.com/resources/documentation-api
	freesound.org를 통해 재미있는 음향효과 다운받아보자!
*/

using namespace std;

int main()
{
	cout << "FMOD cpp conext example" << endl;

	FMOD::System     *system(nullptr); //하나를 선언하는게 일반적
	FMOD::Sound      *sound(nullptr);//여러 개의 사운드 이용시 여러 개 선언
	FMOD::Channel    *channel(nullptr); //한 시스템에서 여러 개의 채널 열 수 있음(사운드 여러 개면 채널도 여러 개인 것이 깨짐없이 플레이 가능
	FMOD_RESULT       result; // 작업결과가 잘 나왔는지 사용하는 플래그
	unsigned int      version; 
	void             *extradriverdata(nullptr);

	result = FMOD::System_Create(&system);
	if (result != FMOD_OK) return -1; //제대로 실행됐는지 확인, 문제 발생시 종료/오류 메시지
	
	result = system->getVersion(&version);
	if (result != FMOD_OK) return -1;
	else printf("FMOD version %08x\n", version);

	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata); //채널을 32개까지 사용하겠다.
	if (result != FMOD_OK) return -1;

	//result = system->createSound("singing.wav", FMOD_LOOP_NORMAL, 0, &sound); //Loop ON, 배경음악과 같이 무한히 반복해야하는 음향
	result = system->createSound("singing.wav", FMOD_LOOP_OFF, 0, &sound); // .mp3 files work!
	//wav파일로부터 사운드 생성
	if (result != FMOD_OK) return -1;

	result = system->playSound(sound, 0, false, &channel); //사운드 재생, 한 채널에서 여러 개 사운드도 재생 가능
	if (result != FMOD_OK) return -1;
	//playSound는 실행이 됐을 때 기다려주는게 아니라 그냥 계속 코드 진행됨

	while (true) //while을 통해 프로그램을 계속 실행상태로 유지
	{
		result = system->update(); //update가 없어도 재생은 됨
		if (result != FMOD_OK) return -1;

		//if (channel)
		//{
		//	bool playing = false;
		//	result = channel->isPlaying(&playing); //재생 여부 저장, 재생중이면 true 재생이 끝났으면 false
		//	if (!playing) break; //음악끝났으면 while문 종료
		//}

		cout << "Press 0 to pause, 1 to resume, and x to exit" << endl;
		
		int i = getch(); // i is ASCII code

		if (i == '0')
			channel->setPaused(true);
		else if (i == '1')
			channel->setPaused(false);
		else if (i == 'x')
			break;
	}

	system->release();	
}
