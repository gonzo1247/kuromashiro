#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <WinUser.h>
#include "resource.h"
#include "File\CFile.h"
#include "Login\CLogin.h"
#include "resource.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK CheckRadioProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

const wchar_t szOptionChild[] = L"Optionen";
const UINT PM_OPTION = WM_APP + 1;

void Steuerelemente(HWND hwnd, HINSTANCE hInst);

#define ID_TEXT 4000
#define ID_ACC 4001
#define ID_PW  4002
#define ID_LOGIN 4003
#define ID_EXIT 4004
#define ID_OPTION 4005
#define ID_OPTEXIT 4006

#define ID_MUSIC	4007
#define ID_GRAPHIC	4008
#define ID_FULLSCR	4009

HWND hText;
HWND hAcc;
HWND hPw;
HWND hLogin;
HWND hExit;
HWND hOption;
HWND hChild;

HWND hMusic, hGraphic, hFullscr;

// Haupt

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
//	HWND hwnd;
	MSG msg;

	// Hauptfenster erstellen

	WNDCLASSEX wc = {};
	WNDCLASS wcc = {};

	const wchar_t szClassName[] = L"Kuroda";
	const wchar_t szOption[] = L"Optionen";

	wc.cbSize = sizeof (WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;

	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(GetModuleHandle(NULL),
        MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND + 1;
    wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU2);;
	wc.lpszClassName = szClassName;

	RegisterClassEx(&wc);

	HWND hwnd = CreateWindowEx(NULL,
		szClassName,
		L"Kuroda",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_MAXIMIZE,
        CW_USEDEFAULT, CW_USEDEFAULT, //0, 0,// CW_USEDEFAULT, CW_USEDEFAULT, //((GetSystemMetrics(SM_CXSCREEN) / 2) - 600), ((GetSystemMetrics(SM_CXSCREEN) / 2) - 600),
		CW_USEDEFAULT, CW_USEDEFAULT,// 1000, 600,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, nCmdShow);

	// PrEen
	if (hwnd == NULL)
	{
		MessageBox(hwnd, TEXT("Pruefung"), TEXT("Error"), 0);
		return 0;
	}

	// Child Window

	wcc.cbClsExtra = 0;
	wcc.cbWndExtra = 0;
	wcc.hbrBackground = (HBRUSH)COLOR_BACKGROUND + 1;
	wcc.hCursor = 0; // LoadCursor(NULL, IDC_ARROW);
	wcc.hIcon = 0; // LoadIcon(NULL, IDI_APPLICATION);
	wcc.hInstance = hInstance;
	wcc.lpfnWndProc = ChildProc;
	wcc.lpszClassName = szOption;
	wcc.lpszMenuName = NULL;
	wcc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wcc);
	
/*	HWND hwnd2 = CreateWindow(
		szOption,
		szOption,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);		 

	// PrEen
	if (hwnd2 == NULL)
	{
		MessageBox(hwnd2, TEXT("Pruefung hwnd2"), TEXT("Error"), 0);
		return 0;
	}					  */

	// Steuerelemente erstellen
	Steuerelemente(hwnd, hInstance);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

//	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
//	ShowWindow(hwnd2, nCmdShow);
//	UpdateWindow(hwnd2);

	CFile file;
	file.CCreateSetting("settings.txt");

	// beenden
	return msg.wParam;
}


// Steuerelemente

void Steuerelemente(HWND hwnd, HINSTANCE hinst)
{
	hText = CreateWindow(
		L"STATIC",
		L"UserLogin",
		WS_VISIBLE | WS_CHILD | ES_CENTER,
		600, 315,
		150, 20,
		hwnd,
		(HMENU)ID_TEXT,
		hinst,
		NULL);

	hAcc = CreateWindow(
		L"EDIT",
		L"Account",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		600, 345,
		150, 20,
		hwnd,
		(HMENU)ID_ACC,
		hinst,
		NULL);

	hPw = CreateWindow(
		L"EDIT",
		L"Passwort",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		600, 375,
		150, 20,
		hwnd,
		(HMENU)ID_PW,
		hinst,
		NULL);

	hLogin = CreateWindow(
		L"BUTTON",
		L"Login",
		BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,
		600, 405,
		70, 30,
		hwnd,
		(HMENU)ID_LOGIN,
		hinst,
		NULL);

	hExit = CreateWindow(
		L"BUTTON",
		L"Beenden",
		BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,
		675, 405,
		70, 30,
		hwnd,
		(HMENU)ID_EXIT,
		hinst,
		NULL);

	hOption = CreateWindow(
		L"BUTTON",
		L"Optionen",
		BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,
		1290, 595,
		70, 30,
		hwnd,
		(HMENU)ID_OPTION,
		hinst,
		NULL);




}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC                 hdc, hdcMem;
	static HBITMAP      hBitMap;
	static BITMAP       bitmap;
	PAINTSTRUCT         ps;
	static HWND         hButton;
	HINSTANCE			hInst = NULL;
//	static HWND			hChild;
	static RECT			rect;
    CLogin              clogin;
    char string[255];
    HMENU hMenu = GetMenu(hwnd);
    UINT uState = GetMenuState(hMenu,
        ID_SPRACHE_DEUTSCH,
        MF_BYCOMMAND);

	switch (msg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			DeleteObject(hBitMap);
			return 0;

		case WM_CREATE:
			hBitMap = (HBITMAP)LoadImage(0, TEXT("bild3.bmp"), IMAGE_BITMAP, 0, 0,
				LR_DEFAULTSIZE | LR_LOADFROMFILE | LR_CREATEDIBSECTION);

			if (hBitMap == NULL)
			{
				MessageBox(hwnd, TEXT("Bild konnte nicht geladen werden"), TEXT("Error"), 0);
				return -1;
			}

			GetObject(hBitMap, sizeof (BITMAP), &bitmap);


			return 0;

		case WM_PAINT:
			{
				hdc = BeginPaint(hwnd, &ps);
				hdcMem = CreateCompatibleDC(hdc);
				SelectObject(hdcMem, hBitMap);
				BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight,
					hdcMem, 0, 0, SRCCOPY);
				DeleteDC(hdcMem);
				EndPaint(hwnd, &ps);

				return 0;
			}

			return 0;

		case WM_COMMAND:
			{
				switch (wParam)
				{
					case ID_LOGIN:
					{
						wchar_t szText[256];
						wchar_t szPasswort[256];
						GetWindowText(hAcc, szText, 256);
						GetWindowText(hPw, szPasswort, 256);
                      //  clogin.GetData(&szText[256], &szPasswort[256]);

					//	SetWindowText(hText, szText);
						SetWindowText(hAcc, L" ");
						SetWindowText(hPw, L" ");

						// need code to send the data to server.

						return 0;
											
					}

					case ID_EXIT:
					{
						int resultat;

						resultat = MessageBox(hwnd, L"Wirklich beenden?",
							L"Programm beenden",
							MB_YESNO | MB_ICONQUESTION);

						if (resultat == IDYES)
						{
							PostQuitMessage(0);
							return (0);
						}

						return (0);
					}

					case ID_OPTION:

						hChild = CreateWindow(
							szOptionChild,
							szOptionChild,
							WS_CHILDWINDOW | WS_DLGFRAME,
							225, 100,//5, rect.bottom - 35,
							900, 550, //rect.right - 10, 30,
							hwnd,
							NULL,
                            ((LPCREATESTRUCT)lParam)->hInstance,//(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), // ((LPCREATESTRUCT)lParam)->hInstance,
							NULL);

						// PrEen
						if (hChild == NULL)
						{
							MessageBox(hChild, TEXT("Pruefung hChild"), TEXT("Error"), 0);
							return 0;
						}

						ShowWindow(hChild, SW_SHOW);

                        DialogBox(((LPCREATESTRUCT)lParam)->hInstance,// (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
                            MAKEINTRESOURCE(IDD_DIALOG1),
                            hwnd,
                            (DLGPROC)CheckRadioProc);
						 
						return 0;

                    case ID_MENU_40001:

                        break;
                    case ID_MENU_BEENDEN:
                        DestroyWindow(hwnd);
                        break;

                    case ID_SPRACHE_DEUTSCH:
                        SetMenu(hwnd, LoadMenu(hInst,
                            MAKEINTRESOURCE(IDR_MENU2)));
                        break;
                    case ID_SPRACHE_JAPANISCH:
                        SetMenu(hwnd, LoadMenu(hInst,
                            MAKEINTRESOURCE(IDR_MENU3)));

                    case ID_40012:
                        SetMenu(hwnd, LoadMenu(hInst,
                            MAKEINTRESOURCE(IDR_MENU2)));
                        break;
                    case ID_40013:
                        SetMenu(hwnd, LoadMenu(hInst,
                            MAKEINTRESOURCE(IDR_MENU3)));
					
				}
				break;
		} break;

		case WM_SIZE:
			MoveWindow(hChild, 375, 200, 450, 450, TRUE);
			MoveWindow(hOption, 1290, 595, 70, 30, TRUE);
			MoveWindow(hExit, 675, 405, 70, 30, TRUE);
			MoveWindow(hLogin, 600, 405, 70, 30, TRUE);
			MoveWindow(hPw, 600, 375, 150, 20, TRUE);
			MoveWindow(hAcc, 600, 345, 150, 20, TRUE);
			MoveWindow(hText, 600, 315, 150, 20, TRUE);
			return 0;

	}

	return DefWindowProc(hwnd, msg, wParam, lParam);

}

LRESULT CALLBACK ChildProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC                 hdc, hdcMem;
	static HBITMAP      hBitMap;
	static BITMAP       bitmap;
	PAINTSTRUCT         ps;

	HWND hOptExit;

	switch (msg)
	{
		case WM_DESTROY:
			DestroyWindow(hChild);
			DeleteObject(hBitMap);
			return 0;

		case WM_CREATE:
			hBitMap = (HBITMAP)LoadImage(0, TEXT("bild5.bmp"), IMAGE_BITMAP, 0, 0,
				LR_DEFAULTSIZE | LR_LOADFROMFILE | LR_CREATEDIBSECTION);

			if (hBitMap == NULL)
			{
				MessageBox(hwnd, TEXT("Bild konnte nicht geladen werden"), TEXT("Error"), 0);
				return -1;
			}


			GetObject(hBitMap, sizeof (BITMAP), &bitmap);

			hOptExit = CreateWindow(
				L"BUTTON",
				L"Beenden",
				BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,
				800, 480,
				70, 30,
				hwnd,
				(HMENU)ID_OPTEXIT,
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL);

			hMusic = CreateWindow(
				L"BUTTON",
				L"Music",
				BS_AUTOCHECKBOX | WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_GROUP,
				700, 400,
				70, 30,
				hwnd,
				(HMENU)ID_MUSIC,
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL);

			return 0;

		case WM_PAINT:
		{
			hdc = BeginPaint(hwnd, &ps);
			hdcMem = CreateCompatibleDC(hdc);
			SelectObject(hdcMem, hBitMap);
			BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight,
				hdcMem, 0, 0, SRCCOPY);
			DeleteDC(hdcMem);
			EndPaint(hwnd, &ps);

			return 0;
		}

		return 0;

		case WM_COMMAND:
		{
			switch (wParam)
			{
				case ID_OPTEXIT:
					DestroyWindow(hChild);
					//PostQuitMessage(0);
					return (0);
                     

			}
		}
		case WM_SIZE:
			MoveWindow(hChild, 375, 200, 450, 450, TRUE);
			MoveWindow(hMusic, 400, 200, 70, 30, TRUE);


        case WM_KEYDOWN:
            switch (wParam)
            {
            case VK_ESCAPE:
                DestroyWindow(hChild);
                return 0;
            }
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}



LRESULT CALLBACK CheckRadioProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    switch (uMsg)
    {
        case WM_COMMAND:
        {
            switch (wParam)
            {
                case IDCANCEL:
                    EndDialog(hDlg, IDCANCEL);
                    break;
                    return (0);


            }
    }
    }


    return DefWindowProc(hDlg, uMsg, wParam, lParam);

}