#include "BotClick.h"

static void FindEnemiesMenu()
{
	//AskPj();

	//showFindEnemiesMenuGetRoadmap();
	showHeal();
	showWhereAreYouUbicated();

	int in;

	showFindEnemiesMenu();
	std::cin >> in;

	if (in == 0) {
		return;
	}
	else if (in == 1) {
		sequential_ = true;
		hunting_ = false;
		invos_ = false;
	}
	else if (in == 2) {
		sequential_ = true;
		hunting_ = true;
		invos_ = false;
	}
	else if (in == 3) {
		sequential_ = false;
		hunting_ = false;
		invos_ = false;
	}
	else if (in == 4) {
		sequential_ = false;
		hunting_ = true;
		invos_ = false;
	}
	else if (in == 5) {
		sequential_ = false;
		hunting_ = false;
		invos_ = true;
	}
	else if (in == 6) {
		sequential_ = false;
		hunting_ = true;
		invos_ = true;
	}

	std::cout << "------------------ \n";
	std::cout << "Do you want a teleport to the map? (0/1) \n";
	std::cin >> in;
	if(in) {
		GoKillMonsters();
	}

	while(true) {
		LookForTrouble(1,1/*x_roadmap_, y_roadmap_*/, false);
		Sleep(20 * SECONDS);
		LogFile("Look for trouble in reverse...");
		LookForTrouble(1,1/*x_roadmap_, y_roadmap_*/, true);
		LogFile("Look for trouble in reverse [OK]");
	}

}

static void MineralMenu()
{
	showMineralMenu();

	int in;
	std::cin >> in;

	if(in == 0) {
		return;
	} else if(in == 1) {
		LogFile("lv.1  [TIRITH] . . . ");

		restart_roadmap_ = false;
		use_zaap_ = true;
		zaap_file_ = "ZaapToZaap/amaknaCheLv20";

		if (first_time_go_to_initial_map_) {
			first_time_go_to_initial_map_ = false;
			ClickOnExe();
			Sleep(10 * SECONDS);
			PressCtrlKey('3'); // Pods
			Sleep(3 * SECONDS);
			CheckFight();

			if (!CheckZaapEdge()) {  // AM I lost?
				if (!CheckZaapAstrub()) {
					PressCtrlKey('0');		// Recall Potion
				}
				Sleep(3 * SECONDS);

				ClickZaap(zaap_file_);
			}
		}

		if(!restart_roadmap_) ExecuteRoadMap("Mineral/FromEdgeZaapToTirith");

		if(!restart_roadmap_) ExecuteRoadMap("Mineral/Tirith");

		if(!restart_roadmap_) ExecuteRoadMap("Mineral/FromTirithToEdgeZaap");

		LogFile("[TIRITH] [OK]");
	} 
}


static void FarmerMenu()
{
	showFarmerMenu();

	int in;
	std::cin >> in;

	if(in == 0) {
		return;
	} else if (in == 1) {
		while(true) {
			LogFile("lv.40  [WHE / BAR] . . . ");

			restart_roadmap_ = false;
			use_zaap_ = true;
			zaap_file_ = "ZaapToZaap/gobball";

			if (first_time_go_to_initial_map_) {
				first_time_go_to_initial_map_ = false;
				ClickOnExe();
				Sleep(10 * SECONDS);
				PressCtrlKey('3'); // Pods
				Sleep(3 * SECONDS);
				CheckFight();

				if (!CheckZaapGobball()) {  // AM I lost?
					if (!CheckZaapAstrub()) {
						PressCtrlKey('0');		// Recall Potion
					}
					Sleep(3 * SECONDS);

					ClickZaap(zaap_file_);
				}
			}

			if (!restart_roadmap_) ExecuteRoadMap("Farmer/gobball_lv40");

			LogFile("[WHE / BAR]  [OK]");
		}
	}
}

static void AlchemistMenu()
{
	showAlchemistMenu();

	int in;
	std::cin >> in;

	first_time_go_to_initial_map_ = true;

	if(in == 0) {
		return;
	} else if(in == 1) {
		while(true) {
			restart_roadmap_ = false;
			LogFile("lv.1 [ASTRUB]   . . . ");

			if(first_time_go_to_initial_map_) {
				first_time_go_to_initial_map_ = false;
				ClickOnExe();
				Sleep(10 * SECONDS);
				CheckFight();

				if(!CheckZaapAstrub()) {  // AM I lost?
					PressCtrlKey('0');		// Recall Potion
					Sleep(3 * SECONDS);
				}
			}

			if(!restart_roadmap_) ExecuteRoadMap("Alch/AlchemistAstrub4_-11");
			if(!restart_roadmap_) ExecuteRoadMap("Alch/AlchemistAstrubDownToBank");

			LogFile("enter into the BANK");

			SaveItInTheBank();

			Sleep(10 * SECONDS);
			if(!CheckZaapAstrub()) {  // AM I lost?
				PressCtrlKey('0');		// Recall Potion
				Sleep(3 * SECONDS);
			}

			LogFile("[ASTRUB] [OK]");
		}
	} else if(in == 2) {
		while (true) {
			restart_roadmap_ = false;
			LogFile("lv.40 [EDGE]  . . . ");
			use_zaap_ = true;
			zaap_file_ = "ZaapToZaap/amaknaCheLv20";
			
			if (first_time_go_to_initial_map_) {
				first_time_go_to_initial_map_ = false;
				ClickOnExe();
				Sleep(10 * SECONDS);
				PressCtrlKey('3'); // Pods
				Sleep(3 * SECONDS);
				CheckFight();

				if (!CheckZaapEdge()) {  // AM I lost?
					if (!CheckZaapAstrub()) {
						PressCtrlKey('0');		// Recall Potion
					}
					Sleep(3 * SECONDS);

					ClickZaap(zaap_file_);
				}

				restart_roadmap_ = false;
				first_time_go_to_initial_map_ = false;
			}

			if(!restart_roadmap_) ExecuteRoadMap("Alch/AlchemistEdgelv40");

			if(!restart_roadmap_) {
				talking_with_npj_disable_check_ = true;
				LogFile("enter into the TALLER");
				ExecuteRoadMap("Alch/AlchemistEdgelv40Taller1");
				KeyboardWrite("memory");
				ExecuteRoadMap("Alch/AlchemistEdgelv40Taller2");
				talking_with_npj_disable_check_ = false;
			}

			if(!restart_roadmap_) ExecuteRoadMap("Alch/AlchemistEdgelv40AfterTaller");

			if(!restart_roadmap_) {
				Sleep(10 * SECONDS);
				if(!CheckZaapEdge()) {  // AM I lost?
					PressCtrlKey('0');		// Recall Potion
					Sleep(3 * SECONDS);
					ClickZaap(zaap_file_);
				}
			}

			LogFile("[EDGE] [OK]");
		}
	} else if(in == 3) {
		while (true) {
			restart_roadmap_ = false;
			LogFile("lv.80 [BREEDER]  . . . ");
			use_zaap_ = true;
			zaap_file_ = "ZaapToZaap/koalak";

			if(first_time_go_to_initial_map_) {
				first_time_go_to_initial_map_ = false;
				ClickOnExe();
				Sleep(10 * SECONDS);
				PressCtrlKey('3'); // Pods
				Sleep(3 * SECONDS);
				CheckFight();

				if (!CheckZaapKoalak()) {  // AM I lost?
					if (!CheckZaapAstrub()) {
						PressCtrlKey('0');		// Recall Potion
					}
					Sleep(3 * SECONDS);

					ClickZaap(zaap_file_);
				}

				restart_roadmap_ = false;
				first_time_go_to_initial_map_ = false;
			}

			if (!restart_roadmap_) ExecuteRoadMap("Alch/AlchemistBreederlv80");

			if (!restart_roadmap_) {
				Sleep(10 * SECONDS);
				if (!CheckZaapKoalak()) {  // AM I lost?
					PressCtrlKey('0');		// Recall Potion
					Sleep(3 * SECONDS);
					ClickZaap(zaap_file_);
				}
			}

			LogFile("[BREEDER] [OK]");
		}

	} else if(in == 5) {
		while (true) {
			restart_roadmap_ = false;
			LogFile("lv.140 [MOON]  . . . ");
			use_zaap_ = true;
			zaap_file_ = "ZaapToZaap/moon";

			if(first_time_go_to_initial_map_) {
				first_time_go_to_initial_map_ = false;
				ClickOnExe();
				Sleep(10 * SECONDS);
				PressCtrlKey('3'); // Pods
				Sleep(3 * SECONDS);
				CheckFight();

				if (!CheckZaapMoon()) {  // AM I lost?
					if (!CheckZaapAstrub()) {
						PressCtrlKey('0');		// Recall Potion
					}
					Sleep(3 * SECONDS);

					ClickZaap(zaap_file_);
				}

				restart_roadmap_ = false;
				first_time_go_to_initial_map_ = false;
			}

			if (!restart_roadmap_) ExecuteRoadMap("Alch/AlchemistMoonlv140");

			if (!restart_roadmap_) {
				Sleep(10 * SECONDS);
				if (!CheckZaapMoon()) {  // AM I lost?
					PressCtrlKey('0');		// Recall Potion
					Sleep(3 * SECONDS);
					ClickZaap(zaap_file_);
				}
			}

			LogFile("[MOON] [OK]");
		}


	} else if(in == 99) {
		restart_roadmap_ = false;
		LogFile("[Telemetry] . . . ");
		ExecuteRoadMap("Telemetry");
		LogFile("Telemetry [OK]");
	}
}

static void FishermanMenu()
{
	showFishermanMenu();

	int in;
	std::cin >> in;

	first_time_go_to_initial_map_ = true;

	if(in == 0) {
		return;
	} else if(in == 2) {
		while (true) {
			restart_roadmap_ = false;
			LogFile("lv.40 [SUFOKIAN SHORELINE] . . . ");
			use_zaap_ = true;
			zaap_file_ = "ZaapToZaap/shoreline";

			if(first_time_go_to_initial_map_) {
				first_time_go_to_initial_map_ = false;
				ClickOnExe();
				Sleep(10 * SECONDS);
				PressCtrlKey('3'); // Pods
				Sleep(3 * SECONDS);
				CheckFight();

				if(!CheckZaapSufokianShoreline()) {  // AM I lost?
					if(!CheckZaapAstrub()) {
						PressCtrlKey('0');		// Recall Potion
					}
					Sleep(3 * SECONDS);

					ClickZaap(zaap_file_);
				}

				restart_roadmap_ = false;
				first_time_go_to_initial_map_ = false;
			}

			if(!restart_roadmap_) ExecuteRoadMap("Fisher/SufokianShorelinelv40_1");

			if(!restart_roadmap_) ExecuteRoadMap("Fisher/SufokianShorelinelv40_2");

			if(!restart_roadmap_) ExecuteRoadMap("Fisher/SufokianShorelinelv40_3");

			if(!restart_roadmap_) ExecuteRoadMap("Fisher/SufokianShorelinelv40_4");

			if(!restart_roadmap_) {
				Sleep(10 * SECONDS);
				if (!CheckZaapSufokianShoreline()) {  // AM I lost?
					PressCtrlKey('0');		// Recall Potion
					Sleep(3 * SECONDS);
					ClickZaap(zaap_file_);
				}
			}

			LogFile("[SUFOKIAN SHORELINE] [OK]");
		}

	}
}



static void WoodMenu()
{
	showWoodMenu();

    int in, x, y;
	std::cin >> in;
	
	if(in == 0) {
		return;
	} else if(in == 1) {
		while(true) {
			restart_roadmap_ = false;
			LogFile("lv.1  [ASTRUB] . . . ");
			//back_to_starting_roadmap_ = "Wood/fromAstrubZaapToWoodLv1";
			use_zaap_ = false;

			if(first_time_go_to_initial_map_) {
				first_time_go_to_initial_map_ = false;
				ClickOnExe();
				Sleep(10 * SECONDS);
				PressCtrlKey('3'); // Pods
				Sleep(3 * SECONDS);
				CheckFight();
				if(!CheckZaapAstrub()) {
					PressCtrlKey('0');		// Recall Potion
				}
				Sleep(2 * SECONDS);
				restart_roadmap_ = false;
				std::cout << "fromAstrubZaapToWoodLv1" << std::endl;
				if(!restart_roadmap_) ExecuteRoadMap("Wood/fromAstrubZaapToWoodLv1");
			}

			std::cout << "astrubAshLv1" << std::endl;
			if(!restart_roadmap_) ExecuteRoadMap("Wood/astrubAshLv1");

			LogFile("[ASTUB] [OK]");
		}
		first_time_go_to_initial_map_ = true;
	} else if(in == 2) {
		while(true) {
			restart_roadmap_ = false;
			LogFile("lv.20 [AMAKNA]  . . . " );
			use_zaap_ = true;
			zaap_file_ = "ZaapToZaap/amaknaCheLv20";
			
			if(first_time_go_to_initial_map_) {
				LogFile("first_time_go_to_initial_map_");
				first_time_go_to_initial_map_ = false;
				ClickOnExe();
				Sleep(10 * SECONDS);
				
				PressCtrlKey('3'); // Pods
				Sleep(3 * SECONDS);
				CheckFight();

				if(!CheckZaapEdge()) {  // AM I lost?
					if(!CheckZaapAstrub()) {
						PressCtrlKey('0');		// Recall Potion
					}
					Sleep(3 * SECONDS);

					ClickZaap(zaap_file_);
				}
				restart_roadmap_ = false;
				first_time_go_to_initial_map_ = false;
			}
			
			if(!restart_roadmap_) { 
				ExecuteRoadMap("Wood/fromEdgeZaapToWoodLv20");
			}
			if(!restart_roadmap_) {
				ExecuteRoadMap("Wood/amaknaCheLv20");
			}
			
			
			if(!restart_roadmap_) {
				LogFile("enter into the TALLER");
				talking_with_npj_disable_check_ = true;
				//ExecuteRoadMap("Wood/amaknaWoodTaller");
				ExecuteRoadMap("Wood/amaknaWoodTaller1");
				KeyboardWrite("ply");
				ExecuteRoadMap("Wood/amaknaWoodTaller3");
				talking_with_npj_disable_check_ = false;
			}
			
			if(!restart_roadmap_) {
				ExecuteRoadMap("Wood/amaknaCheLv20FromTallerToFinish");
			}
			if(!restart_roadmap_) {
				ExecuteRoadMap("Wood/formAmaknaCheLv20FinishToStart");
			}

			Sleep(10 * SECONDS);
			if(!CheckZaapEdge()) {  // AM I lost?
				PressCtrlKey('0');		// Recall Potion
				Sleep(3 * SECONDS);

				ClickZaap(zaap_file_);
			}

			LogFile("[AMAKNA] [OK]");
		}
		//first_time_go_to_initial_map_ = true;
	} else if(in == 4) {
		while(true) {
			restart_roadmap_ = false;
			LogFile("lv.70 [BOMBU]  . . . ");
			use_zaap_ = true;
			zaap_file_ = "ZaapToZaap/plains";

			if(first_time_go_to_initial_map_) {
				first_time_go_to_initial_map_ = false;
				ClickOnExe();
				Sleep(10 * SECONDS);

				PressCtrlKey('3'); // Pods
				Sleep(3 * SECONDS);
				CheckFight();

				if(!CheckZaapCaniaPlains()) {  // AM I lost?
					if(!CheckZaapAstrub()) {
						PressCtrlKey('0');		// Recall Potion
					}
					Sleep(3 * SECONDS);

					ClickZaap(zaap_file_);
				}
				restart_roadmap_ = false;
				first_time_go_to_initial_map_ = false;
			}

			if(!restart_roadmap_) {
				ExecuteRoadMap("Wood/bombu1");
			}
			if(!restart_roadmap_) {
				ExecuteRoadMap("Wood/bombu2");
			}
			LogFile("bombu3");
			if(!restart_roadmap_) {
				ExecuteRoadMap("Wood/bombu3");
			}
			LogFile("bombu4");
			if(!restart_roadmap_) {
				ExecuteRoadMap("Wood/bombu4");
			}

			if(!restart_roadmap_) {
				if(CheckZaapCaniaMassif()) { // Click zaap and return to start
					x = 1182;
					y = 409;
					SetCursorPos(x, y);
					mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
					Sleep(30);
					mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
					Sleep(8 * SECONDS);

					x = 1096;
					y = 236;
					SetCursorPos(x, y);
					mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
					Sleep(30);
					mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
					Sleep(8 * SECONDS);

					KeyboardWrite("Pig Pla");
				} else {
					PressCtrlKey('0');		// Recall Potion
					Sleep(3 * SECONDS);

					ClickZaap(zaap_file_);
				}
			}

			Sleep(10 * SECONDS);
			if(!CheckZaapCaniaPlains()) {  // AM I lost?
				PressCtrlKey('0');		// Recall Potion
				Sleep(3 * SECONDS);

				ClickZaap(zaap_file_);
			}

			LogFile("[BOMBU] [OK]");
		}
	} else if(in == 8 || in == 9) {
		while(true) {
			restart_roadmap_ = false;
			LogFile("[OTOMAI] . . . ");
			use_zaap_ = true;
			zaap_file_ = "ZaapToZaap/coastOto";

			if(first_time_go_to_initial_map_) {
				first_time_go_to_initial_map_ = false;
				ClickOnExe();
				Sleep(10 * SECONDS);
				PressCtrlKey('3'); // Pods
				Sleep(3 * SECONDS);
				CheckFight();

				if(!CheckZaapOtoCoast()) {  // AM I lost?
					if(!CheckZaapAstrub()) {
						PressCtrlKey('0');		// Recall Potion
					}
					Sleep(3 * SECONDS);

					ClickZaap(zaap_file_);
				}

				restart_roadmap_ = false;
				first_time_go_to_initial_map_ = false;

				if(!restart_roadmap_) {
					ExecuteRoadMap("Wood/fromCoastToWoodOtomai");
				}

				if(in == 8) {
					if(!restart_roadmap_) {
						ExecuteRoadMap("Wood/fromWoodOtomaiToCenter");
					}
				}
			}

			if(in == 8) {
				if(!restart_roadmap_) {
					OtomaiCenterRoadMap();
				}
			} else {
				if(!restart_roadmap_) {
					YewOtomaiRoadMap();
				}
			}

			//Sleep(10 * SECONDS);
			//first_time_go_to_initial_map_ = true;

			LogFile("[OTOMAI] [OK]");
		}
	} else if (in == 10) {
		while(true) {
			restart_roadmap_ = false;
			LogFile("[KOALAK] . . . ");
			use_zaap_ = true;
			zaap_file_ = "ZaapToZaap/koalak";

			if(first_time_go_to_initial_map_) {
				first_time_go_to_initial_map_ = false;
				ClickOnExe();
				Sleep(10 * SECONDS);
				CheckFight();

				if(!CheckZaapKoalak()) {  // AM I lost?
					if(!CheckZaapAstrub()) {
						PressCtrlKey('0');		// Recall Potion
					}
					Sleep(3 * SECONDS);

					ClickZaap(zaap_file_);
				}

				restart_roadmap_ = false;
				first_time_go_to_initial_map_ = false;

				if(!restart_roadmap_) ExecuteRoadMap("Wood/fromBreedToWoodKoalak");
			}

			if(!restart_roadmap_) WoodKoalakRoadMap();

			if(!restart_roadmap_) ExecuteRoadMap("Wood/kaliptusMiddle");

			if(!CheckZaapKoalak()) {  // AM I lost?
				if(!CheckZaapAstrub()) {
					PressCtrlKey('0');		// Recall Potion
				}
				Sleep(3 * SECONDS);

				ClickZaap(zaap_file_);
			}

			if(!restart_roadmap_) ExecuteRoadMap("Wood/fromBreedToWoodKoalak");


			LogFile("[KOALAK] [OK]");
		}
	} else if (in == 99) {
		restart_roadmap_ = false;
		LogFile("[Telemetry] . . . ");
		ExecuteRoadMap("Telemetry");
		LogFile("Telemetry [OK]");
	}
}

static void  DailyMissionsMenu()
{
	ShowDailyMissions();
	talking_with_npj_disable_check_ = true;

	int in;
	std::cin >> in;

	if(in == 0) {
		return;
	} else if(in == 1) {
		return;
	} else if(in == 2) {
		//restart_roadmap_ = false;
		//back_to_starting_roadmap_ = "Missions/FightClub";
		LogFile("Fight club . . . ");

		ClickOnExe();
		Sleep(10 * SECONDS);
		CheckFight();

		if(!CheckZaapAstrub()) {
			PressCtrlKey('0');		// Recall Potion
		}
		Sleep(2 * SECONDS);

		ClickZaap("ZaapToZaap/frigost");

		ExecuteRoadMap("Missions/FightClub");

		Sleep(8 * SECONDS);
		CheckFight();
		//EnterFightMode();

		LogFile("FightClubAfter");
		ExecuteRoadMap("Missions/FightClubAfter");
		
		LogFile("Fight club [OK]");
	}  

	talking_with_npj_disable_check_ = false;
}

static void MainMenu()
{
	//AskPj();
	while(true) {
		showMainMenu();
		int in;
		std::cin >> in;
		if (in == 0) {
			system("exit");
			break;
		} else if (in == 1) {
			DebugPoints();
		} else if (in == 2) {
			FarmerMenu();
		} else if(in == 3) {
			WoodMenu();
		}  else if(in == 4) {
			MineralMenu();
		}  else if(in == 5) {
			AlchemistMenu();
		} else if(in == 6) {
			FishermanMenu();
		} else if(in == 9) {
			DailyMissionsMenu();
		} else if(in == 10) {
			FindEnemiesMenu();
		} else if (in == 70) {
			LogFile("Slow PC.");
			#undef SECONDS
			#define SECONDS (1250);
		} else if(in == 71) {
			current_pj_ = "ENU";
			invos_ = true;
			heal_ = true;
			LogFile("Playing as Enutrof.");
		} else if(in == 99) {
			Sleep(5000);

			if(!restart_roadmap_) ExecuteRoadMap("Fisher/SufokianShorelinelv40_4");

			//FindExe();
		} 
		//std::cout << "\x1B[2J\x1B[H"; // Clear
	}

}

int main()
{
	current_pj_						= "FECA";

	restart_roadmap_				= false;
	first_time_go_to_initial_map_	= true;
	lowering_pods_					= false;
	use_zaap_						= false;
	zaap_file_						= "";

	myselfFightMenuPosition_		= 0;
	black_position_					= 0;
	turnNumber_						= 1;
	bastionRemainingTurns_			= 4;

	sequential_						= false;
	hunting_						= false;
	invos_							= false;
	heal_							= false;

	go_kill_monsters_				= -1;
	myself_in_the_arena_pos_		= {-1,-1};

	talking_with_npj_disable_check_ = false;

	HWND hwnd = GetConsoleWindow();
	RECT rect = {0, 0, 315, 800};
	MoveWindow(hwnd, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top,TRUE);

	GoKillMonsters_funcs_.push_back(GoKillPiwis);
	GoKillMonsters_funcs_.push_back(GoKillGobballs);
	GoKillMonsters_funcs_.push_back(GoKillChamps);
	GoKillMonsters_funcs_.push_back(GoKillCaniaMassifRobots);
	GoKillMonsters_funcs_.push_back(GoKillDune);
	GoKillMonsters_funcs_.front();

	MainMenu();

	return 0;
}
