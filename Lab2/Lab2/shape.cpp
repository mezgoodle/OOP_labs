#include "framework.h"
#include "shape.h"

// Get coords of points
void Shape::Set(long x1, long y1, long x2, long y2) {
	xs1 = x1;
	ys1 = y1;
	xs2 = x2;
	ys2 = y2;
}

void PointShape::Show(HDC hdc) {
	SetPixel(hdc, xs1, ys1, RGB(0, 0, 0)); // Show point
}

void LineShape::Show(HDC hdc) {
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // Create pen
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs2, ys2);						// Create line

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}


void RectShape::Show(HDC hdc) {
	HPEN hPen, hPenOld;
	HBRUSH hBrush, hBrushOld;
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));	// Create pen
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	hBrush = CreateSolidBrush(RGB(255, 255, 255));
    hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	SelectObject(hdc, hBrush);

	Rectangle(hdc, xs1, ys1, xs2, ys2);				// Create rectangle

	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

void EllipseShape::Show(HDC hdc) {
	HPEN hPen, hPenOld;
	HBRUSH hBrush, hBrushOld;
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // Create pen
	hPenOld = (HPEN)SelectObject(hdc, hPen);

    Arc(hdc, xs1, ys1, xs2, ys2, 0, 0, 0, 0);    // Create ellipse

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
};
