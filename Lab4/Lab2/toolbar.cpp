#include "framework.h"
#include "resource1.h"
#include "toolbar.h"

HWND hwndToolBar = NULL;
extern HINSTANCE hInst;
bool point, line, rect, ellipse, pointline, cube = 0;
int whatPressed = NULL;

void Toolbar::OnCreate(HWND hWnd)
{
	TBBUTTON tbb[7];
	ZeroMemory(tbb, sizeof(tbb));
	tbb[0].iBitmap = 0;
	tbb[0].fsState = TBSTATE_ENABLED;
	tbb[0].fsStyle = TBSTYLE_BUTTON;
	tbb[0].idCommand = ID_TOOL_POINT;
	tbb[1].iBitmap = 1;
	tbb[1].fsState = TBSTATE_ENABLED;
	tbb[1].fsStyle = TBSTYLE_BUTTON;
	tbb[1].idCommand = ID_TOOL_LINE;
	tbb[2].iBitmap = 2; //індекс зображення у BITMAP
	tbb[2].fsState = TBSTATE_ENABLED;
	tbb[2].fsStyle = TBSTYLE_BUTTON;
	tbb[2].idCommand = ID_TOOL_RECT;
	tbb[3].iBitmap = 3;
	tbb[3].fsState = TBSTATE_ENABLED;
	tbb[3].fsStyle = TBSTYLE_BUTTON;
	tbb[3].idCommand = ID_TOOL_ELLIPSE;
	tbb[4].iBitmap = 4;
	tbb[4].fsState = TBSTATE_ENABLED;
	tbb[4].fsStyle = TBSTYLE_BUTTON;
	tbb[4].idCommand = ID_TOOL_LINE_POINT;
	tbb[5].iBitmap = 5;
	tbb[5].fsState = TBSTATE_ENABLED;
	tbb[5].fsStyle = TBSTYLE_BUTTON;
	tbb[5].idCommand = ID_TOOL_CUBE;
	tbb[6].iBitmap = 6;
	tbb[6].fsState = TBSTATE_ENABLED;
	tbb[6].fsStyle = TBSTYLE_SEP; //роздільник груп кнопок
	tbb[6].idCommand = 6;
	hwndToolBar = CreateToolbarEx(hWnd,
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | CCS_TOP | TBSTYLE_TOOLTIPS,
		IDC_MY_TOOLBAR,
		6, //кількість зображень у BITMAP
		hInst,
		IDB_BITMAP1, //ID ресурсу BITMAP
		tbb,
		6, //кількість кнопок (разом з роздільником)
		24, 24, 24, 24, //розміри кнопок та зображень BITMAP
		sizeof(TBBUTTON));
}

void Toolbar::OnSize(HWND hWnd) {
	RECT rc, rw;

	if (hwndToolBar) {
		GetClientRect(hWnd, &rc);
		GetWindowRect(hwndToolBar, &rw);
		MoveWindow(hwndToolBar, 0, 0, rc.right - rc.left, rw.bottom - rw.top, FALSE);
	}
}

void Toolbar::OnPointPressed(HWND hWnd) {
	SetWindowTextA(hWnd, "Крапка");
	point = 1;
	line = rect = ellipse = pointline = cube = 0;
	OffPressed(ID_TOOL_POINT);
	SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_POINT, point);
}

void Toolbar::OnLinePressed(HWND hWnd) {
	SetWindowTextA(hWnd, "Лінія");
	line = 1;
	point = rect = ellipse = pointline = cube = 0;
	OffPressed(ID_TOOL_LINE);
	SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_LINE, line);
}

void Toolbar::OnRectPressed(HWND hWnd) {
	SetWindowTextA(hWnd, "Прямокутник");
	rect = 1;
	point = line = ellipse = pointline = cube = 0;
	OffPressed(ID_TOOL_RECT);
	SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_RECT, rect);
}

void Toolbar::OnEllipsePressed(HWND hWnd) {
	SetWindowTextA(hWnd, "Еліпс");
	ellipse = 1;
	point = line = rect = pointline = cube = 0;
	OffPressed(ID_TOOL_ELLIPSE);
	SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_ELLIPSE, ellipse);
}

void Toolbar::OnPointLinePressed(HWND hWnd) {
	SetWindowTextA(hWnd, "Лінія з точками");
	pointline = 1;
	point = line = rect = ellipse = cube = 0;
	OffPressed(ID_TOOL_LINE_POINT);
	SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_LINE_POINT, pointline);
}

void Toolbar::OnCubePressed(HWND hWnd) {
	SetWindowTextA(hWnd, "Куб");
	cube = 1;
	point = line = rect = ellipse = pointline = 0;
	OffPressed(ID_TOOL_CUBE);
	SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_CUBE, cube);
}

void Toolbar::OnNotify(HWND hWnd, LPARAM lParams) {
	LPNMHDR pnhm = (LPNMHDR)lParams;
	LPSTR pText;

	if (pnhm->code == TTN_NEEDTEXT)
	{
		LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParams;
		switch (lpttt->hdr.idFrom)
		{
		case ID_TOOL_POINT:
			pText = (LPSTR)"Точка";
			break;
		case ID_TOOL_LINE:
			pText = (LPSTR)"Лінія";
			break;
		case ID_TOOL_RECT:
			pText = (LPSTR)"Прямокутник";
			break;
		case ID_TOOL_ELLIPSE:
			pText = (LPSTR)"Еліпс";
			break;
		case ID_TOOL_LINE_POINT:
			pText = (LPSTR)"Лінія з точками";
			break;
		case ID_TOOL_CUBE:
			pText = (LPSTR)"Куб";
			break;
		default: pText = (LPSTR)"Щось невідоме";
		}
		lstrcpy(lpttt->szText, pText);
	}
}

void Toolbar::OffPressed(int id) {
	SendMessage(hwndToolBar, TB_PRESSBUTTON, whatPressed, 0);
	whatPressed = id;
}