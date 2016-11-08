#ifndef INCLUDE_EMU_DROPDOWNVIEW_H_
#define INCLUDE_EMU_DROPDOWNVIEW_H_

#include "core/view/SingleView.h"

class DropdownView : public SingleView
{
public:
	DropdownView(ViewPtr child):
		SingleView(child)
	{}

	virtual void onRender(Eigen::Matrix4f& mv, Eigen::Matrix4f& p)
	{

	}
};

#endif /* INCLUDE_EMU_DROPDOWNVIEW_H_ */
