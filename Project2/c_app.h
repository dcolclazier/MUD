#pragma once
#include <Windows.h>
#include "timer.h"
#include <string>

#include "defines.h"


class CApp {
	long double _worldTickTime;
	long double _gameLoopTime;
	unsigned long long int _uptime;
	void print_line(HDC hdc, RECT& rect, const std::string& txt, double arg);
	void print_line(HDC hdc, RECT& rt, const std::string& txt);

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool Init(HINSTANCE hInstance, MSG& msg, HWND& hWnd, void* test);
public:
	int Main(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow);
	static LRESULT CALLBACK GlobalWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void PaintWindow(HWND hWnd);
};