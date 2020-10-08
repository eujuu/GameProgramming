#pragma once

#include "RGB.h" //색
#include "Vector2.h" //2d 좌표 설정
#include "Vector3.h" //3d 좌표 설정
#include "Colors.h" //색들을 미리 정의(rgb값)
#include "Timer.h"
#include "DrawFunctions.h" //도형 그리기 

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>         // std::this_thread::sleep_for
#include <iostream>
#include <vector>
#include <string>
#include <map>

namespace ej
{
	using vec2 = Vector2<float>;
	using vec3 = Vector3<float>;

	class Game2D
	{
	private:
		//윈도우 창
		int width = 640;
		int height = 480;

		GLFWwindow* glfw_window = nullptr; //창에 대한 포인터

		Timer timer;

		float spf = 1.0f / 60.0f;		 // second(s) per frame(fps의 역수)

		// control options
		std::map<int, bool> key_status;  // key_id, is_pressed
		std::map<int, bool> mbtn_status; // mouse_button_id, is_pressed
		bool draw_grid = true;

	public:
		//생성자
		Game2D()
		{}

		Game2D(const std::string& _title, const int& _width, const int& _height,
			const bool & use_full_screen = false, const int & display_ix = 0);

		~Game2D();

		Game2D & init(const std::string& _title, const int& _width, const int& _height,
			const bool & use_full_screen = false, const int & display_ix = 0);

		void reportErrorAndExit(const std::string& function_name, const std::string& message);

		bool isKeyPressed(const int& key);
		bool isKeyReleased(const int & key);
		bool isKeyPressedAndReleased(const int& key); //눌렀다가 뗀 액션

		bool isMouseButtonPressed(const int& mbtn);
		bool isMouseButtonReleased(const int& mbtn);
		bool isMouseButtonPressedAndReleased(const int& mbtn);

		vec2 getCursorPos(const bool& screen_coordinates = true);

		float getTimeStep(); //한 프레임 당 시간이 얼마나 흘렀는지

		void drawGrid();

		void run(); //중요

		virtual void update()  //중요
		{
			// draw
			// play sound
			// physics update
			// etc.
		}
	};
}