#include "framework.h"
#include "myeditor.h"

int c = 0;
static bool isPressed = false;
static const int MY_SHAPE_ARRAY_SIZE = 110;
Shape** pcshape = new Shape * [MY_SHAPE_ARRAY_SIZE];

MyEditor* MyEditor::p_instance = 0;

MyEditor* MyEditor::getInstance() {
	if (!p_instance) p_instance = new MyEditor();
	return p_instance;
}

MyEditor::~MyEditor() {
	for (int i = 0; i < c; i++) delete pcshape[i];
	delete pcshape;
}

void MyEditor::Start(Shape* shape) {
	pcshape[c] = shape;
}

void MyEditor::OnLBdown(HWND hWnd) {
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x1 = x2 = pt.x;
	y1 = y2 = pt.y;
	isPressed = true;
}

void MyEditor::OnLBup(HWND hWnd) {
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	isPressed = false;
	pcshape[c]->Set(x1, y1, x2, y2);
	c++;
	InvalidateRect(hWnd, NULL, TRUE);
	pcshape[c] = pcshape[c - 1]->Copy();
}

void MyEditor::OnMouseMove(HWND hWnd) {
	if (isPressed) {
		POINT pt;
		HDC hdc = GetDC(hWnd);

		SetROP2(hdc, R2_NOTXORPEN);

		MoveToEx(hdc, x1, y1, NULL);
		pcshape[c]->Set(x1, y1, x2, y2);
		pcshape[c]->WayTrack(hdc);

		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);

		x2 = pt.x;
		y2 = pt.y;

		MoveToEx(hdc, x1, y1, NULL);
		pcshape[c]->Set(x1, y1, x2, y2);
		pcshape[c]->WayTrack(hdc);

		ReleaseDC(hWnd, hdc);
	}
}

void MyEditor::OnPaint(HWND hWnd) {
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);
	for (int i = 0; i < c; i++) {
		if (pcshape[i]) pcshape[i]->Show(hdc);
	}
	EndPaint(hWnd, &ps);
}

std::string MyEditor::GetString() {
	std::string str = "Figure: " + pcshape[c]->GetName() + "|"
		+ "x1: " + std::to_string(x1) + "|"
		+ "y1: " + std::to_string(y1) + "|"
		+ "x2: " + std::to_string(x2) + "|"
		+ "y2: " + std::to_string(y2) + "|";
	return str;
}
