#pragma once
#include "Auravyx/UI/GUI/GUI.h"
#include "Auravyx/Utility/Math/Vec4f.h"
#include "Auravyx/UI/GUI/ScrollBar.h"

#define NO_SCROLL 0
#define SCROLL 1

class ListMenu : public GUI
{
public:

	float x, y;
	float width, height;

	float ySize = 40;

	ListMenu();
	~ListMenu();

	char mode = NO_SCROLL;

	Vec4f backgroundColour = Vec4f::rgbaColour(180, 180, 180, 255);
	Vec4f barColour = Vec4f::rgbaColour(120, 120, 120, 120);

	std::shared_ptr<ScrollBar> scrollbar;

	std::vector<float> sizes;

	void handleResize();

	void update();

	void render();

	void setMode(char mode);

	void setBounds(float x, float y, float width, float height);

	void notifyNewGUI()
	{
		sizes.emplace_back(40.0);
		handleResize();
	}
};

