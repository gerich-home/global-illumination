// GlobalLighting.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "GlobalLighting.h"

#include "SimpleTracing.h"
#include "Rasterizer.h"

#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "Square.h"
#include "Scene.h"

#include "SphereLight.h"
#include "TriangleLight.h"
#include "SquareLight.h"
#include "CompositeLightSource.h"

#include <time.h>

using namespace Engine;

IShape* scene;
ILightSource* lights;

#define W 640
#define H 480
#define WORKERS 8

Luminance L[W * H];

DWORD ThreadProc(LPVOID lpdwThreadParam);
CRITICAL_SECTION CriticalSection;
bool destroyed = false;
bool inited = false;
volatile int currentLine;
bool busy[H];
int frame[H];

#include "MemoryManager.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
volatile HWND hWnd;
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: разместите код здесь.
	MSG msg;
	HACCEL hAccelTable;

	// Инициализация глобальных строк
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GLOBALLIGHTING, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GLOBALLIGHTING));

	// Цикл основного сообщения:
	while (GetMessage(&msg, NULL, 0, 0))
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
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
//  КОММЕНТАРИИ:
//
//    Эта функция и ее использование необходимы только в случае, если нужно, чтобы данный код
//    был совместим с системами Win32, не имеющими функции RegisterClassEx'
//    которая была добавлена в Windows 95. Вызов этой функции важен для того,
//    чтобы приложение получило "качественные" мелкие значки и установило связь
//    с ними.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GLOBALLIGHTING));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_GLOBALLIGHTING);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}


	GO_FLOAT kd1[] = {0, 0, 0};
	GO_FLOAT ks1[] = {1, 1, 1};
	int      n1[]  = {15, 15, 15};
	const Material* m1 = new Material(kd1, ks1, n1);

	GO_FLOAT kd2[] = {0, 0, 0};
	GO_FLOAT ks2[] = {0, 0, 0};
	int      n2[]  = {0, 0, 0};
	const Material* m2 = new Material(kd2, ks2, n2);
	
	GO_FLOAT kd3[] = {0.8, 0.8, 0.8};
	GO_FLOAT ks3[] = {0, 0, 0};
	int      n3[]  = {0, 0, 0};
	const Material* m3 = new Material(kd3, ks3, n3);
	
	GO_FLOAT Le1[] = {10, 10, 10};

	const IShape* shapes[] = {

		//floor
		new Shapes::Square(Vector(-0.5, -0.5, 1), Vector(-0.5, -0.5, 2), Vector(0.5,  -0.5, 1), m3),
		//ceiling
		//new Shapes::Square(Vector(-0.5,  0.5, 1), Vector(0.5,   0.5, 1), Vector(-0.5,  0.5, 2), m3),
		//back wall
		new Shapes::Square(Vector(-0.5, -0.5, 2), Vector(-0.5, 0.5, 2), Vector(0.5,  -0.5, 2), m3),
		//left wall
		new Shapes::Square(Vector(-0.5,  0.5, 1), Vector(-0.5, 0.5, 2), Vector(-0.5, -0.5, 1), m3),
		//right wall
		new Shapes::Square(Vector(0.5,  0.5, 1), Vector(0.5, -0.5, 1), Vector(0.5, 0.5, 2), m3),
		
		new Shapes::Sphere(Vector(0, -0.4, 1.5), 0.1, m1),
		new Shapes::Sphere(Vector(0.25, 0.2, 1.7), 0.1, m1),
	};
	
	const ILightSource* lightSources[] = {
		//new Lights::Square(Vector(-0.15, 0.5, 1.35), Vector(0.15,  0.5, 1.35), Vector(-0.15, 0.5, 1.65), Luminance(Le1)),
		new Lights::Sphere(Vector(0, 0.5, 1.5), 0.1, Luminance(Le1)),
	};
	
	scene = new Shapes::Scene(sizeof(shapes) / sizeof(IShape*), shapes);
	lights = new Lights::CompositeLightSource(sizeof(lightSources) / sizeof(ILightSource*), lightSources);
	
	srand(time(0));

	InitializeCriticalSection(&CriticalSection);

	for(int i = 0; i< WORKERS; i++)
	{
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&ThreadProc, 0, 0, 0);
	}
	
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	inited = true;
	return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND	- обработка меню приложения
//  WM_PAINT	-Закрасить главное окно
//  WM_DESTROY	 - ввести сообщение о выходе и вернуться.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	RECT r;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		if(GetUpdateRect(hWnd, &r, false))
		{
			hdc = BeginPaint(hWnd, &ps);

			if(inited)
			{
				for(int j = r.top; j <= r.bottom && j < H; j++)
				{
					for(int i = r.left; i <= r.right && i < W; i++)
					{
						Luminance l = L[i * H + j] / frame[j];
						SetPixel(hdc, i, j, RGB(l.r() > 1 ? 255 : l.r() * 255,
												l.g() > 1 ? 255 : l.g() * 255,
												l.b() > 1 ? 255 : l.b() * 255
												));
					}

					SetPixel(hdc, 10, j, RGB((frame[j] % 2) * 255, 0, ((frame[j] + 1) % 2) * 255));
				}
			}
			else
			{
				r.left = 0;
				r.top = 0;
				r.bottom = H - 1;
				r.right = W - 1;
				FillRect(hdc, &r, (HBRUSH) (GetStockObject(BLACK_BRUSH)));
			}
			EndPaint(hWnd, &ps);
		}

		break;
	case WM_DESTROY:
		PrintMemoryTable();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
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



DWORD ThreadProc(LPVOID lpdwThreadParam)
{

	IEngine* engine = new SimpleTracing();

	int j = -1;

	while(!destroyed)
	{
		EnterCriticalSection(&CriticalSection);
		
		if(j >= 0)
		{
			frame[j]++;
			busy[j] = false;
		}

		while(busy[currentLine])
		{	
			currentLine++;

			if(currentLine == H)
			{
				currentLine = 0;
			}
		}

		j = currentLine;
		busy[j] = true;

		LeaveCriticalSection(&CriticalSection);

		for(int i = 0; i < W && !destroyed; i++)
		{
			L[i * H + j] += ColorAtPixel(i + (float)rand() / RAND_MAX - 0.5, j + (float)rand() / RAND_MAX - 0.5, W, H, 3, scene, lights, engine);
		}

		RECT r;
		r.left   = 0;
		r.top    = j;
		r.right  = W;
		r.bottom = j + 1;
		InvalidateRect(hWnd, &r, false);
	}

	return 0;
}