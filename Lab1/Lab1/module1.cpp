#include "framework.h";
#include "resource1.h";

LPTSTR buffer;
int cchMax;

//Callback-функція вікна
static BOOL CALLBACK MyWork(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM)
{
    switch (iMessage)
    {
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            GetDlgItemText(hDlg, IDC_EDIT1, buffer, cchMax);

            EndDialog(hDlg, 1);
            break;
        }
        if (LOWORD(wParam) == IDCANCEL)
            EndDialog(hDlg, 0);
        break;
    default:
        break;
    }
    return FALSE;
}