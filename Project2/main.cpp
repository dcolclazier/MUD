#include <windows.h>
#include "c_app.h"
#include <iostream>
//int main() {
//
//
//	std::cin.get();;
//	return 0;
//}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	CApp Application;
	Application.Main(hInstance, lpCmdLine, nCmdShow);
	//main();
	return 0;
}


