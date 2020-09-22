#pragma once
#include "framework.h"
class Editor
{
public: //а, можливо, ще потрібен віртуальний деструктор?
	virtual void OnLBdown(HWND) = 0;
	virtual void OnLBup(HWND) = 0;
	virtual void OnMouseMove(HWND) = 0;
	virtual void OnPaint(HWND) = 0;
};