#include "Game2D.h"
#include "PrimitivesGallery.h"
#include "TankExample.h"
#include "FaceExample.h"
#include "WalkingPerson.h"
#include "SolarSystem.h"

namespace jm
{

	class RotatingStarExample : public Game2D 
	{
		//회전은 시간의 개념이 필요
		float time = 0.0f;
		public: 
			void update() override {
				rotate(time * 180.0f); //회전
				drawFilledStar(Colors::gold, 0.4f, 0.25f); //바깥쪽 원의 반지름이 0.4, 안쪽원의 반지름이 0.25
				time += this->getTimeStep();
			}
	};
}
int main(void)
{

	//g키를 누르면 grid나옴
	////jm::MouseExample().init("This is my digital canvas!", 1000, 1000, false).run();
	//jm::Game2D().init("This is my digital canvas!", 1280, 960, false).run();
	jm::RotatingStarExample().init("Rotating Star Example!", 1280, 960, false).run();

	//jm::PrimitivesGallery().init("Primitive Gallery", 1280, 960, false).run();
	//jm::SolarSystem().run();
	//jm::FaceExample().run();
	//jm::WalkingPerson().run();
	//jm::TankExample().run();

	return 0;
}
