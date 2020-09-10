#include "framework.h"
#include "module1.h"
#include "module3.h"

HINSTANCE hinst1;

static BOOL CALLBACK Work_MOD1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int Func_MOD1(HINSTANCE hInst, HWND hWnd)
{
    return DialogBox(hInst, MAKEINTRESOURCE(IDD_WORK_MOD1), hWnd, Work_MOD1);
}

BOOL onClick(HWND hDlg, WPARAM wParam)
{
    return EndDialog(hDlg, LOWORD(wParam));
}

// First callback
BOOL CALLBACK Work_MOD1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
        case WM_COMMAND:
            switch(LOWORD(wParam)) 
            {
                case IDC_CANCEL_MOD1:
                    onClick(hDlg, wParam);
                    DefWindowProc(hDlg, message, wParam, lParam);
                    return TRUE;
                case IDC_NEXT_MOD1:
                    onClick(hDlg, wParam);
                    Func_MOD3(hinst1, hDlg);
                    return TRUE;
            }
            break;
        case WM_CLOSE:
            EndDialog(hDlg, 0);
        break;
    }
    return FALSE;
}
