#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("GDI");
	HWND         hwnd;
	MSG          msg;
	WNDCLASS     wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, TEXT("Get System Metrics No. 1"),
		WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC         hdc;
	int         i, j;
	PAINTSTRUCT ps;
	TCHAR       szBuffer[10];
	POINT apt[5] = { 100,100,200,100,200,200,100,200,100,100 };
	static int cxClient, cyClient, iColor;
	HPEN hPen1;
	HBRUSH hBrush1;

	switch (message)
	{
	case WM_CREATE:
		iColor = 0;
		return 0;
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		
		hPen1 = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		SelectObject(hdc, hPen1);

		Polygon(hdc, apt, 5);

		DeleteObject(hPen1);
		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

