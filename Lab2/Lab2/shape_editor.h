#pragma once
#include "editor.h"
#include "shape.h"
#include "resource.h"

class ShapeEditor : public Editor // Shape editor class for figures
{
protected:
	int x1, x2, y1, y2;
public:
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND);
	virtual void OnInitMenuPopup(HWND, WPARAM);
};

class ShapeObjectsEditor // Shape editor class for figure objects
{
private:
	ShapeEditor *pse;
public:
	ShapeObjectsEditor(void);
	~ShapeObjectsEditor();
	void StartPointEditor();
	void StartLineEditor();
	void StartRectEditor();
	void StartEllipseEditor();
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
};

class PointEditor : public ShapeEditor
{
public:
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
};

class LineEditor : public ShapeEditor
{
public:
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
};

class RectEditor : public ShapeEditor
{
public:
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
};

class EllipseEditor : public ShapeEditor
{
public:
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
};

