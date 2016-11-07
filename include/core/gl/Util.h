#ifndef INCLUDE_CORE_GL_UTIL_H_
#define INCLUDE_CORE_GL_UTIL_H_

#include <eigen3/Eigen/Core>

namespace Util
{
	void ortho(Eigen::Matrix4f& matrix,
			   float l, float r, float t, float b, float f, float n);
}

#endif /* INCLUDE_CORE_GL_UTIL_H_ */
