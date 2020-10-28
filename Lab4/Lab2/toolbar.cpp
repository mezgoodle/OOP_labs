#include "framework.h"
#include "resource1.h"
#include "toolbar.h"

// Required variables
HWND hwndToolBar = NULL;
extern HINSTANCE hInst;
bool point, line, rect, ellipse = 0;
int whatPressed = NULL;

// Create toolbar listener
void Toolbar::OnCreate(HWND hWnd)
{
    TBBUTTON tbb[5];
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
    tbb[4].fsStyle = TBSTYLE_SEP; //роздільник груп кнопок
    tbb[4].idCommand = 4;
    hwndToolBar = CreateToolbarEx(hWnd,
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | CCS_TOP | TBSTYLE_TOOLTIPS,
        IDC_MY_TOOLBAR,
        4, //кількість зображень у BITMAP
        hInst,
        IDB_BITMAP1, //ID ресурсу BITMAP
        tbb,
        5, //кількість кнопок (разом з роздільником)
        24, 24, 24, 24, //розміри кнопок та зображень BITMAP
        sizeof(TBBUTTON));
}

// Change toolbar listener
void Toolbar::OnSize(HWND hWnd) {
	RECT rc, rw;

	if (hwndToolBar) {
		GetClientRect(hWnd, &rc);
		GetWindowRect(hwndToolBar, &rw);
		MoveWindow(hwndToolBar, 0, 0, rc.right - rc.left, rw.bottom - rw.top, FALSE);
	}
}

// Unpress toolbar button
void Toolbar::OffPressed(int id) {
	SendMessage(hwndToolBar, TB_PRESSBUTTON, whatPressed, 0);

	whatPressed = id;
}

// Pressed toolbar point button
void Toolbar::OnPointPressed() {
	point = !point;
	line = rect = ellipse = 0;
	OffPressed(ID_TOOL_POINT);
	SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_POINT, point);
}

// Pressed toolbar line button
void Toolbar::OnLinePressed() {
	line = !line;
	point = rect = ellipse = 0;
	OffPressed(ID_TOOL_LINE);
	SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_LINE, line);
}

// Pressed toolbar rectangle button
void Toolbar::OnRectPressed() {
	rect = !rect;
	point = line = ellipse = 0;
	OffPressed(ID_TOOL_RECT);
	SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_RECT, rect);
}

// Pressed toolbar ellipse button
void Toolbar::OnEllipsePressed() {
	ellipse = !ellipse;
	point = line = rect = 0;
	OffPressed(ID_TOOL_ELLIPSE);
	SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_ELLIPSE, ellipse);
}

// Notify current pressed button
void Toolbar::OnNotify(HWND hWnd, LPARAM lParam)
{
    LPNMHDR pnmh = (LPNMHDR)lParam;
    LPCSTR pText;
    if (pnmh->code == TTN_NEEDTEXT)
    {
        LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParam;
        switch (lpttt->hdr.idFrom)
        {
        case ID_TOOL_POINT:
            pText = "Крапка";
            break;
        case ID_TOOL_LINE:
            pText = "Лінія";
            break;
        case ID_TOOL_RECT:
            pText = "Прямокутник";
            break;
        case ID_TOOL_ELLIPSE:
            pText = "Еліпс";
            break;
        default: pText = "Щось невідоме";
        }
        lstrcpy(lpttt->szText, pText);
    }
}
