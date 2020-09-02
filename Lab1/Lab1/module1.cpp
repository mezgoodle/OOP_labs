#include "pch.h"
#include "framework.h"
#include "module1.h"

BOOL CALLBACK Work_MOD1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_CANCEL_MOD1:
            EndDialog(hDlg, LOWORD(wParam));
            return TRUE;
        case IDC_NEXT_MOD1:
            EndDialog(hDlg, LOWORD(wParam));
            return TRUE;
        }
        break;
    }
    return FALSE;
}