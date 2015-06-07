#pragma once
#include <Windows.h>
#include <string>


//#define WINDOW_CLASS "MUD_SRV" //


class CApp {
	long double _looptime;
	long double _gameLoopTime;
	unsigned long long int _uptime;
	void print_line(HDC hdc, RECT& rect, std::string txt, double arg); //initial day
	void print_line(HDC hdc, RECT& rt, std::string txt); //initial day

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); //initial day
	bool Init(HINSTANCE hInstance, MSG& msg, HWND& hWnd); //initial day
public:
	int Main(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow); //initial day
	static LRESULT CALLBACK GlobalWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); //initial day
	void PaintWindow(HWND hWnd); //initial day
};