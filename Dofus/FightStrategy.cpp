#include "FightStrategy.h"

void EnterFightMode()
{
	LogFile("I am in a fight!");
	int ruletNumber = 0;

	while (!IsTheFightFinished() && !AmIDefeated() && !AmILevelUp() && !IsErrorWindow() && !AmIDead()) {
		SimpleTurnMode();
		myselfFightMenuPosition_ = FindMyselfInTheMenuFight();

		Sleep(SECONDS);
		ruletNumber = Ruleta10();
		SetCursorPos(LIMIT_CELL_X_MIN + ruletNumber * 100, LIMIT_CELL_Y_MIN + ruletNumber * 50);
	}

	if (go_kill_monsters_ == -1) { // If fighting monsters, do nothing, I need to check it afterwards.
		if(AmIDead()) {
			Sleep(2 * SECONDS);
			ClickDeadOk();
			Sleep(2 * SECONDS);
			GhostRoadmap();
		}

		if(IsErrorWindow()) {
			Sleep(2 * SECONDS);
			ClickErrorWindowOk();
		}

		if(AmILevelUp()) {
			Sleep(2 * SECONDS);
			ClickLevelUpOk();
		}

		//if (AmIDefeated()) { // Press Escape below, like I won the fight.
			//go_kill_piwis_ = true;
		//}

		Sleep(2 * SECONDS);

		PressEscape();
	}
	turnNumber_ = 1;
	bastionRemainingTurns_ = 4;
	LogFile("I finished the fight!");
}

void SimpleTurnMode() 
{
	if (AmIEnteringInAFight()) { // Entering a fight = my turn
		if (sequential_) {
			ClickFightSequential(false);
		}
		else {
			ClickFightFocus();
		}
		PressSpace();
		Sleep(3 * SECONDS);
		if (GetAsyncKeyState(VK_ESCAPE)) {

			return;
		}
	}
}

void ClickFightFocus()
{
	//std::cout << "ClickFightFocus" << std::endl;
	Sleep(100);
	bool arakna_invoked = false;
	bool chafer_invoked = false;
	COLORREF arakna_color = GetColor(INVO_SPELL_POS_7_X, INVO_SPELL_POS_7_Y);
	COLORREF chafer_color = GetColor(INVO_SPELL_POS_8_X, INVO_SPELL_POS_8_Y);

	if (IsTheFightFinished()) {
		return;
	}

	if(turnNumber_ > 30) {
		RandomClicksMove(30);
	}

	//for(int chaval = 0; chaval < pj.size(); ++chaval) {
	//	if(pj[chaval] == "FECA") {
	if (invos_ && (myself_in_the_arena_pos_.first != -1) && ((turnNumber_ % 4) == 2)) {
		Sleep(100);
		/**************
		** ARAÑA
		*************/
		PressCtrlKey('7'); /* Araña */
		Sleep(100);

		SetCursorPos(myself_in_the_arena_pos_.first - 44, myself_in_the_arena_pos_.second - 22);
		Sleep(100);
		mouse_event(MOUSEEVENTF_LEFTDOWN, LIMIT_CELL_X_MIN, LIMIT_CELL_Y_MIN, 0, 0);
		Sleep(50);
		mouse_event(MOUSEEVENTF_LEFTUP, LIMIT_CELL_X_MIN, LIMIT_CELL_Y_MIN, 0, 0);
		SetCursorPos(0, 0);
		Sleep(50);

		if (arakna_color != GetColor(INVO_SPELL_POS_7_X, INVO_SPELL_POS_7_Y)) {
			arakna_invoked = true;
		}

		if (!arakna_invoked)
		{

			Sleep(100);
			PressCtrlKey('7'); /* Araña */
			Sleep(100);

			SetCursorPos(myself_in_the_arena_pos_.first + 44, myself_in_the_arena_pos_.second + 22);
			Sleep(100);
			mouse_event(MOUSEEVENTF_LEFTDOWN, LIMIT_CELL_X_MIN, LIMIT_CELL_Y_MIN, 0, 0);
			Sleep(50);
			mouse_event(MOUSEEVENTF_LEFTUP, LIMIT_CELL_X_MIN, LIMIT_CELL_Y_MIN, 0, 0);
			SetCursorPos(0, 0);
			Sleep(50);
			if (arakna_color != GetColor(INVO_SPELL_POS_7_X, INVO_SPELL_POS_7_Y)) {
				arakna_invoked = true;
			}
		}


		if (!arakna_invoked)
		{
			Sleep(100);
			PressCtrlKey('7'); /* Araña */
			Sleep(100);

			SetCursorPos(myself_in_the_arena_pos_.first + 44, myself_in_the_arena_pos_.second - 22);
			Sleep(100);
			mouse_event(MOUSEEVENTF_LEFTDOWN, LIMIT_CELL_X_MIN, LIMIT_CELL_Y_MIN, 0, 0);
			Sleep(50);
			mouse_event(MOUSEEVENTF_LEFTUP, LIMIT_CELL_X_MIN, LIMIT_CELL_Y_MIN, 0, 0);
			SetCursorPos(0, 0);
			Sleep(50);
			if (arakna_color != GetColor(INVO_SPELL_POS_7_X, INVO_SPELL_POS_7_Y)) {
				arakna_invoked = true;
			}
		}

		if (!arakna_invoked)
		{
			Sleep(100);
			PressCtrlKey('7'); /* Araña */
			Sleep(100);

			SetCursorPos(myself_in_the_arena_pos_.first - 44, myself_in_the_arena_pos_.second + 22);
			Sleep(100);
			mouse_event(MOUSEEVENTF_LEFTDOWN, LIMIT_CELL_X_MIN, LIMIT_CELL_Y_MIN, 0, 0);
			Sleep(50);
			mouse_event(MOUSEEVENTF_LEFTUP, LIMIT_CELL_X_MIN, LIMIT_CELL_Y_MIN, 0, 0);
			SetCursorPos(0, 0);
			Sleep(50);
			if (arakna_color != GetColor(INVO_SPELL_POS_7_X, INVO_SPELL_POS_7_Y)) {
				arakna_invoked = true;
			}
		}

		/**************
		** Chaferfu
		*************/
		PressCtrlKey('8');
		Sleep(100);

		SetCursorPos(myself_in_the_arena_pos_.first - 44, myself_in_the_arena_pos_.second - 66);
		Sleep(100);
		mouse_event(MOUSEEVENTF_LEFTDOWN, LIMIT_CELL_X_MIN, LIMIT_CELL_Y_MIN, 0, 0);
		Sleep(50);
		mouse_event(MOUSEEVENTF_LEFTUP, LIMIT_CELL_X_MIN, LIMIT_CELL_Y_MIN, 0, 0);
		SetCursorPos(0, 0);
		Sleep(50);
		if (chafer_color != GetColor(INVO_SPELL_POS_8_X, INVO_SPELL_POS_8_Y)) {
			chafer_invoked = true;
		}


		if (!chafer_invoked) {
			Sleep(100);
			PressCtrlKey('8');
			Sleep(200);

			SetCursorPos(myself_in_the_arena_pos_.first + 44, myself_in_the_arena_pos_.second + 66);
			Sleep(100);
			mouse_event(MOUSEEVENTF_LEFTDOWN, LIMIT_CELL_X_MIN, LIMIT_CELL_Y_MIN, 0, 0);
			Sleep(50);
			mouse_event(MOUSEEVENTF_LEFTUP, LIMIT_CELL_X_MIN, LIMIT_CELL_Y_MIN, 0, 0);
			SetCursorPos(0, 0);
			Sleep(50);
			if (chafer_color != GetColor(INVO_SPELL_POS_8_X, INVO_SPELL_POS_8_Y)) {
				chafer_invoked = true;
			}
		}

		if (!chafer_invoked) {
			Sleep(100);
			PressCtrlKey('8');
			Sleep(200);

			SetCursorPos(myself_in_the_arena_pos_.first + 44, myself_in_the_arena_pos_.second - 66);
			Sleep(100);
			mouse_event(MOUSEEVENTF_LEFTDOWN, LIMIT_CELL_X_MIN, LIMIT_CELL_Y_MIN, 0, 0);
			Sleep(50);
			mouse_event(MOUSEEVENTF_LEFTUP, LIMIT_CELL_X_MIN, LIMIT_CELL_Y_MIN, 0, 0);
			SetCursorPos(0, 0);
			Sleep(50);
			if (chafer_color != GetColor(INVO_SPELL_POS_8_X, INVO_SPELL_POS_8_Y)) {
				chafer_invoked = true;
			}
		}

		if (!chafer_invoked) {
			Sleep(100);
			PressCtrlKey('8');
			Sleep(200);

			SetCursorPos(myself_in_the_arena_pos_.first - 44, myself_in_the_arena_pos_.second + 66);
			Sleep(100);
			mouse_event(MOUSEEVENTF_LEFTDOWN, LIMIT_CELL_X_MIN, LIMIT_CELL_Y_MIN, 0, 0);
			Sleep(50);
			mouse_event(MOUSEEVENTF_LEFTUP, LIMIT_CELL_X_MIN, LIMIT_CELL_Y_MIN, 0, 0);
			SetCursorPos(0, 0);
			Sleep(50);
			if (chafer_color != GetColor(INVO_SPELL_POS_8_X, INVO_SPELL_POS_8_Y)) {
				chafer_invoked = true;
			}
		}


		arakna_invoked = false;
		chafer_invoked = false;
	}

	if ((turnNumber_ % 3) == 1) {
		SetCursorPos(LIMIT_CELL_X_MIN, LIMIT_CELL_Y_MIN);
		Sleep(100);
		mouse_event(MOUSEEVENTF_LEFTDOWN, LIMIT_CELL_X_MIN, LIMIT_CELL_Y_MIN, 0, 0);
		Sleep(50);
		mouse_event(MOUSEEVENTF_LEFTUP, LIMIT_CELL_X_MIN, LIMIT_CELL_Y_MIN, 0, 0);

		Sleep(200);
		// Murallas
		PressCtrlKey('1');
		Sleep(200);

		DefendMe();

		Sleep(200);

		// Escudo
		PressCtrlKey('2');
		Sleep(150);

		DefendMe();
	}

	if (IsTheFightFinished()) {
		return;
	}

	if ((turnNumber_ % 3) == 0) {

		if (bastionRemainingTurns_ <= 0) { // Bastion
			PressCtrlKey('4');
			Sleep(250);
			bastionRemainingTurns_ = 4;
			DefendMe();

			Sleep(250);
			PressCtrlKey('9'); // PA gliph
			Sleep(250);
			DefendMe();

		}
		else {	// Barricada
			PressCtrlKey('3');
			Sleep(250);
			DefendMe();

			if (turnNumber_ > 5) {
				Sleep(250);
				PressKey('9'); // Repulsive gliph
				Sleep(250);
				DefendMe();
			}


		}

	}

	Sleep(200);

	if(IsTheFightFinished()) {
		return;
	}

	for(int ii = 0; ii < POSIBLE_FIGHT_POSITIONS; ++ii) {

		if(IsBlack(Get_translateFightMenuPositions(ii * 2), Get_translateFightMenuPositions((ii * 2) + 1) ) ) {
			break;
		}

		Sleep(200);
		AttackOneEnemy('4', ii); // Gliph

		if(turnNumber_ > 5) {
			Sleep(250);
			PressKey('9'); // Repulsive gliph
			Sleep(250);
			DefendMe();
		}

		Sleep(200);
		AttackOneEnemy('3', ii); // Lifeless

		if (IsTheFightFinished()) {
			return;
		}
		Sleep(200);
		AttackOneEnemy('2', ii);  //Natural

		if (IsTheFightFinished()) {
			return;
		}

		Sleep(150);
		AttackOneEnemy('6', ii); // Llamilla

		if (IsTheFightFinished()) {
			return;
		}

		if (IsTheFightFinished()) {
			return;
		}

		if (IsTheFightFinished()) {
			return;
		}
	}

	// Si quedan pocos enemigos
	if (myselfFightMenuPosition_ < 3) {
		ClickFightSequential(true);
	}

	Sleep(200);

	turnNumber_++;
	bastionRemainingTurns_--;

	if (!IsTheFightFinished()) {
		// Random Clicks to move
		if (!invos_) {
			RandomClicksMove(5);
		}
	}
}

void RandomClicksMove(int moves)
{
	for (int ii = 0; ii < moves; ++ii) {
		if (!IsTheFightFinished() && !AmIDead() && !AmIDefeated()) {
			int ruletNumberPosX = RuletaInput(RANDOM_X_LIMIT_MIN, RANDOM_X_LIMIT_MAX);
			int ruletNumberPosY = RuletaInput(RANDOM_Y_LIMIT_MIN, RANDOM_Y_LIMIT_MAX);
			Sleep(100);
			SetCursorPos(ruletNumberPosX, ruletNumberPosY);
			Sleep(300);
			mouse_event(MOUSEEVENTF_LEFTDOWN, ruletNumberPosX, ruletNumberPosY, 0, 0);
			Sleep(20);
			mouse_event(MOUSEEVENTF_LEFTUP, ruletNumberPosX, ruletNumberPosY, 0, 0);
		}
	}
}

void ClickFightSequential(bool little)
{
	//std::cout << "ClickFightSequential" << std::endl;
	Sleep(100);

	if (IsTheFightFinished()) {
		return;
	}

	if (!little) {
		if ((turnNumber_ % 3) == 1) {
			SetCursorPos(LIMIT_CELL_X_MIN, LIMIT_CELL_Y_MIN);
			Sleep(100);
			mouse_event(MOUSEEVENTF_LEFTDOWN, LIMIT_CELL_X_MIN, LIMIT_CELL_Y_MIN, 0, 0);
			Sleep(50);
			mouse_event(MOUSEEVENTF_LEFTUP, LIMIT_CELL_X_MIN, LIMIT_CELL_Y_MIN, 0, 0);

			Sleep(200);
			// Murallas
			PressCtrlKey('1');
			Sleep(200);

			DefendMe();

			Sleep(200);

			// Escudo
			PressCtrlKey('2');
			Sleep(150);

			DefendMe();
		}

		if (IsTheFightFinished()) {
			return;
		}

		if ((turnNumber_ % 3) == 0) {

			if (bastionRemainingTurns_ <= 0) { // Barricada
				PressCtrlKey('3');
				Sleep(250);
				bastionRemainingTurns_ = 4;
				DefendMe();
			}
			else {	// Bastion
				PressCtrlKey('4');
				Sleep(250);
				DefendMe();

				if (turnNumber_ > 5) {
					Sleep(250);
					PressKey('9'); // Repulsive gliph
					Sleep(250);
					DefendMe();
				}

				Sleep(250);
				PressCtrlKey('9'); // PA gliph
				Sleep(250);
				DefendMe();
			}

		}
	}

	Sleep(SECONDS);

	if (IsTheFightFinished()) {
		return;
	}

	Sleep(200);
	AttackTheEnemy('4'); // Gliph

	if (turnNumber_ > 5) {
		Sleep(250);
		PressKey('9'); // Repulsive gliph
		Sleep(250);
		DefendMe();
	}

	Sleep(200);
	AttackTheEnemy('3'); // Lifeless

	if (IsTheFightFinished()) {
		return;
	}

	Sleep(200);
	AttackTheEnemy('2');  //Natural

	if (IsTheFightFinished()) {
		return;
	}

	Sleep(200);
	AttackTheEnemy('6'); // Llamilla

	if (IsTheFightFinished()) {
		return;
	}

	Sleep(200);
	AttackTheEnemy('7'); // Pompete

	if (IsTheFightFinished()) {
		return;
	}

	if (IsTheFightFinished()) {
		return;
	}

	Sleep(200);

	if(!little) {
		if (!IsTheFightFinished()) {
			// Random Clicks to move
			for (int ii = 0; ii < 5; ++ii) {
				int ruletNumberPosX = RuletaInput(RANDOM_X_LIMIT_MIN, RANDOM_X_LIMIT_MAX);
				int ruletNumberPosY = RuletaInput(RANDOM_Y_LIMIT_MIN, RANDOM_Y_LIMIT_MAX);
				Sleep(300);
				SetCursorPos(ruletNumberPosX, ruletNumberPosY);
				Sleep(100);
				mouse_event(MOUSEEVENTF_LEFTDOWN, ruletNumberPosX, ruletNumberPosY, 0, 0);
				Sleep(20);
				mouse_event(MOUSEEVENTF_LEFTUP, ruletNumberPosX, ruletNumberPosY, 0, 0);
			}

		}
		turnNumber_++;
		bastionRemainingTurns_--;
	}

}

void CheckFight()
{
	if(AmIEnteringInAFight()) {
		PrepareForFighting();
		EnterFightMode();
		AfterFighting();
	}

	if(CheckZaapAstrub()) { // It means that I am dead
		restart_roadmap_ = true;
		first_time_go_to_initial_map_ = true;
	}
}

void CheckFightInvocar()
{
	if (AmIEnteringInAFight()) {
		PrepareForFightingInvocar();
		EnterFightMode();
		AfterFightingLevear();
	}

	if (CheckZaapAstrub()) { // It means that I am dead
		restart_roadmap_ = true;
		first_time_go_to_initial_map_ = true;
	}
}

void CheckFightLevear()
{
	if (AmIEnteringInAFight()) {
		PrepareForFighting();
		EnterFightMode();
		AfterFightingLevear();
	}
}
