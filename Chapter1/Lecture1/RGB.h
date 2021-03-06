#pragma once

#include "Vector3.h"

namespace ej
{
	class RGB : public Vector3<float>
	{
		using BASE = Vector3<float>;

	public:
		RGB(const float & fr, const float & fg, const float & fb)
			: BASE(fr, fg, fb)
		{}

		// integer type rgb values are divided by 255.0f because OpenGL uses real rgb values.
		// 실수로 바꾸어준다.(0~255의 int대신 실수를 인식하기 때문)
		RGB(const int & cr, const int & cg, const int & cb)
			: BASE(static_cast<float>(cr) / 255.0f, static_cast<float>(cg) / 255.0f, static_cast<float>(cb) / 255.0f)
		{}

		RGB(const RGB & _rgb)
			: BASE(_rgb.r, _rgb.g, _rgb.b)
		{}

		~RGB()
		{
		}
	};
}
