#include "framework.h"
#include "module1.h"
#include "module3.h"

HINSTANCE hinst3;

static BOOL CALLBACK Work_MOD3(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int Func_MOD3(HINSTANCE hInst, HWND hWnd)
{
    return DialogBox(hInst, MAKEINTRESOURCE(IDD_WORK_MOD2), hWnd, Work_MOD3);
}

BOOL CALLBACK Work_MOD3(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_OK_MOD2:       // Next button
            EndDialog(hDlg, LOWORD(wParam));
            return TRUE;
        case IDC_CANCEL_MOD2:   // Cancel button
            EndDialog(hDlg, LOWORD(wParam));
            DefWindowProc(hDlg, message, wParam, lParam);
            return TRUE;
        case IDC_BACK_MOD2:     // Back button
            EndDialog(hDlg, LOWORD(wParam));
            Func_MOD1(hinst3, hDlg);
            // DialogBox(hinst3, MAKEINTRESOURCE(IDD_WORK_MOD1), hDlg, Func_MOD1);
            return TRUE;
        }
        break;
    }
    return FALSE;
}