#include "PicoView.h"
#include <memory>
#include <algorithm>
#include "core/view/RatioView.h"
#include "core/view/MarginView.h"
#include "core/view/ListView.h"
#include "core/view/BoxView.h"
#include "emu/DropdownView.h"
#include "emu/EmulatorView.h"

PicoView::PicoView()
{
	emulator = std::make_shared<EmulatorView>();
	View::Ptr dd = std::make_shared<DropdownView>(emulator);
	View::Ptr ratio = std::make_shared<RatioView>(1, dd);
	View::Ptr margin = std::make_shared<MarginView>(0.9, ratio);

	View::Ptr box2 = std::make_shared<BoxView>(nvgRGBf(0.99, 0.99, 0.99));
	View::Ptr dd2 = std::make_shared<DropdownView>(box2);
	View::Ptr margin2 = std::make_shared<MarginView>(0.95, dd2);
	addChild(margin2);
	addChild(margin);
}

void PicoView::onTick()
{
	emulator->onTick();
}

void PicoView::onLayout(const Vector2i& pos, const Vector2i& size)
{
	View::onLayout(pos, size);

	View::Ptr left = getChild(0);
	View::Ptr right = getChild(1);

	int mid = size.x() / 2;
	if (left)
		left->onLayout(Vector2i::Zero(), Vector2i(mid, size.y()));
	if (right)
		right->onLayout(Vector2i(mid, 0), Vector2i(size.x() - mid, size.y()));
}

void PicoView::onMouseMoveEvent(MouseMoveEvent& event)
{
	ViewGroup::onMouseMoveEvent(event);
}

bool PicoView::onMouseButtonEvent(MouseButtonEvent& event)
{
	return true;
}
