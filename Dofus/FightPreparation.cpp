#include "FightPreparation.h"

bool IsThatPersonInTheFightMenuFriend(int pos)
{
	bool ret = false;
	COLORREF color;
	int x = 0, y = 0;
	switch (pos) {
	case 0:
		x = FIGTH_MENU_POS_X_0;
		y = FIGTH_MENU_POS_Y_0;
		break;
	case 1:
		x = FIGTH_MENU_POS_X_1;
		y = FIGTH_MENU_POS_Y_1;
		break;
	case 2:
		x = FIGTH_MENU_POS_X_2;
		y = FIGTH_MENU_POS_Y_2;
		break;
	case 3:
		x = FIGTH_MENU_POS_X_3;
		y = FIGTH_MENU_POS_Y_3;
		break;
	case 4:
		x = FIGTH_MENU_POS_X_4;
		y = FIGTH_MENU_POS_Y_4;
		break;
	case 5:
		x = FIGTH_MENU_POS_X_5;
		y = FIGTH_MENU_POS_Y_5;
		break;
	case 6:
		x = FIGTH_MENU_POS_X_6;
		y = FIGTH_MENU_POS_Y_6;
		break;
	case 7:
		x = FIGTH_MENU_POS_X_7;
		y = FIGTH_MENU_POS_Y_7;
		break;
	case 8:
		x = FIGTH_MENU_POS_X_8;
		y = FIGTH_MENU_POS_Y_8;
		break;
	case 9:
		x = FIGTH_MENU_POS_X_9;
		y = FIGTH_MENU_POS_Y_9;
		break;
	case 10:
		x = FIGTH_MENU_POS_X_10;
		y = FIGTH_MENU_POS_Y_10;
		break;
	default:
		break;
	}

	color = GetColor(x, y);

	if (!IsBlack(x, y)) {
		black_position_++;
	}

	if (((int(GetRValue(color)) > (FIGTH_MENU_ENEMY_COLOR_RED + ERROR_GET_COLOUR_SMALL)) &&
		(int(GetBValue(color)) < (FIGTH_MENU_ENEMY_COLOR_BLUE - ERROR_GET_COLOUR_SMALL))))
	{
		black_position_;
		ret = true;
	}

	return ret;
}

int FindMyselfInTheMenuFight()
{
	int ret = 0;
	for (int ii = 0; ii < 16; ++ii) {
		//cout << "pos ii: " << ii;
		if (IsThatPersonInTheFightMenuFriend(ii)) {
			//cout << " friend" << endl;
			ret = ii;
			break;
		}
		else { // It's treason then
			  //cout << " enemy" << endl;
		}
	}
	return ret;
}

std::pair<int, int> FindMyselfInTheArena()
{
	int black_name_addition = 122;
	if (current_pj_ == "ENU") {
		black_name_addition = 88;
	}

	int iteration = 0;
	bool odd = false;
	int odd_suplement = 0;
	COLORREF color_me_fight_before;

	myselfFightMenuPosition_ = FindMyselfInTheMenuFight();
	int x_myself = translateFightMenuPositions[(myselfFightMenuPosition_ * 2)];
	int y_myself = translateFightMenuPositions[(myselfFightMenuPosition_ * 2) + 1];
	color_me_fight_before = GetColor(x_myself, y_myself);

	for (int xx = LIMIT_CELL_X_MAX; xx > LIMIT_CELL_X_MIN; xx -= 44) {
		for (int yy = LIMIT_CELL_Y_MAX + odd_suplement - 44; yy > LIMIT_CELL_Y_MIN; yy -= 44) {
			++iteration;
			if ((iteration % 10) == 0) {
				yy++;
			}

			if (IsRedCellPreFight(GetColor(xx, yy))) {
				if (IsRedCellPreFight(GetColor(xx - 2, yy - 2)) && IsRedCellPreFight(GetColor(xx + 2, yy + 2))) {
					LogFile("Go there! (red cell)");

					SetCursorPos(xx, yy);
					Sleep(100);
					mouse_event(MOUSEEVENTF_LEFTDOWN, xx, yy, 0, 0);
					Sleep(50);
					mouse_event(MOUSEEVENTF_LEFTUP, xx, yy, 0, 0);
					SetCursorPos(0, 0);
					Sleep(50);

					return { xx,yy };
				}
			}

		}
		if (odd) {
			odd = false;
			odd_suplement = 0;
		}
		else {
			odd = true;
			odd_suplement = 22;
		}
		iteration = 0;
	}
	return { -1,-24 };
}

void DefendMe()
{
	myselfFightMenuPosition_ = FindMyselfInTheMenuFight();
	//LogFile("DefendMe: I am in pos: " + std::to_string(myselfFightMenuPosition_));
	int x = Get_translateFightMenuPositions(myselfFightMenuPosition_ * 2);
	int y = Get_translateFightMenuPositions((myselfFightMenuPosition_ * 2) + 1);
	SetCursorPos(x, y);
	Sleep(200);
	mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
	Sleep(20);
	mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);

	Sleep(200);
}

void AttackOneEnemy(int key, int pos)
{
	//TRADUCCIO FIGHT POSITIONS
	int x = Get_translateFightMenuPositions(pos * 2);
	int y = Get_translateFightMenuPositions((pos * 2) + 1);

	if (IsBlack(x, y) && (pos > 3)) {
		return;
	}

	if (!IsThatPersonInTheFightMenuFriend(pos)) {
		PressKey(key);
		Sleep(200);

		SetCursorPos(x, y);
		Sleep(120);
		mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
		Sleep(20);
		mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
	}
}

void AttackTheEnemy(int key)
{
	for (int ii = 0; ii < POSIBLE_FIGHT_POSITIONS; ++ii) {
		//TRADUCCIO FIGHT POSITIONS
		int x = Get_translateFightMenuPositions(ii * 2);
		int y = Get_translateFightMenuPositions((ii * 2) + 1);

		if (IsBlack(x, y)) {
			break;
		}
		if (!IsThatPersonInTheFightMenuFriend(ii)) {
			PressKey(key);
			Sleep(200);

			SetCursorPos(x, y);
			Sleep(150);
			mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
			Sleep(50);
			mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
		}
	}
}

void PutMenuBar(int changes, bool up)
{
	int x = MENU_BAR_ARROW_DOWN_POS_X;
	int y = MENU_BAR_ARROW_DOWN_POS_Y;
	if (up) {
		x = MENU_BAR_ARROW_UP_POS_X;
		y = MENU_BAR_ARROW_UP_POS_Y;
	}
	SetCursorPos(x, y);

	for (int ii = 0; ii < changes; ++ii) {
		mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
		Sleep(200);
		mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
		Sleep(600);
	}
	Sleep(1000);
}

void PrepareForFighting()
{
	/*****************************
	** Poner Barra numero 1
	*****************************/

	PutMenuBar(5, true);

	Sleep(SECONDS);

	/*****************************
	** Clickar set pelea (Cntrl + 2)
	*****************************/

	black_position_ = 0;
	FindMyselfInTheMenuFight(); // Para encontrar el negro
	//LogFile("black_position: " + std::to_string(black_position_));

	if(hunting_) {
		PressCtrlKey('4');
	} else {
		if (black_position_ > 4) { // Si hay muchos enemigos, poner glifos
			PressCtrlKey('5');
		} else {
			PressCtrlKey('2');
		}
	}

	Sleep(3 * SECONDS);

	/*****************************
	** Turn observer mode Off
	*****************************/

	//ClickWhereIWant(OBSERVER_MODE_POS_X, OBSERVER_MODE_POS_Y);

	/*****************************
	** Start fight!
	*****************************/

	PressSpace();

	Sleep(2 * SECONDS);

	/*****************************
	** Poner Barra hechizos numero 1
	*****************************/

	PutMenuBar(1, true);

	Sleep(1000);
}

void PrepareForFightingInvocar()
{
	/*****************************
	** Poner Barra numero 1
	*****************************/
	PutMenuBar(5, true);

	Sleep(1000);

	black_position_ = 0;
	FindMyselfInTheMenuFight(); // Para encontrar el negro
	//std::cout << "black_position: " << black_position_ << std::endl;

	if (hunting_) {
		PressCtrlKey('4');
	}
	else {
		if (black_position_ > 4) { // Si hay muchos enemigos, poner glifos
			PressCtrlKey('5');
		}
		else {
			PressCtrlKey('2');
		}
	}

	/*****************************
	** Find myself in the arena
	*****************************/
	myself_in_the_arena_pos_ = FindMyselfInTheArena();

	Sleep(SECONDS);

	//LogFile("myself_in_the_arena_pos_:" + std::to_string(myself_in_the_arena_pos_.first) );

	/*****************************
	** If I am still pregaring the fight menu
	*****************************/
	PressSpace();
}

void AfterFighting()
{
	Sleep(6 * SECONDS);

	/*****************************
	** Clickar set pods (Cntrl + 3)
	*****************************/
	PressCtrlKey('3');

	Sleep(3 * SECONDS);

	/*****************************
	** Poner Barra numero 4
	*****************************/
	PutMenuBar(3, false); // lenyador
	Sleep(2 * SECONDS);
}

void AfterFightingLevear()
{
	Sleep(3 * SECONDS);

	/*****************************
	** Rest
	*****************************/
	PressKey('1');
}
