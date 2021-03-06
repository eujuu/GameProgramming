#include "Game2D.h"
#include "PrimitivesGallery.h"
#include "TankExample.h"
#include "FaceExample.h"
#include "WalkingPerson.h"
#include "SolarSystem.h"

namespace ej
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
	/*
	class TransformationsExample : public Game2D 
	{
		public:
			void update() override
			{
				beginTransformation();
				//계속 점을 이동 시키는 건 귀찮으니 좌표계 자체를 이동시킨다!(이동은 계속 반영됨)
				translate(0.1f, 0.0f);

				const float dx = 0.1f; //움직일 거리, Translate되는 거리가 달라진다!
				const float dy = 0.2f;
				
				//점 그리기
				
				//const vec2 point(0.0f, 0.0f); //2차원 공간에서의 위치, 원점 표현
				//drawPoint(Colors::green, point, 5.0f);

				//선 그리기
				const vec2 p0(0.0f , 0.0f);
				const vec2 p1(0.5f , 0.5f);
				const vec2 p2(0.5f, 0.0f);
				//drawLine(Colors::red, p0, Colors::blue, p1);

				//삼각형 그리기(선 3개로)
				//형태를 유지하면서 이동 시키는 것 == Translation
				drawLine(Colors::red, p0, Colors::blue, p1);
				drawLine(Colors::red, p1, Colors::blue, p2);
				drawLine(Colors::red, p2, Colors::blue, p0);
				
				endTransformation(); //좌표계 원점으로

				translate(-0.1f, 0.0f);
				drawLine(Colors::red, p0, Colors::blue, p1);
				drawLine(Colors::red, p1, Colors::blue, p2);
				drawLine(Colors::red, p2, Colors::blue, p0);

			}
	};
	*/
	//rotation
	class TransformationsExample : public Game2D
	{
	public:
		void update() override {
			setLineWidth(5.0f);
			drawWiredBox(Colors::gold, 0.5f, 0.25f); //원점을 기준으로 정의되어 있다.

			beginTransformation();
			rotate(30.0f); //원점에 대해 회전 됨.
			drawWiredBox(Colors::skyblue, 0.5f, 0.25f);
			endTransformation();

			beginTransformation(); //컴퓨터 그래픽스는 아래 함수들이 역순으로 적용이 된다.
									//즉, 박스 그린 후 회전 적용, translate적용이 되므로 rotate가 원점에 대해 회전이 되는 것이 이상하지 않음
			translate(0.25f, 0.0f);
			rotate(30.0f);
			drawWiredBox(Colors::red, 0.5f, 0.25f);
			endTransformation();

			beginTransformation();
			rotate(30.0f);
			translate(0.25f, 0.0f);
			drawWiredBox(Colors::blue, 0.5f, 0.25f);
			endTransformation();

		}
	};
	//원점 이동 후 회전
	class TransformationsExample2 : public Game2D {
	public:
		void update() override {
			setLineWidth(3.0f);
			const vec2 center_of_rot(-0.4f, 0.0f);//이 점에 대해 회전 시키자!
			drawWiredBox(Colors::gold, 0.5f, 0.25f);
			
			//회전 중심 원점 이동
			translate(center_of_rot);
			rotate(45.0f);
			translate(-center_of_rot);
			drawWiredBox(Colors::olive, 0.5f, 0.25f);
			drawPoint(Colors::black, center_of_rot, 5.0f);
			
		}
	};
	//scailing
	class TransformationsExample3 : public Game2D {
	public:
		float time = 0;
		void update() override {
			setLineWidth(3.0f);
			
			
			rotate(time * 90.0f);
			translate(0.5f, 0.0f);
			rotate(time * 90.0f);
			scale(2.0f, 0.25f);
			drawWiredBox(Colors::gold, 0.5f, 0.5f);
			time += this->getTimeStep();
		}
	};
	class MouseExample : public Game2D {
	public:
		void update() override {
			//윈도우 좌표계
			//const vec2 mouse_pos = getCursorPos(false);
			// window에서 제공하는 api 사용시, 좌측 상단이 0,0이고 우측하단이 해상도-1, 해상도 -1을 가지게 됨
			
			//화면 좌표계에서의 마우스좌표 위치
			const vec2 mouse_pos = getCursorPos(true);
			// 화면 중간이 0,0이 됨
			//std::cout << mouse_pos << std::endl;
			
			//mouse position 위치에 원을 그린다.
			if (isMouseButtonPressed(GLFW_MOUSE_BUTTON_1)) {
				translate(mouse_pos);
				drawFilledCircle(Colors::gold, 0.05f);
			}
			if (isMouseButtonPressed(GLFW_MOUSE_BUTTON_2)) {
				translate(mouse_pos);
				drawFilledCircle(Colors::red, 0.05f);
			}
		}
	};
	void drawHouse(const RGB& roof_color, const vec2& pos, const float& angle =0.0f) {
		beginTransformation(); //house
		{
			translate(pos);
			rotate(angle);
			//body
			drawFilledBox(Colors::yellow, 0.2f, 0.2f);

			//roof
			drawFilledTriangle(roof_color, { -0.13f,  0.1f }, { 0.13f, 0.1f }, { 0.0f, 0.2f });
			drawWiredTriangle(roof_color, { -0.13f,  0.1f }, { 0.13f, 0.1f }, { 0.0f, 0.2f });

			//window
			drawFilledBox(Colors::skyblue, 0.1f, 0.1f);
			drawWiredBox(Colors::gray, 0.1f, 0.1f);
			drawLine(Colors::gray, { 0.0f, -0.05f }, Colors::gray, { 0.0f, 0.05f });
			drawLine(Colors::gray, { -0.05f, 0.0f }, Colors::gray, { 0.05f, 0.0f });

		}
		endTransformation();
	}
	class Example : public Game2D {
	public:
		void update() override {
			//매개변수를 활용하여 일반화 시키기!
			drawHouse(Colors::blue, { -0.5f, 0.0f });  //left
			drawHouse(Colors::red, vec2(0.0f, 0.0f), 10.0f); //center
			drawHouse(Colors::olive, { 0.5f, 0.0f }); //right
			
		}
		
	};

	
}
int main(void)
{

	//g키를 누르면 grid나옴
	//ej::MouseExample().init("This is my digital canvas!", 1000, 1000, false).run();
	//jm::Game2D().init("This is my digital canvas!", 1280, 960, false).run();
	//jm::RotatingStarExample().init("Rotating Star Example!", 1280, 960, false).run();
	//ej::TransformationsExample().init("Point!", 1280, 960, false).run();
	//ej::TransformationsExample3().init("Desired Postion Rotation", 1280, 960, false).run();
	//ej::PrimitivesGallery().init("Primitive Gallery", 1280, 960, false).run();
	//ej::SolarSystem().run(); //lecture2 homework
	//ej::FaceExample().run();
	//ej::WalkingPerson().run();
	//ej::TankExample().run();
	ej::Example().run();
	
	return 0;
}
