#include "framework.h"
#include "editor.h"

class ShapeEditor : public Editor {
protected:
public:
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND);
};