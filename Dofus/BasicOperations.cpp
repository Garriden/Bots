#define DEFINE_VARIABLES
#include "BasicOperations.h"

int Ruleta10()
{
	int ret = 0;
	if (RANDOM_RULETA_) {
		std::mt19937 rng(static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()));
		ret = (rng()) % 10;
	}
	return ret;
}

int RuletaInput(int x, int y)
{
	int ret = 0;
	if (RANDOM_RULETA_) {
		std::mt19937 rng(static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()));
		ret = (rng()) % (abs(y - x));
	}
	return (x + ret);
}

void GetScreenSize()
{
	HWND activeWindow = GetActiveWindow();
	HMONITOR activeMonitor = MonitorFromWindow(activeWindow, MONITOR_DEFAULTTONEAREST);
	MONITORINFO monitorInfo{};
	monitorInfo.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(activeMonitor, &monitorInfo);

	int displayWidth = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
	int displayHeight = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;

	std::cout << displayWidth << " / " << displayHeight << std::endl;
}

COLORREF GetColor(int x, int y)
{
	HDC hdc_ = GetDC(NULL);
	COLORREF color = GetPixel(hdc_, x, y);
	ReleaseDC(NULL, hdc_);

	return color;
}

COLORREF GetColorCout(int x, int y)
{
	HDC hdc_ = GetDC(NULL);
	COLORREF color = GetPixel(hdc_, x, y);
	ReleaseDC(NULL, hdc_);
	LogFile(std::to_string(int(GetRValue(color))) + " " + 
			std::to_string(int(GetGValue(color))) + " " + 
			std::to_string(int(GetBValue(color))) );

	return color;
}
