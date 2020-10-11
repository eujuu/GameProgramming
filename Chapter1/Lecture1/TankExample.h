#pragma once

#include "Game2D.h"

namespace ej
{
	class MyTank
	{
	public:
		vec2 center = vec2(0.0f, 0.0f); //��ũ�� �� ��ġ
		//vec2 direction = vec2(1.0f, 0.0f, 0.0f); //ȸ�������� ���

		void draw()
		{
			beginTransformation();
			{
				translate(center);
				drawFilledBox(Colors::green, 0.25f, 0.1f); // body
				translate(-0.02f, 0.1f);
				drawFilledBox(Colors::blue, 0.15f, 0.1f); // turret
				translate(0.15f, 0.0f);
				drawFilledBox(Colors::red, 0.15f, 0.03f);  // barrel
			}
			endTransformation();
		}
	};

	class MyBullet
	{
	public:
		vec2 center = vec2(0.0f, 0.0f);
		vec2 velocity = vec2(0.0f, 0.0f); //�ӵ�

		void draw()
		{
			beginTransformation();
			{
				translate(center);
				drawFilledRegularConvexPolygon(Colors::yellow, 0.02f, 8);
				drawWiredRegularConvexPolygon(Colors::gray, 0.02f, 8);
			}
			endTransformation();
		}

		void update(const float& dt)
		{
			center += velocity * dt; //�Ѿ��� ��ġ�� ��ȭ(�Ѿ��� ���Ͱ�)
		}
	};

	class TankExample : public Game2D
	{
	public:
		MyTank tank;

		//MyBullet *bullet = nullptr; //�Ѿ��� �߻簡 �������� ����(�������ͷ� �ʱ�ȭ)
		std::vector<std::unique_ptr<MyBullet>> bullets;
		
		
		int idx = 0;
		//TODO: allow multiple bullets
		//TODO: delete bullets when they go out of the screen

	public:
		TankExample()
			: Game2D("This is my digital canvas!", 1024, 768, false, 2)
		{}

		~TankExample()
		{
			//if(bullet != nullptr) delete bullet;
		}

		void update() override
		{
			// move tank
			if (isKeyPressed(GLFW_KEY_LEFT))	tank.center.x -= 0.5f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_RIGHT))	tank.center.x += 0.5f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_UP))		tank.center.y += 0.5f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_DOWN))	tank.center.y -= 0.5f * getTimeStep();

			// shoot a cannon ball
			if (isKeyPressedAndReleased(GLFW_KEY_SPACE))
			{
				for (auto& bullet : bullets) {
					if(!bullet) {
						bullet = std::make_unique<MyBullet>();
						//bullet = new MyBullet; //��ź  ����, ��𼱰� delete�� ����� ��.

						bullet->center = tank.center;
						bullet->center.x += 0.2f;
						bullet->center.y += 0.1f;
						bullet->velocity = vec2(1.0f, 0.0f);
						break;
					}
				}
				
			}
			for(auto &bullet: bullets)
				if (bullet) bullet->update(getTimeStep());

			// rendering
			tank.draw();
			for (auto& bullet : bullets)
				if (bullet!=nullptr) bullet->draw();
		}
	};
}