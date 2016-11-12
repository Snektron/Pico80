#ifndef INCLUDE_CORE_VIEW_LAYOUT_H_
#define INCLUDE_CORE_VIEW_LAYOUT_H_

#include "core/view/View.h"

#define MATCH_PARENT -1
#define WRAP_CONTENT -2

enum Orientation
{
	Vertical,
	Horizontal
};

class ViewGroup;

class Layout
{
public:
	virtual Vector2i measure(const Vector2i& parentSize, ViewGroup *group);
	virtual void onLayout(const Vector2i& pos, const Vector2i& size, ViewGroup *group);
	virtual ~Layout() = default;
	typedef std::shared_ptr<Layout> Ptr;
};

class BoxLayout
{
private:
	int margin;
	Vector2i size;
	Orientation orientation;

public:
	BoxLayout(Vector2i& size, int margin, Orientation orientation);
	Vector2i measure(const Vector2i& parentSize, ViewGroup *group);
	void onLayout(const Vector2i& pos, const Vector2i& size, ViewGroup *group);

private:
	Vector2i measureWrap(ViewGroup *group);
};

#endif /* INCLUDE_CORE_VIEW_LAYOUT_H_ */
