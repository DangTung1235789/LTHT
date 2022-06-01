#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("SysMets1");
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
		WS_OVERLAPPEDWINDOW,
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
	static int  cxChar, cxCaps, cyChar;
	HDC         hdc;
	int         i, j;
	PAINTSTRUCT ps;
	TCHAR       szBuffer[10];
	TEXTMETRIC  tm;
	POINT apt[5] = { 100,100,200,100,200,200,100,200,100,100 };
	int left, top, bottom, right;
	static int cxClient, cyClient;

	switch (message)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

	case WM_CREATE:
		hdc = GetDC(hwnd);

		GetTextMetrics(hdc, &tm);
		cxChar = tm.tmAveCharWidth;
		cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
		cyChar = tm.tmHeight + tm.tmExternalLeading;

		ReleaseDC(hwnd, hdc);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		left = 0;
		top = 0;
		right = cxClient / 6;
		bottom = cyClient / 6;

		for (i = 1; i <= 6; i++) {
			for (j = 0; j < 6; j++) {
				Rectangle(hdc, left, top, right, bottom);
				left = left;
				top = top + (cyClient / 6);
				right = right;
				bottom = bottom + (cyClient / 6);
			}
			top = 0;
			left = (cxClient / 6) * i;
			right = (cxClient / 6) * (i + 1);
			bottom = (cyClient / 6);
		}

		

		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

