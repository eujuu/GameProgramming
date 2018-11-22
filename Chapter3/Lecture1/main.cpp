#include "Game2D.h"
#include "Examples/PrimitivesGallery.h"
#include "RandomNumberGenerator.h"
#include <vector>
#include <memory>

namespace jm
{
	class RigidCircle
	{
	public:
		vec2 pos;
		vec2 vel;
		float radius = 0.1f;

		void draw()
		{
			beginTransformation();
			{
				translate(pos);
				drawFilledCircle(Colors::hotpink, radius);
				setLineWidth(2.0f);
				drawWiredCircle(Colors::black, radius);
			}
			endTransformation();
		}
	};

	class Example : public Game2D
	{
	public:
		RigidCircle rigid_body;

		Example()
			: Game2D()
		{
			rigid_body.pos = vec2(-0.8f, 0.3f);
			rigid_body.vel = vec2(1.0f, 0.0f);
		}

		void update() override
		{
			rigid_body.draw();
		}
	};
}

int main(void)
{
	jm::Example().run();

	return 0;
}
