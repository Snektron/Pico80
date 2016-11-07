#include "core/gl/Util.h"

namespace Util
{
	void ortho(Eigen::Matrix4f& matrix,
			   float l, float r, float t, float b, float f, float n)
	{
		matrix << 2.0 / (r - l) , 0, 0, -(r + l) / (r - l),
				0, 2.0 / (t - b), 0, -(t + b) / (t - b),
				0, 0, -2.0 / (f - n), -(f + n) / (f - n),
				0, 0, 0, 1;
	}
}
