#include "framework.h"
#include "shape.h"

Shape::~Shape() {};

void Shape::Set(long x1, long y1, long x2, long y2)
{
	xs1 = x1;
	ys1 = y1;
	xs2 = x2;
	ys2 = y2;
}

void PointShape::Show(HDC hdc) {
	SetPixel(hdc, xs1, ys1, RGB(0, 0, 0)); // Show point
}

void PointShape::WayTrack(HDC hdc) {}


Shape* PointShape::Copy() {
	return new PointShape();
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

void LineShape::WayTrack(HDC hdc) {
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs2, ys2);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

Shape* LineShape::Copy() {
	return new LineShape();
}

void RectShape::Show(HDC hdc) {
	HPEN hPen, hPenOld;
	HBRUSH hBrush, hBrushOld;
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));					// Create pen
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	hBrush = CreateSolidBrush(RGB(192, 192, 192));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	SelectObject(hdc, hBrush);

	Rectangle(hdc, 2 * xs1 - xs2, 2 * ys1 - ys2, xs2, ys2);				// Create rectangle

	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

void RectShape::WayTrack(HDC hdc) {
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	Rectangle(hdc, 2 * xs1 - xs2, 2 * ys1 - ys2, xs2, ys2);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

Shape* RectShape::Copy() {
	return new RectShape();
}

void EllipseShape::Show(HDC hdc) {
	HPEN hPen, hPenOld;
	HBRUSH hBrush, hBrushOld;
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // Create pen
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	SelectObject(hdc, hBrush);

	Ellipse(hdc, xs1, ys1, xs2, ys2);

	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
};

void EllipseShape::WayTrack(HDC hdc) {
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, xs1, ys1, NULL);
	Ellipse(hdc, xs1, ys1, xs2, ys2);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}


Shape* EllipseShape::Copy() {
	return new EllipseShape();
}

void PointLineShape::Show(HDC hdc) {
	long x1, x2, y1, y2;
	x1 = xs1; y1 = ys1; x2 = xs2; y2 = ys2;

	LineShape::Set(x1, y1, x2, y2);
	LineShape::Show(hdc);

	EllipseShape::Set(x1 + 10, y1 + 10, x1 - 10, y1 - 10);
	EllipseShape::Show(hdc);

	EllipseShape::Set(x2 + 10, y2 + 10, x2 - 10, y2 - 10);
	EllipseShape::Show(hdc);

	LineShape::Set(x1, y1, x2, y2);
}

void PointLineShape::WayTrack(HDC hdc) {
	long x1, x2, y1, y2;
	x1 = xs1;
	y1 = ys1;
	x2 = xs2;
	y2 = ys2;
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	Ellipse(hdc, x1 + 10, y1 + 10, x1 - 10, y1 - 10);
	Ellipse(hdc, x2 + 10, y2 + 10, x2 - 10, y2 - 10);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

Shape* PointLineShape::Copy() {
	return new PointLineShape();
}

void CubeShape::Show(HDC hdc) {
	long x1, x2, y1, y2;
	x1 = xs1; y1 = ys1; x2 = xs2; y2 = ys2;

	HPEN hPen, hPenOld;
	HBRUSH hBrush, hBrushOld;
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));					// Create pen
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	hBrush = CreateSolidBrush(RGB(192, 192, 192));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	SelectObject(hdc, hBrush);

	Rectangle(hdc, x1 - 75, y1 - 75, x1 + 75, y1 + 75);		
	Rectangle(hdc, x2 - 75, y2 - 75, x2 + 75, y2 + 75);		// Create rectangle

	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);

	LineShape::Set(x1 - 75, y1 - 75, x2 - 75, y2 - 75);
	LineShape::Show(hdc);

	LineShape::Set(x1 - 75, y1 + 75, x2 - 75, y2 + 75);
	LineShape::Show(hdc);

	LineShape::Set(x1 + 75, y1 + 75, x2 + 75, y2 + 75);
	LineShape::Show(hdc);

	LineShape::Set(x1 + 75, y1 - 75, x2 + 75, y2 - 75);
	LineShape::Show(hdc);

	LineShape::Set(x1, y1, x2, y2);
}

void CubeShape::WayTrack(HDC hdc) {
	long x1, x2, y1, y2;
	x1 = xs1;
	y1 = ys1;
	x2 = xs2;
	y2 = ys2;
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	Rectangle(hdc, x1 - 75, y1 - 75, x1 + 75, y1 + 75);
	Rectangle(hdc, x2 - 75, y2 - 75, x2 + 75, y2 + 75);
	LineTo(hdc, x1, y1);
	MoveToEx(hdc, x1 - 75, y1 - 75, NULL);
	LineTo(hdc, x2 - 75, y2 - 75);
	MoveToEx(hdc, x1 - 75, y1 + 75, NULL);
	LineTo(hdc, x2 - 75, y2 + 75);
	MoveToEx(hdc, x1 + 75, y1 + 75, NULL);
	LineTo(hdc, x2 + 75, y2 + 75);
	MoveToEx(hdc, x1 + 75, y1 - 75, NULL);
	LineTo(hdc, x2 + 75, y2 - 75);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

Shape* CubeShape::Copy() {
	return new CubeShape();
}
