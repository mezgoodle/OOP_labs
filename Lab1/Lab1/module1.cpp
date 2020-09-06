#include "framework.h"
#include "module1.h"

HINSTANCE hinst;

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
                EndDialog(hDlg, LOWORD(wParam));
                DefWindowProc(hDlg, message, wParam, lParam);
                return TRUE;
            case IDC_NEXT_MOD1:
                EndDialog(hDlg, LOWORD(wParam));
                DialogBox(hinst, MAKEINTRESOURCE(IDD_WORK_MOD2), hDlg, Work_MOD2);
                return TRUE;
        }
        break;
    }
    return FALSE;
}

// Second callback
BOOL CALLBACK Work_MOD2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
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
            DialogBox(hinst, MAKEINTRESOURCE(IDD_WORK_MOD1), hDlg, Work_MOD1);
            return TRUE;
        }
        break;
    }
    return FALSE;
}