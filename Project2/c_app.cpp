#include "World.h"
#include "c_app.h"
#include "Server.h"
#include <chrono>
#include <sstream>
#include <iomanip>
#include <ccomplex>

class Timer  {
	typedef std::chrono::high_resolution_clock _clock;
	typedef std::chrono::duration<long double, std::ratio<1> > _second;
	std::chrono::time_point<_clock> _begin;
public:
	Timer() : _begin(_clock::now()) {}
	void reset() { _begin = _clock::now(); }
	long double elapsed() const {
		return std::chrono::duration_cast<_second>(_clock::now() - _begin).count();
	}
};


bool InitializeCommands();
LRESULT CALLBACK CApp::GlobalWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	LPCREATESTRUCT cs;
	
	if (message == WM_NCCREATE) {
		cs = reinterpret_cast<LPCREATESTRUCT>(lParam);
		SetWindowLong(hWnd, GWL_USERDATA, reinterpret_cast<LONG>(cs->lpCreateParams));
	}
	CApp *pApp = reinterpret_cast<CApp*>(GetWindowLong(hWnd, GWL_USERDATA));
	return pApp->WndProc(hWnd, message, wParam, lParam);
}
LRESULT CApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_CLOSE:
		// Quit the program
		PostQuitMessage(0);
		break;

	case WM_PAINT:
		PaintWindow(hWnd);
		break;
	case SM_WINSOCK:
		
		World::world()->server()->SocketMessageHandler(wParam, lParam);
		InvalidateRgn(hWnd, nullptr, 0);
		
		break;


	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
bool CApp::Init(HINSTANCE hInstance, MSG& msg, HWND& hWnd, void* test)
{
	WNDCLASSEX wcex;
	WSADATA wsaData;
	// Register the Windows class:

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)GlobalWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = WINDOW_CLASS;
	wcex.hIconSm = NULL;

	if (!RegisterClassEx(&wcex))
		return 0;

	// Create the Window
	hWnd = CreateWindowEx(NULL, WINDOW_CLASS,
						  MUD_WINDOWTITLE, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX,
						  GetSystemMetrics(SM_CXSCREEN) / 2 - 300 / 2,
						  GetSystemMetrics(SM_CYSCREEN) / 2 - 200 / 2,
						  300, 200, NULL, NULL, hInstance, this);

	if (!hWnd) return 0;

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	int error = WSAStartup(0x0202, &wsaData);
	if (error) {
		MessageBox(hWnd, "Could not Init Winsock2", "ERROR", MB_OK);
		return 0;
	}
	else if (wsaData.wVersion != 0x0202) {
		MessageBox(hWnd, "Could not Init Winsock2 - Wrong Version", "ERROR", MB_OK);
		WSACleanup();
		return 0;
	}
	return true;
}
int CApp::Main(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow) // lol this should be empty....
{
	HANDLE hTimer;
	LARGE_INTEGER hbTimeout;
	HWND hWnd; //message window
	MSG msg; //windows msg object
	auto world = World::world();
	
	_worldTickTime = _gameLoopTime = _uptime = 0;
	hbTimeout.QuadPart = -1000000LL;
	hTimer = CreateWaitableTimer(nullptr, TRUE, "Heartbeat");

	//INIT SECTION
	if (!world->logger()->InitLogs()) {
		return EXIT_FAILURE;
	}
	if (hTimer == nullptr) {
		world->logger()->write("system", "Heartbeat timer creation failed.");
		return EXIT_FAILURE;
	}
	if (!SetWaitableTimer(hTimer, &hbTimeout, 0, NULL, NULL, 0)) {
		world->logger()->write("system", "SetWaitableTimer failed.");
		return EXIT_FAILURE;
	}
	if (!Init(hInstance, msg, hWnd, this)) {
		world->logger()->write("system", "Window initialization failed.");
		return EXIT_FAILURE;
	}
	if (!InitializeCommands()) {
		world->logger()->write("world", "World commands initialization failed.");
		return EXIT_FAILURE;
	}
	if (!world->InitializeFiles()) {
		world->logger()->write("world", "World messages initialization failed.");
		return EXIT_FAILURE;
	}
	if (!world->channels()->InitChannels()) {
		world->logger()->write("world", "World channels initialization failed.");
		return EXIT_FAILURE;
	}
	if (world->server()->socket()->CreateSocket(hWnd, SM_WINSOCK, MUD_LSTNPORT) == 0) {
		world->logger()->write("network", "Server initialization failed.");
		return EXIT_FAILURE;
	}

	
	int tick = 0;
	world->logger()->write("system", "Init complete - game loop starting.");
	
	Timer worldLoopTimer;
	while (WM_QUIT != msg.message) {
		if (WaitForSingleObject(hTimer, INFINITE) != WAIT_OBJECT_0) { return 1;	}
		
		Timer gameLoopTimer;
		auto realTimeout = hbTimeout;
		
		//Check for world tick. - WORLD CODE HERE
		if (++tick % 599 == 0) {
			_worldTickTime = worldLoopTimer.elapsed();
			worldLoopTimer.reset();
			world->logger()->write("world", std::string("World Tick... Uptime: ") + std::to_string(++_uptime) + " minutes.");
			tick = 0;
		}

		//Process incoming player input.
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) > 0) { 
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//offset timer by game execution loop time
		//_gameLoopTime = gameLoopTimer.elapsed();
		//realTimeout.QuadPart += (_gameLoopTime * 1000000);

		//reset timer
		if (!SetWaitableTimer(hTimer, &realTimeout, 0, nullptr, nullptr, 0)) {
			return 1;
		}
	}
	
	delete world;
	//delete Server::GetServer();
	return 1;
}

//This function is responsible for what appears on the server's app screen... 
void CApp::PaintWindow(HWND hWnd) {

	std::stringstream sout;

	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);
	RECT rt;
	GetClientRect(hWnd, &rt);

	print_line(hdc, rt, MUD_TITLE);
	print_line(hdc, rt, "Connections: ", World::world()->server()->player_count());
	print_line(hdc, rt, "World tick time: ", _worldTickTime);
	print_line(hdc, rt, "Game loop time: ", _gameLoopTime);
		
	EndPaint(hWnd, &ps);
}

//no touchy - used by CApp::PaintWindow. Draws the specified string and double to the window,
//	with a newline.
void CApp::print_line(HDC hdc, RECT& rt, const std::string& txt, double arg) {
	std::stringstream sout;
	sout << std::fixed << std::setprecision(10);
	sout << txt << arg;
	DrawText(hdc, sout.str().c_str(), strlen(sout.str().c_str()), &rt, DT_CENTER);
	rt.top += 16;
}
//no touchy - used by CApp::PaintWindow. Draws the specified string to the window,
//	with a newline.
void CApp::print_line(HDC hdc, RECT& rt, const std::string& txt) {
	std::stringstream sout;
	sout << std::fixed << std::setprecision(10);
	sout << txt;
	DrawText(hdc, sout.str().c_str(), strlen(sout.str().c_str()), &rt, DT_CENTER);
	rt.top += 16;
}
