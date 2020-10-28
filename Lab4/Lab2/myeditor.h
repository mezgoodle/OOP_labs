#pragma once
#include "shape.h"
#include "resource.h"

class MyEdior
{
public:
	static MyEditor* getInstance();
	int x1, y1, x2, y2;
	~MyEditor();
	void Start(Shape*);
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND);

private:
	static MyEditor* p_instance;
	MyEditor() {};
	MyEditor(const MyEditor&);
};

extern Shape** pcshape;
extern int c;
