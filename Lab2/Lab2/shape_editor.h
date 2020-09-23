#pragma once
#include "editor.h"
#include "shape.h"
#include "resource.h"

class ShapeEditor : public Editor
{
protected:
	int x1, x2, y1, y2;
public:
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND);
};

class ShapeObjectsEditor
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
};

class PointEditor : public ShapeEditor
{
public:
	void OnLBdown(HWND);
	void OnLBup(HWND);
};

class LineEditor : public ShapeEditor
{
public:
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
};

class RectEditor : public ShapeEditor
{
public:
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
};

class EllipseEditor : public ShapeEditor
{
public:
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
};