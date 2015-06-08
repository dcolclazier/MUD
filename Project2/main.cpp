#include <windows.h>
#include "c_app.h"
#include <iostream>
//No touchy.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	CApp Application;
	Application.Main(hInstance, lpCmdLine, nCmdShow);
	return 0;
}


