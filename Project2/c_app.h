#pragma once
#include <Windows.h>
#include <string>

#define SM_WINSOCK WM_USER+1
#define WINDOW_CLASS "MUD_SRV"


class CApp {
	long double _looptime;
	long double _gameLoopTime;
	unsigned long long int _uptime;
	void print_line(HDC hdc, RECT& rect, std::string txt, double arg);
	void print_line(HDC hdc, RECT& rt, std::string txt);

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool Init(HINSTANCE hInstance, MSG& msg, HWND& hWnd, void* test);
public:
	int Main(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow);
	static LRESULT CALLBACK GlobalWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void PaintWindow(HWND hWnd);
};