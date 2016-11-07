#ifndef INCLUDE_CORE_GL_UTIL_H_
#define INCLUDE_CORE_GL_UTIL_H_

#include <eigen3/Eigen/Core>

namespace Util
{
	Eigen::Matrix4f ortho(int l, int r, int t, int b, int n, int f)
	{
		Eigen::Matrix4f matrix;
		matrix << 2.0 / (r - l), 0, 0, -(r + l) / (r - l),
				 0,  2.0 / (t - b), 0, -(t + b) / (t - b),
				 0, 0, -2.0 / (f - n), -(f + n) / (f - n),
				 0, 0, 0, 1;
		return matrix;
	}
}

#endif /* INCLUDE_CORE_GL_UTIL_H_ */
