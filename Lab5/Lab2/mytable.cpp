#include "framework.h"
#include "Mytable.h"
#include <fstream>
using namespace std;

void MyTable::Add(HWND hWndDlg, string str) {
	ofstream f;
	string path = "C://Users/Maxim/Desktop/Projects/OOP_labs/Lab5/table.txt";
	f.open(path, ofstream::app);
	if (!f.is_open()) {
		throw new exception("Can't open a file");
	}
	else {
		f << str << "\n";
	}
	f.close();

	SendDlgItemMessage(hWndDlg, IDC_LIST, LB_ADDSTRING, 0, (LPARAM)str.c_str());
}
