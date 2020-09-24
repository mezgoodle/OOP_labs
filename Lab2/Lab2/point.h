#pragma once
#include "framework.h"
#include "shape_editor.h"

class PointEditor : public ShapeEditor
{
public:
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
};