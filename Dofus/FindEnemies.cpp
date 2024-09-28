#include "FindEnemies.h"

/* from right to left, down to up */
void LookForTrouble(int x, int y, bool reverse)
{
    LogFile("LookForTrouble");
	ClickOnExe();

	if(heal_) {
		while(!HaveIHealth()) {
			LogFile("I am Healing...");
			Sleep(30 * SECONDS);
		}
	}

	for(int ii = 0; ii < x; ++ii) {
		for(int jj = 0; jj < y; ++jj) {
			PressKey('1'); /* Rest */

			WatchCells();
			if(jj != (y - 1)) {
				if((ii % 2) == 0) {
					if(reverse) {
						ChangeMap(RIGHT);
					} else {
						ChangeMap(LEFT);
					}
				} else {
					if(reverse) {
						ChangeMap(LEFT);
					} else {
						ChangeMap(RIGHT);
					}
				}
			}
		}

		if(reverse) {
			ChangeMap(DOWN);
		} else {
			ChangeMap(UP);
		}
	}
}

void WatchCells()
{
	int iteration = 0;
	int xx_before, yy_before;
	bool odd = false;
	int odd_suplement = 0;
	COLORREF color;
	for(int xx = LIMIT_CELL_X_MAX; xx > LIMIT_CELL_X_MIN; xx -= 44) {
		for(int yy = LIMIT_CELL_Y_MAX + odd_suplement; yy > LIMIT_CELL_Y_MIN; yy -= 44) {

			++iteration;
			if((iteration % 10) == 0) {
				yy++;
			}

			if(heal_) {
				while(!HaveIHealth()) {
					std::cout << "Healing...";
					Sleep(30 * SECONDS);
				}
			}
			color = GetColor(xx, yy);
			PressKey('w');
			Sleep(200);
			if(color != GetColor(xx, yy)) {
				LogFile("MOOB found!");
				SetCursorPos(xx, yy);
				mouse_event(MOUSEEVENTF_LEFTDOWN, xx, yy, 0, 0);
				Sleep(50);
				mouse_event(MOUSEEVENTF_LEFTUP, xx, yy, 0, 0);
				Sleep(8 * SECONDS);

				if(invos_) {
					CheckFightInvocar();
				} else {
					CheckFightLevear();
				}

				if (AmITalkingWithNPJ() || IsMercant() || IsErrorWindow() || IWonTheFight()) {
					LogFile("WatchCells: Press escape!");
					Sleep(2 * SECONDS);
					PressEscape();
					Sleep(2 * SECONDS);
				}

				if(AmIDead()) {
					LogFile("WatchCells: I am dead!");
					Sleep(2 * SECONDS);
					ClickDeadOk();
					Sleep(2 * SECONDS);
					GhostRoadmap();
					Sleep(5 * SECONDS);
				}

				if(AmIDefeated()) {
					LogFile("WatchCells: I am defeated!");
					Sleep(5 * SECONDS);
					PressEscape();
					Sleep(2 * SECONDS);
					GoKillMonsters();
				}

				if(AmILevelUp()) {
					Sleep(2 * SECONDS);
					ClickLevelUpOk();
				}

				Sleep(2 * SECONDS);
				if(heal_) {
					while(!HaveIHealth()) {
						LogFile("Healing...");
						Sleep(30 * SECONDS);
					}
				}

				// Move away my pj to not disturb
				xx_before = xx;
				yy_before = yy;

				SetCursorPos(LIMIT_CELL_X_MIN, LIMIT_CELL_Y_MIN);
				mouse_event(MOUSEEVENTF_LEFTDOWN, LIMIT_CELL_X_MIN, LIMIT_CELL_Y_MIN, 0, 0);
				Sleep(50);
				mouse_event(MOUSEEVENTF_LEFTUP, LIMIT_CELL_X_MIN, LIMIT_CELL_Y_MIN, 0, 0);
				xx = xx_before;
				yy = yy_before;

				yy -= 44;
			}

		}
		if(odd) {
			odd = false;
			odd_suplement = 0;
		} else {
			odd = true;
			odd_suplement = 22;
		}
		iteration = 0;
	}
}

void GoKillMonsters()
{
	ClickOnExe();

	Sleep(2 * SECONDS);
	if(!CheckZaapAstrub()) {
		PressCtrlKey('0');		// Recall Potion
	}
	Sleep(10 * SECONDS);
	
	if(go_kill_monsters_ >= 0) {
		ClickZaap(zaap_file_);
	}
	Sleep(10 * SECONDS);

	GoKillMonsters_funcs_[go_kill_monsters_]();
}

void GoKillPiwis()
{
	LogFile("GoKillPiwis");
	ChangeMap(LEFT);
	ChangeMap(LEFT);
	ChangeMap(LEFT);
	ChangeMap(UP);
	ChangeMap(UP);
}

void GoKillGobballs()
{
	LogFile("GoKillGobballs");
	ChangeMap(DOWN);
	ChangeMap(DOWN);
	ChangeMap(DOWN);
	ChangeMap(RIGHT);
}

void GoKillChamps()
{
	LogFile("GoKillChamps");
	ChangeMap(RIGHT);
	ChangeMap(RIGHT);
	ChangeMap(RIGHT);
	ChangeMap(RIGHT);
	ChangeMap(RIGHT);
	ChangeMap(DOWN);
	ChangeMap(DOWN);
	ChangeMap(DOWN);
}

void GoKillCaniaMassifRobots()
{
	LogFile("GoKillCaniaMassifRobots");
	ChangeMap(LEFT);
}

void GoKillDune()
{
	LogFile("GoKillDune");
	ChangeMap(UP);
}