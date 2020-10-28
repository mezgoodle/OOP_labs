#pragma once
#define ID_TOOL_POINT                   32805
#define ID_TOOL_LINE                    32806
#define ID_TOOL_RECT			        32807
#define ID_TOOL_ELLIPSE                 32809
#define IDC_MY_TOOLBAR                  32811

// Declare Toolbar class
class Toolbar {
public:
	void OnCreate(HWND hWnd);
	void OnSize(HWND);
	void OnPointPressed();
	void OnLinePressed();
	void OnRectPressed();
	void OnEllipsePressed();
	void OnNotify(HWND, LPARAM);
	void OffPressed(int);
};
