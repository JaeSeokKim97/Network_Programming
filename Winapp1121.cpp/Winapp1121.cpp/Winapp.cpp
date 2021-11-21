#define _CRT_SECUER_NO_WARNINGS // (LNK2019, LNK1120) ������ ������Ʈ �Ӽ� -> ��Ŀ -> �ý��� -> �����ý��� -> �ֿܼ��� â���� ����
#include <windows.h>	// (C4996)���� �߻��� ������Ʈ �Ӽ� -> C/C++ -> ��ó���� -> ��ó���� ���ǿ� _CRT_SECURE_NO_WARNINGS �߰�
#include <stdio.h>

// ������ ���ν���
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
// ���� ��Ʈ�� ��� �Լ�
void DisplayText(char* fmt, ...);

HINSTANCE hlnst; //�ν��Ͻ� �ڵ�
HWND hEdit; // ���� ��Ʈ��

int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevInstance,
	LPSTR IpCmdLine, int nCmdShow)
{
	hlnst = hlnstance;

	// ������ Ŭ���� ���
	WNDCLASS wndclass;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hlnstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = "MyWndClass";
	if (!RegisterClass(&wndclass)) return 1;

	// ������ ����
	HWND hWnd = CreateWindow("MyWndClass", "WinApp", WS_OVERLAPPEDWINDOW,
		0, 0, 600, 200, NULL, NULL, hlnstance, NULL);
	if (hWnd == NULL) return 1;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// �޽��� ����
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

//������ ���ν���
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM IParam)
{
	switch (uMsg) {
	case WM_CREATE:
		hEdit = CreateWindow("edit", NULL,
			WS_CHILD | WS_VISIBLE | WS_HSCROLL |
			WS_VSCROLL | ES_AUTOHSCROLL |
			ES_AUTOVSCROLL | ES_MULTILINE,
			0, 0, 0, 0, hWnd, (HMENU)100, hlnst, NULL);
		DisplayText("������ GUI ���� ���α׷��Դϴ�.\r\n");
		DisplayText("�ν��Ͻ� �ڵ鰪�� %#x�Դϴ�.\r\n", hlnst);
		return 0;
	case WM_SIZE:
		MoveWindow(hEdit, 0, 0, LOWORD(IParam), HIWORD(IParam), TRUE);
		return 0;
	case WM_SETFOCUS:
		SetFocus(hEdit);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, IParam);
}

//���� ��Ʈ�� ��� �Լ�
void DisplayText(char* fmt, ...)
{
	va_list arg;
	va_start(arg, fmt);

	char cbuf[256];
	vsprintf(cbuf, fmt, arg);

	int nLength = GetWindowTextLength(hEdit);
	SendMessage(hEdit, EM_SETSEL, nLength, nLength);
	SendMessage(hEdit, EM_REPLACESEL, FALSE, (LPARAM)cbuf);

	va_end(arg);
}
