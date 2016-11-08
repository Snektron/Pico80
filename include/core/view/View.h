#ifndef INCLUDE_CORE_VIEW_VIEW_H_
#define INCLUDE_CORE_VIEW_VIEW_H_

#include <memory>

class View
{
protected:
	float f, n;
	int x, y, width, height;

public:
	View();
	View(float far, float near);

	virtual void update();
	virtual void render();
	virtual void resize(int x, int y, int width, int height);

	float getWidth();
	float getHeight();

	virtual ~View() = default;

protected:
	virtual void onUpdate(){};
	virtual void onRender(){};
	virtual void onResize(int width, int height){};
};

typedef std::shared_ptr<View> ViewPtr;

#endif /* INCLUDE_CORE_VIEW_VIEW_H_ */
