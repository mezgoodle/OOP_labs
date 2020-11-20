// Lab2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Lab2.h"
#include "resource.h"
#include "toolbar.h"
#include "myeditor.h"
#include "MyTable.h"
#include <fstream>
using namespace std;


#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окн

MyEditor* editorShape = MyEditor::getInstance();// Create editor shape object
Toolbar tool;                                   // Create toolbar object
HWND dlg = NULL;
MyTable* table = new MyTable;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK       DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB2));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB2 );
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    std::string str = "";
    switch (message)
    {
    case WM_LBUTTONDOWN: //натиснуто ліву кнопку миші у клієнтській частині вікна
        if (editorShape) editorShape->OnLBdown(hWnd);
        break;
    case WM_LBUTTONUP: //відпущено ліву кнопку миші у клієнтській частині вікна
        if (editorShape) editorShape->OnLBup(hWnd);
        str = editorShape->GetString();
        table->Add(dlg, str);
        break;
    case WM_MOUSEMOVE: //пересунуто мишу у клієнтській частині вікна
        if (editorShape) editorShape->OnMouseMove(hWnd);
        break;
    case WM_INITMENUPOPUP:
        //editorShape.OnInitMenuPopup(hWnd, wParam);
        break;
    case WM_CREATE:
        tool.OnCreate(hWnd);         // Create toolbar
        if (editorShape) editorShape->Start(new EmptyShape);
        break;
    case WM_SIZE:
        tool.OnSize(hWnd);           // Size of toolbar
        break;
    case WM_NOTIFY:
        tool.OnNotify(hWnd, lParam); // Notify pressed button
        break;
    case WM_PAINT: //потрібно оновлення зображення клієнтської частині вікна
        if (editorShape) editorShape->OnPaint(hWnd);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDD_TABLEMENU:
                dlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_TABLE), 0, DlgProc);
                ShowWindow(dlg, SW_SHOW);
                SetWindowTextA(dlg, "Таблиця");
                break;
            case IDM_POINT:
                tool.OnPointPressed(hWnd);
                if (editorShape) editorShape->Start(new PointShape);
                break;
            case IDM_LINE:
                tool.OnLinePressed(hWnd);
                if (editorShape) editorShape->Start(new LineShape);
                break;
            case IDM_RECT:
                tool.OnRectPressed(hWnd);
                if (editorShape) editorShape->Start(new RectShape);
                break;
            case IDM_ELLIPSE:
                tool.OnEllipsePressed(hWnd);
                if (editorShape) editorShape->Start(new EllipseShape);
                break;
            case IDM_CUBE:
                tool.OnCubePressed(hWnd);
                if (editorShape) editorShape->Start(new CubeShape);
                break;
            case IDM_POINT_LINE:
                tool.OnPointLinePressed(hWnd);
                if (editorShape) editorShape->Start(new PointLineShape);
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProcW(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    string path = "C://Users/Maxim/Desktop/Projects/OOP_labs/Lab5/table.txt";
    ifstream file;
    switch (uMsg)
    {
    case WM_INITDIALOG:
        file.open(path);
        if (!file.is_open()) {
            throw new exception("can't open file");
        }
        else {
            string str;
            while (!file.eof()) {
                str = "";
                getline(file, str);
                if (str != "") SendDlgItemMessage(hWnd, IDC_LIST, LB_ADDSTRING, 0, (LPARAM)str.c_str());
            }
        }
        file.close();
        return (INT_PTR)TRUE;
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDCANCEL || LOWORD(wParam) == IDOK)
        {
            DestroyWindow(hWnd);
            return TRUE;
        }
    }
    return (INT_PTR)FALSE;
}
