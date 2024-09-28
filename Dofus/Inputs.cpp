#include "Inputs.h"

void PressKey(int keyParam)
{
	SHORT key;
	UINT mappedkey;
	INPUT input = { 0 };
	key = VkKeyScan(keyParam);
	mappedkey = MapVirtualKey(LOBYTE(key), 0);
	input.type = INPUT_KEYBOARD;
	input.ki.dwFlags = KEYEVENTF_SCANCODE;
	input.ki.wScan = mappedkey;
	SendInput(1, &input, sizeof(input));
	Sleep(10);
	input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(input));
}

void PressCtrlKey(int keyParam)
{
	SHORT key;
	UINT mappedkey;
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	// Press the "Ctrl" key
	ip.ki.wVk = VK_CONTROL;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));
	Sleep(100);

	// Press the key
	key = VkKeyScan(keyParam);
	mappedkey = MapVirtualKey(LOBYTE(key), 0);
	ip.ki.dwFlags = KEYEVENTF_SCANCODE;
	ip.ki.wScan = mappedkey;
	SendInput(1, &ip, sizeof(INPUT));
	Sleep(30);

	// Release the key
	ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
	Sleep(100);

	// Release the "Ctrl" key
	ip.ki.wVk = VK_CONTROL;
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(SECONDS); // pause for 1 second
}

void KeepKeyPressed(int keyParam)
{
	SHORT key;
	UINT mappedkey;
	INPUT input = { 0 };
	key = VkKeyScan(keyParam);
	mappedkey = MapVirtualKey(LOBYTE(key), 0);
	input.type = INPUT_KEYBOARD;
	input.ki.dwFlags = KEYEVENTF_SCANCODE;
	input.ki.wScan = mappedkey;
	SendInput(1, &input, sizeof(input));
	Sleep(10);
}

void ReleaseKeyPressed(int keyParam)
{
	SHORT key;
	UINT mappedkey;
	INPUT input = { 0 };
	key = VkKeyScan(keyParam);
	mappedkey = MapVirtualKey(LOBYTE(key), 0);
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = mappedkey;
	Sleep(10);
	input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(input));
}

void PressSpace()
{
	INPUT space = { 0 };
	space.type = INPUT_KEYBOARD;
	space.ki.wVk = VK_SPACE;
	SendInput(1, &space, sizeof(INPUT)); // Send KeyDown
	space.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &space, sizeof(INPUT)); // Send KeyUp
}

void PressEscape()
{
	INPUT space = { 0 };
	space.type = INPUT_KEYBOARD;
	space.ki.wVk = VK_ESCAPE;
	SendInput(1, &space, sizeof(INPUT)); // Send KeyDown
	space.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &space, sizeof(INPUT)); // Send KeyUp
}

void PressEnter()
{
	INPUT space = { 0 };
	space.type = INPUT_KEYBOARD;
	space.ki.wVk = VK_RETURN;
	SendInput(1, &space, sizeof(INPUT)); // Send KeyDown
	space.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &space, sizeof(INPUT)); // Send KeyUp
}

void KeyboardWrite(std::string s)
{
	for (char& c : s) {
		PressKey(c);
		Sleep(500);
	}
}

void ClickOnExe()
{
	
	int x = PRIVATE_MODE_POS_X_1 - 100;
	int y = PRIVATE_MODE_POS_Y_1;
	int ii = 0;
	COLORREF color;
	bool color_found = false;

	for(ii = 0; ii < 170 && !color_found; ii += 5) {
		//SetCursorPos(x+ii, y); // Private mode
		Sleep(10);
		color = GetColor(x+ii, y);

		if(FindPrivateMode(color)) {
			color_found = true;
		}
	}

	if(color_found) {
		SetCursorPos(x+ii, y); // Private mode
		Sleep(30);
		mouse_event(MOUSEEVENTF_LEFTDOWN, x+ii, y, 0, 0);
		Sleep(50);
		mouse_event(MOUSEEVENTF_LEFTUP, x+ii, y, 0, 0);

		Sleep(500);

		x = PRIVATE_MODE_POS_X_2;
		y = PRIVATE_MODE_POS_Y_2;
	} else { // Click on the top exe bar
		x = LIMIT_CELL_X_MIN - 10;
		y = LIMIT_CELL_Y_MIN - 100;
	}

	SetCursorPos(x, y); // Private mode
	Sleep(100);
	mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
	Sleep(50);
	mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
}


std::string getTxt(std::string file_name)
{
	std::string item_name;
	std::ifstream nameFileout;
	nameFileout.open(file_name);
	std::string line;
	while(std::getline(nameFileout, line)) {
		LogFile("Write Zaap: " + line);
		return line;
	}
	return line;
}


std::string GetTxtFile(std::string file_name)
{
	std::string file_name_path = "x64/Release/Telemetry/" + file_name + ".txt";
	std::fstream file(file_name_path, std::ios::in);

	if (!file.is_open()) {
		file_name_path = "Telemetry/" + file_name + ".txt";
		std::fstream file(file_name_path, std::ios::in);
		if (!file.is_open()) {
			LogFile("Could not open the file");
		}
		else {
			return getTxt(file_name_path);
		}
	}
	else { // Debug mode
		return getTxt(file_name_path);
	}

	return "s";
}

std::vector<std::vector<std::pair<int, int> > > TranslateCSVToArray(std::string file_name)
{
	std::fstream file(file_name, std::ios::in);

	std::vector<std::vector<std::pair<int, int> > > content;
	std::vector<std::pair<int, int> > row;
	std::pair<int, int> coord;
	std::string line, word;

	while (getline(file, line)) {
		row.clear();

		std::stringstream str(line);

		while (getline(str, word, ',')) {
			coord.first = stoi(word);
			getline(str, word, ',');
			coord.second = stoi(word);
			row.push_back(coord);
		}
		content.push_back(row);
	}

	return content;
}

std::vector<std::vector<std::pair<int, int> > > GetCSVFile(std::string file_name)
{
	std::string file_name_path = "x64/Release/Telemetry/" + file_name + ".csv";
	std::fstream file(file_name_path, std::ios::in);

	if (!file.is_open()) {
		file_name_path = "Telemetry/" + file_name + ".csv";
		std::fstream file(file_name_path, std::ios::in);
		if (!file.is_open()) {
			LogFile("Could not open the file");
		}
	}
	return TranslateCSVToArray(file_name_path);
}

void ClickLevelUpOk()
{
	int ruletNumber = Ruleta10();

	SetCursorPos(I_AM_LEVEL_UP_POS_X_4, I_AM_LEVEL_UP_POS_Y_4);
	Sleep(100);
	mouse_event(MOUSEEVENTF_LEFTDOWN, I_AM_LEVEL_UP_POS_X_4, I_AM_LEVEL_UP_POS_Y_4, 0, 0);
	Sleep(ruletNumber);
	mouse_event(MOUSEEVENTF_LEFTUP, I_AM_LEVEL_UP_POS_X_4, I_AM_LEVEL_UP_POS_Y_4, 0, 0);
	Sleep(ruletNumber * 100);
}

void ClickDeadOk()
{
	LogFile("ClickDead button Ok.");
	int ruletNumber = Ruleta10();

	SetCursorPos(AM_I_DEAD_POS_X_4, AM_I_DEAD_POS_Y_4);
	Sleep(100);
	mouse_event(MOUSEEVENTF_LEFTDOWN, AM_I_DEAD_POS_X_4, AM_I_DEAD_POS_Y_4, 0, 0);
	Sleep(ruletNumber * 10);
	mouse_event(MOUSEEVENTF_LEFTUP, AM_I_DEAD_POS_X_4, AM_I_DEAD_POS_Y_4, 0, 0);
	Sleep(ruletNumber * 100);
}


void ClickErrorWindowOk()
{
	int ruletNumber = Ruleta10();

	SetCursorPos(IS_ERROR_WINDOW_POS_X_4, IS_ERROR_WINDOW_POS_Y_4);
	Sleep(100);
	mouse_event(MOUSEEVENTF_LEFTDOWN, IS_ERROR_WINDOW_POS_X_4, IS_ERROR_WINDOW_POS_Y_4, 0, 0);
	Sleep(ruletNumber);
	mouse_event(MOUSEEVENTF_LEFTUP, IS_ERROR_WINDOW_POS_X_4, IS_ERROR_WINDOW_POS_Y_4, 0, 0);
	Sleep(ruletNumber * 100);
}

void recordTelemetry()
{
	std::vector<std::pair<int, int> > Coord;
	POINT cursor;
	char buff[256];
	int pos = 0;
	int territory = 0;
	bool firstTime = true;
	bool telemetry_paused = false;

	std::ofstream myFile;
	std::string randomName = std::to_string(RuletaInput(1, 999999));
	myFile.open(randomName + ".txt");

	Sleep(2 * SECONDS);

	while(true) {

		if(firstTime) {
			firstTime = false;
			sprintf_s(buff, "const std::vector < std::vector<std::pair<int, int> > > Coordets = { \n");
			OutputDebugStringA(buff);
		}

		if(GetAsyncKeyState(VK_LSHIFT)) {
			if(!telemetry_paused) {
				LogFile("Telemetry paused...");
			} else {
				LogFile("Telemetry back to hit again");
			}
			telemetry_paused = !telemetry_paused;
			Sleep(3 * SECONDS);
		}

		if(!telemetry_paused) {
			if(GetAsyncKeyState(VK_ESCAPE)) {
				sprintf_s(buff, "};\n");
				OutputDebugStringA(buff);

				myFile.close();

				break;
			}

			if(GetAsyncKeyState(VK_LBUTTON) < 0) { // Click
				GetCursorPos(&cursor);
				Coord.push_back(std::make_pair(cursor.x, cursor.y));
				++pos;
				Sleep(500);
			} else if(GetAsyncKeyState(VK_NUMPAD1) < 0) {
				Sleep(500);
				Coord.push_back(std::make_pair(-1, -1));
			} else if(GetAsyncKeyState(VK_NUMPAD2) < 0) {
				Sleep(500);
				Coord.push_back(std::make_pair(-2, -2));
			} else if(GetAsyncKeyState(VK_NUMPAD3) < 0) {
				Sleep(500);
				Coord.push_back(std::make_pair(-3, -3));
			} else if(GetAsyncKeyState(VK_NUMPAD4) < 0) {
				Sleep(500);
				Coord.push_back(std::make_pair(-4, -4));
			} else if(GetAsyncKeyState(VK_NUMPAD5) < 0) {
				Sleep(500);
				Coord.push_back(std::make_pair(-5, -5));
			} else if(GetAsyncKeyState(VK_SPACE)) {
				LogFile("Coord: ");
				sprintf_s(buff, "{ ");
				myFile << "";
				OutputDebugStringA(buff);
				for (int ii = 0; ii < static_cast<int>(Coord.size()); ++ii) {
					sprintf_s(buff, "{%d,%d}", Coord[ii].first, Coord[ii].second);
					OutputDebugStringA(buff);
					myFile << Coord[ii].first << "," << Coord[ii].second;
					std::cout << "{" << Coord[ii].first << "," << Coord[ii].second << "}";
					if (ii < static_cast<int>(Coord.size()) - 1) {
						std::cout << ", ";
						myFile << ", ";
						sprintf_s(buff, ", ");
						OutputDebugStringA(buff);
					}
				}
				sprintf_s(buff, " },\n");
				OutputDebugStringA(buff);
				std::cout << std::endl;
				myFile << "\n";

				Coord.clear();

				++territory;

				Sleep(500);
			}
		}

	}

}

void ChangeMap(int position)
{
	int x = 0, y = 0;
	switch (position)
	{
	case UP:
		x = UP_X;
		y = UP_Y;
		break;
	case DOWN:
		x = DOWN_X;
		y = DOWN_Y;
		break;
	case LEFT:
		x = LEFT_X;
		y = LEFT_Y;
		break;
	case RIGHT:
		x = RIGHT_X;
		y = RIGHT_Y;
		break;
	default:
		break;
	}

	SetCursorPos(x, y);
	mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
	Sleep(50);
	mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
	Sleep(10 * SECONDS);
}

void ClickWhereIWant(int x, int y)
{
	int ruletNumber = Ruleta10();
	Sleep(1 * SECONDS + ruletNumber * 100);

	/****************************
	* Press it!
	****************************/
	SetCursorPos(x, y);
	mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
	Sleep(30);
	mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);

	Sleep(1 * SECONDS + ruletNumber * 100);
}

void DebugPoints()
{
	ShowMenuDebugPoints();
	while (true) {
		if (GetAsyncKeyState(VK_LCONTROL)) {
			Sleep(500);
			POINT cursorPos;
			GetCursorPos(&cursorPos);
			LogFile("Mouse X = " + std::to_string(cursorPos.x));
			LogFile("Mouse Y = " + std::to_string(cursorPos.y));
			COLORREF color = GetColorCout(cursorPos.x, cursorPos.y);
		} else if(GetAsyncKeyState(VK_LSHIFT)) {
			recordTelemetry();
		}
	}
}

bool FindPrivateMode(COLORREF color)
{
	bool ret = false;

	/* It is the desiRED  color */
	if(((int(GetRValue(color)) < PRIVATE_MODE_POS_COLOR_RED_1   + ERROR_GET_COLOUR_SMALL) &&
		(int(GetRValue(color)) > PRIVATE_MODE_POS_COLOR_RED_1   - ERROR_GET_COLOUR_SMALL) &&
		(int(GetGValue(color)) < PRIVATE_MODE_POS_COLOR_GREEN_1 + ERROR_GET_COLOUR_SMALL) &&
		(int(GetGValue(color)) > PRIVATE_MODE_POS_COLOR_GREEN_1 - ERROR_GET_COLOUR_SMALL) &&
		(int(GetBValue(color)) < PRIVATE_MODE_POS_COLOR_BLUE_1  + ERROR_GET_COLOUR_SMALL) &&
		(int(GetBValue(color)) > PRIVATE_MODE_POS_COLOR_BLUE_1  - ERROR_GET_COLOUR_SMALL))
		||
		((int(GetRValue(color))< PRIVATE_MODE_POS_COLOR_RED_2   + ERROR_GET_COLOUR_SMALL) &&
		(int(GetRValue(color)) > PRIVATE_MODE_POS_COLOR_RED_2   - ERROR_GET_COLOUR_SMALL) &&
		(int(GetGValue(color)) < PRIVATE_MODE_POS_COLOR_GREEN_2 + ERROR_GET_COLOUR_SMALL) &&
		(int(GetGValue(color)) > PRIVATE_MODE_POS_COLOR_GREEN_2 - ERROR_GET_COLOUR_SMALL) &&
		(int(GetBValue(color)) < PRIVATE_MODE_POS_COLOR_BLUE_2  + ERROR_GET_COLOUR_SMALL) &&
		(int(GetBValue(color)) > PRIVATE_MODE_POS_COLOR_BLUE_2  - ERROR_GET_COLOUR_SMALL)))
	{
		ret = true;
		LogFile("Private mode (dot) it is found!");
	}

	return ret;
}