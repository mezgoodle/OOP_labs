#include "shape_editor.h"
#include "framework.h"

static int count = 0;
static bool isPressed = false;
int MY_SHAPE_ARRAY_SIZE = 110;
Shape *pcshape = new Shape * [MY_SHAPE_ARRAY_SIZE];

// ShapeObjectEditor methods ---------------------------------------------------------------

ShapeObjectsEditor::ShapeObjectsEditor()
{
	pse = new PointEditor;
}

ShapeObjectsEditor::~ShapeObjectsEditor()
{
	for (int i = 0; i < count; i++) delete pcshape[i];
}

void ShapeObjectsEditor::StartPointEditor()
{
	if (pse) delete pse;
	pse = new PointEditor;
}

void ShapeObjectsEditor::StartLineEditor()
{
	if (pse) delete pse;
	pse = new LineEditor;
}

void ShapeObjectsEditor::StartRectEditor()
{
	if (pse) delete pse;
	pse = new RectEditor;
}

void ShapeObjectsEditor::StartEllipseEditor()
{
	if (pse) delete pse;
	pse = new EllipseEditor;
}

void ShapeObjectsEditor::OnLBdown(HWND hWnd) {
	if (pse) pse->OnLBdown(hWnd);
}

void ShapeObjectsEditor::OnLBup(HWND hWnd, COLORREF color, BOOL isF) {
	if (pse) pse->OnLBup(hWnd, color, isF);
}

void ShapeObjectsEditor::OnMouseMove(HWND hWnd) {
	if (pse && isPressed) pse->OnMouseMove(hWnd);
}

void ShapeObjectsEditor::OnPaint(HWND hWnd) {
	ShapeEditor* draw = new ShapeEditor;
	draw->OnPaint(hWnd);
}

void ShapeObjectsEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParams) {
	if (pse) pse->OnInitMenuPopup(hWnd, wParams);
}

// ShapeEditor methods -------------------------------------------------------------------

void ShapeEditor::OnLBdown(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x1 = x2 = pt.x;
	y1 = y2 = pt.y;
	isPressed = true;
}

void ShapeEditor::OnLBup(HWND hWnd, COLORREF color, BOOL isF)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	isPressed = false;
}

void ShapeEditor::OnPaint(HWND hWnd) {
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);
	for (int i = 0; i < count; i++) {
		if (pcshape[i]) pcshape[i]->Show(hdc);
	}
	EndPaint(hWnd, &ps);
}

void ShapeEditor::OnMouseMove(HWND hWnd) {}

void ShapeEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParams) {};

//Point

void PointEditor::OnLBdown(HWND hWnd) {
	__super::OnLBdown(hWnd);
}

void PointEditor::OnLBup(HWND hWnd, COLORREF color, BOOL isF) {
	__super::OnLBup(hWnd, color, isF);
	PointShape* Point = new PointShape;
	Point->Set(x1, y1, x2, y2);
	Point->SetColor(color);
	pcshape[count] = Point;
	count++;
	InvalidateRect(hWnd, NULL, TRUE);
}

void PointEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParams) {
	HMENU hMenu, hSubMenu;

	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1);
	if ((HMENU)wParams == hSubMenu) {
		CheckMenuItem(hSubMenu, IDM_POINT, MF_CHECKED);
		CheckMenuItem(hSubMenu, IDM_LINE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_RECTANGLE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_UNCHECKED);
	}
}

//Line 

void LineEditor::OnLBdown(HWND hWnd) {
	__super::OnLBdown(hWnd);
}

void LineEditor::OnLBup(HWND hWnd, COLORREF color, BOOL isF) {
	__super::OnLBup(hWnd, color, isF);
	LineShape* Line = new LineShape;
	Line->Set(x1, y1, x2, y2);
	Line->SetColor(color);
	pcshape[count] = Line;
	count++;
	InvalidateRect(hWnd, NULL, TRUE);
}

void LineEditor::OnMouseMove(HWND hWnd) {
	POINT pt;
	HPEN hPen, hPenOld;
	HDC hdc = GetDC(hWnd);

	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);

	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);

	x2 = pt.x;
	y2 = pt.y;

	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

void LineEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParams) {
	HMENU hMenu, hSubMenu;

	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1);
	if ((HMENU)wParams == hSubMenu) {
		CheckMenuItem(hSubMenu, IDM_POINT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_LINE, MF_CHECKED);
		CheckMenuItem(hSubMenu, IDM_RECTANGLE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_UNCHECKED);
	}
}

//Rect

void RectEditor::OnLBdown(HWND hWnd) {
	__super::OnLBdown(hWnd);
}

void RectEditor::OnLBup(HWND hWnd, COLORREF color, BOOL isF) {
	__super::OnLBup(hWnd, color, isF);
	RectShape* Rect = new RectShape;
	Rect->Set(x1, y1, x2, y2);
	Rect->SetColor(color);
	Rect->SetFill(isF);
	pcshape[count] = Rect;
	count++;
	InvalidateRect(hWnd, NULL, TRUE);
}

void RectEditor::OnMouseMove(HWND hWnd) {
	POINT pt;
	HPEN hPen, hPenOld;
	HDC hdc = GetDC(hWnd);

	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x1, y2);
	LineTo(hdc, x2, y2);
	LineTo(hdc, x2, y1);
	LineTo(hdc, x1, y1);

	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);

	x2 = pt.x;
	y2 = pt.y;

	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x1, y2);
	LineTo(hdc, x2, y2);
	LineTo(hdc, x2, y1);
	LineTo(hdc, x1, y1);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

void RectEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParams) {
	HMENU hMenu, hSubMenu;

	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1);
	if ((HMENU)wParams == hSubMenu) {
		CheckMenuItem(hSubMenu, IDM_POINT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_LINE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_RECTANGLE, MF_CHECKED);
		CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_UNCHECKED);
	}
}

// Ellipse

void EllipseEditor::OnLBdown(HWND hWnd) {
	__super::OnLBdown(hWnd);
}


void EllipseEditor::OnLBup(HWND hWnd, COLORREF color, BOOL isF) {
	__super::OnLBup(hWnd, color, isF);
	EllipseShape* Ellipse = new EllipseShape;
	Ellipse->Set(2 * x1 - x2, 2 * y1 - y2, x2, y2);
	Ellipse->SetColor(color);
	Ellipse->SetFill(isF);
	pcshape[count] = Ellipse;
	count++;
	InvalidateRect(hWnd, NULL, TRUE);
}

void EllipseEditor::OnMouseMove(HWND hWnd) {

	POINT pt;
	HPEN hPen, hPenOld;
	HDC hdc = GetDC(hWnd);

	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	Arc(hdc, 2 * x1 - x2, 2 * y1 - y2, x2, y2, 0, 0, 0, 0);

	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);

	x2 = pt.x;
	y2 = pt.y;

	Arc(hdc, 2 * x1 - x2, 2 * y1 - y2, x2, y2, 0, 0, 0, 0);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

void EllipseEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParams) {
	HMENU hMenu, hSubMenu;

	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1);
	if ((HMENU)wParams == hSubMenu) {
		CheckMenuItem(hSubMenu, IDM_POINT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_LINE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_RECTANGLE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_CHECKED);
	}
}
