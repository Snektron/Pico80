#ifndef INCLUDE_CORE_VIEW_VIEW_H_
#define INCLUDE_CORE_VIEW_VIEW_H_

#include <eigen3/Eigen/Core>
#include <memory>

class View
{
private:
	float f, n, x, y, width, height;
	Eigen::Matrix4f matrix;

public:
	View();
	View(float far, float near);

	virtual void update();
	virtual void render();
	virtual void resize(float x, float y, float width, float height);

	float getWidth();
	float getHeight();

	virtual ~View() = default;

protected:
	virtual void onUpdate() {};
	virtual void onRender(Eigen::Matrix4f matrix) = 0;
	virtual void onResize(float width, float height) = 0;
};

#endif /* INCLUDE_CORE_VIEW_VIEW_H_ */
