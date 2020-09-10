#include "framework.h"
#include "module2.h"

TCHAR buf[1024] = { 0 };

static BOOL CALLBACK Work_MOD3(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int Func_MOD2(HINSTANCE hInst, HWND hWnd)
{	
	BOOL window = DialogBox(hInst, MAKEINTRESOURCE(IDD_WORK_MOD3), hWnd, Work_MOD3);
	InvalidateRect(hWnd, 0, TRUE);
	return window;
}

// First callback
BOOL CALLBACK Work_MOD3(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
		// Init list
		SendDlgItemMessage(hDlg, IDC_LIST_MOD2, LB_ADDSTRING, 0, (LPARAM)"IP-93");
		SendDlgItemMessage(hDlg, IDC_LIST_MOD2, LB_ADDSTRING, 0, (LPARAM)"IP-94");
		SendDlgItemMessage(hDlg, IDC_LIST_MOD2, LB_ADDSTRING, 0, (LPARAM)"IP-95");
		SendDlgItemMessage(hDlg, IDC_LIST_MOD2, LB_ADDSTRING, 0, (LPARAM)"IP-96");
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			INT indx = SendDlgItemMessage(hDlg, IDC_LIST_MOD2, LB_GETCURSEL, 0, 0); // Get index
			SendDlgItemMessage(hDlg, IDC_LIST_MOD2, LB_GETTEXT, indx, (long)buf);	// Get message by index
			EndDialog(hDlg, 1);
			break;
		}
		if (LOWORD(wParam) == IDCANCEL) EndDialog(hDlg, 0);
		break;
	default: break;
	}
	return FALSE;
}
