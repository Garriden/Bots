#include "Roadmap.h"

void ExecuteRoadMap(std::string name)
{
	std::vector<std::vector<std::pair<int, int> > > roadmap = GetCSVFile(name);
	for (int ii = 0; ii < static_cast<int>(roadmap.size()); ++ii) {
		LogFile("ii: " + std::to_string(ii));
		if(restart_roadmap_) {
			return;
		}
		ClickIdentities(roadmap[ii]);
		if (restart_roadmap_) {
			return;
		}
	}
}

void ClickIdentities(const std::vector<std::pair<int, int> > map)
{
	Sleep(100);

	int ruletNumber = 1;
	int x = 0;
	int y = 0;

	for (int ii = 0; ii < static_cast<int>(map.size()) - 1; ++ii) {
		if(!restart_roadmap_) {
			ruletNumber = Ruleta10() + 1;

			if (DELAY_BETWEEN_CHOPPS_) {
				Sleep(7 * SECONDS + ruletNumber * 100);
			}

			CheckFight();

			x = map[ii].first - ruletNumber / 4;
			y = map[ii].second - ruletNumber / 4;

			//GetColor(x_, y_);
			Sleep(100 + ruletNumber);
			SetCursorPos(x, y);
			mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
			Sleep(ruletNumber);
			mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
		}
	}

	/**************************************************************
	 * Move to the another map.
	 *
	 * Get the last coordenates from my hardcoded struct, to move to the next map.
	 * - It has, in the input sleep variable. Waiting to finish chopping before moving.
	 * - It has some other sleep, to wait to upload correctly the new map.
	 *
	 ***************************************************************/

	CheckFight();

	if(AmITalkingWithNPJ() || IsMercant() || IsErrorWindow()) {
		PressEscape();
		Sleep(1 * SECONDS);
	}

	if(IsMainMenuWindow()) {
		PressEscape();
	}
	
	if(lowering_pods_ || (!CheckPods() && !restart_roadmap_)) {
		//LogFile("Change maaaaap");
		Sleep(17 * SECONDS + ruletNumber * 100);

		CheckFight();

		if (IsMercantMode()) {
			PressEscape();
			Sleep(2 * SECONDS);
		}
		ruletNumber = Ruleta10();

		x = (map[map.size() - 1].first)  - (ruletNumber / 4);
		y = (map[map.size() - 1].second) - (ruletNumber / 2);

		/* Don't hit treasure hunt window */
		if((x < 355) && ((y > 200) && (y < 250))) {
			y = 300;
		}

		/* Don't hit office level up window */
		if((x < 355) && ((y > 570) && (y < 715))) {
			y = 750;
		}

		SetCursorPos(x, y);
		Sleep(ruletNumber * 10);

		mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
		Sleep(ruletNumber);
		mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);

		Sleep(3 * SECONDS + ruletNumber * 100);
		
	}
}

void OpenAllBags()
{
	LogFile("Open all bags");
	int cont = 0;
	int ruletNumber = Ruleta10();

	Sleep(3 * SECONDS + ruletNumber * 100);

	PressKey('i');
	Sleep(2 * SECONDS + ruletNumber * 100);

	/* Click consumables tab */
	int x = INVENTARY_CONSUMABLES_TAB_POS_X_1;
	int y = INVENTARY_CONSUMABLES_TAB_POS_Y_1;
	SetCursorPos(x, y);
	mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
	Sleep(30);
	mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
	Sleep(2 * SECONDS + ruletNumber * 100);

	x = INVENTARY_CONSUMABLES_TAB_POS_X_2;
	y = INVENTARY_CONSUMABLES_TAB_POS_Y_2;
	SetCursorPos(x, y);
	mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
	Sleep(30);
	mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
	Sleep(2 * SECONDS + ruletNumber * 100);

	/* While is not mimilk, double click */
	COLORREF color2 = GetColorCout(INVENTARY_CONSUMABLES_FIRST_CONSUMABLE_POS_X_2,
		INVENTARY_CONSUMABLES_FIRST_CONSUMABLE_POS_Y_2);

	x = INVENTARY_CONSUMABLES_FIRST_CONSUMABLE_POS_X_2;
	y = INVENTARY_CONSUMABLES_FIRST_CONSUMABLE_POS_Y_2;
	while (!IsMimilk(color2) && !IsRecallPoti(color2) && !IsBrakPoti(color2)) {
		//LogFile("Is not Mimilk or recall poti.");

		SetCursorPos(x, y);

		mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
		Sleep(30);
		mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
		Sleep(50);
		mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
		Sleep(30);
		mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
		Sleep(2 * SECONDS + ruletNumber * 100);

		if (cont++ > 10) {
			x = INVENTARY_CONSUMABLES_SECOND_CONSUMABLE_POS_X_2;
			y = INVENTARY_CONSUMABLES_SECOND_CONSUMABLE_POS_Y_2;
			color2 = GetColor(x, y);

			if (cont++ > 20) {
				x = INVENTARY_CONSUMABLES_THIRD_CONSUMABLE_POS_X_2;
				y = INVENTARY_CONSUMABLES_THIRD_CONSUMABLE_POS_Y_2;
				color2 = GetColor(x, y);

				if (cont++ > 30) {
					x = INVENTARY_CONSUMABLES_FOURTH_CONSUMABLE_POS_X_2;
					y = INVENTARY_CONSUMABLES_FOURTH_CONSUMABLE_POS_Y_2;
					color2 = GetColor(x, y);

					if (cont++ > 35) {
						cont = 0;
					}
				}
			}
		}
		else {
			color2 = GetColor(INVENTARY_CONSUMABLES_FIRST_CONSUMABLE_POS_X_2,
				INVENTARY_CONSUMABLES_FIRST_CONSUMABLE_POS_Y_2);
		}
	}

	PressKey('i');
	Sleep(2 * SECONDS + ruletNumber * 100);
}

void SaveItInTheBank()
{
	Sleep(5 * SECONDS);
	restart_roadmap_ = false;

	if(!CheckZaapAstrub()) {
		Sleep(12 * SECONDS);
		PressCtrlKey('0');		// Recall Potion
	}
	Sleep(5 * SECONDS);

	ExecuteRoadMap("ZaapToBank/fromAstrubZaapToBank");

	OpenAllBags();

	LogFile("Saving it into the bank.");
	restart_roadmap_ = false;
	ExecuteRoadMap("ZaapToBank/astrubBankTransaction");

	if(use_zaap_) {
		ClickZaap(zaap_file_);
	}

	restart_roadmap_ = true;
	first_time_go_to_initial_map_ = true;
}

bool CheckPods()
{
	if(AmIFull() and !lowering_pods_) {
		LogFile("PODS FULL!");

		lowering_pods_ = true;
		SaveItInTheBank();
		lowering_pods_ = false;
		restart_roadmap_ = true;
		return true;
	}
	return false;
}

void MineralIronTirihRoadMap()
{
	for (int ii = 0; ii < static_cast<int>(Coord_tirith_iron.size()); ++ii) {
		ClickIdentities(Coord_tirith_iron[ii]);
	}
}

void WoodKoalakRoadMap()
{
	for (int ii = 0; ii < static_cast<int>(Coord_wood_kalipto.size()); ++ii) {
		std::cout << ii << " / " << std::endl;
		ClickIdentities(Coord_wood_kalipto[ii]);
		if (restart_roadmap_) {
			return;
		}
	}
}

void YewOtomaiRoadMap()
{
	ClickIdentities(Coord_m48_19_);
	if (restart_roadmap_) {
		return;
	}
	ClickIdentities(Coord_m48_18_);
	if (restart_roadmap_) {
		return;
	}
	ClickIdentities(Coord_m48_17_);
	if (restart_roadmap_) {
		return;
	}
	ClickIdentities(Coord_m49_17_);
	if (restart_roadmap_) {
		return;
	}
	ClickIdentities(Coord_m49_16_);
	if (restart_roadmap_) {
		return;
	}
	ClickIdentities(Coord_m49_15_);
	if (restart_roadmap_) {
		return;
	}
	ClickIdentities(Coord_m49_14_);
	if (restart_roadmap_) {
		return;
	}
	ClickIdentities(Coord_m49_13_);
	if (restart_roadmap_) {
		return;
	}
	ClickIdentities(Coord_m50_13_);
	if (restart_roadmap_) {
		return;
	}
	ClickIdentities(Coord_m50_12_);
	if (restart_roadmap_) {
		return;
	}

	YewOtomaiRightRoadMap();
	if (restart_roadmap_) {
		return;
	}
	YewOtomaiLeftRoadMap();
	if (restart_roadmap_) {
		return;
	}

	OtomaiFromLeftToCenterRoadMap();
	if (restart_roadmap_) {
		return;
	}

	OtomaiCenterRoadMap();
	if (restart_roadmap_) {
		return;
	}

	OtomaiFromCenterToLeftRoadMap();
	if (restart_roadmap_) {
		return;
	}
}


void OtomaiCenterRoadMap()
{
	for (int ii = 0; ii < static_cast<int>(Coord_wood_otomai_center.size()); ++ii) {
		ClickIdentities(Coord_wood_otomai_center[ii]);
		if (restart_roadmap_) {
			return;
		}
	}
}

void YewOtomaiRightRoadMap()
{
	ClickIdentities(Coord_0_yew_otomai_right);
	ClickIdentities(Coord_1_yew_otomai_right);
	ClickIdentities(Coord_2_yew_otomai_right);
	ClickIdentities(Coord_3_yew_otomai_right);
	ClickIdentities(Coord_4_yew_otomai_right);
	ClickIdentities(Coord_5_yew_otomai_right);
	ClickIdentities(Coord_6_yew_otomai_right);
	ClickIdentities(Coord_7_yew_otomai_right);
	ClickIdentities(Coord_8_yew_otomai_right);
	ClickIdentities(Coord_9_yew_otomai_right);
}

void YewOtomaiLeftRoadMap()
{
	for (int ii = 0; ii < static_cast<int>(Coord_yew_otomai_left.size()); ++ii) {
		ClickIdentities(Coord_yew_otomai_left[ii]);
		if (restart_roadmap_) {
			return;
		}
	}
}

void OtomaiFromLeftToCenterRoadMap()
{
	for (int ii = 0; ii < static_cast<int>(Coord_otomai_right_to_center.size()); ++ii) {
		ClickIdentities(Coord_otomai_right_to_center[ii]);
		if (restart_roadmap_) {
			return;
		}
	}
}

void OtomaiFromCenterToLeftRoadMap()
{
	for (int ii = 0; ii < static_cast<int>(Coord_otomai_center_to_right.size()); ++ii) {
		ClickIdentities(Coord_otomai_center_to_right[ii]);
		if (restart_roadmap_) {
			return;
		}
	}
}

void WoodAstrubRoadMap()
{
	for (int ii = 0; ii < static_cast<int>(Wood_Astrub_lv1.size()); ++ii) {
		ClickIdentities(Wood_Astrub_lv1[ii]);
		if (restart_roadmap_) {
			return;
		}
	}
	for (int ii = 0; ii < static_cast<int>(Wood_Astrub_lv1_2.size()); ++ii) {
		ClickIdentities(Wood_Astrub_lv1_2[ii]);
		if (restart_roadmap_) {
			return;
		}
	}
}
