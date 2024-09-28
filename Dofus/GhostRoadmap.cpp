#include "GhostRoadmap.h"

void GhostRoadmap()
{
	LogFile("Execute GhostRoadmap.");
	Sleep(6 * SECONDS);
	PressCtrlKey('3'); // Pods.
	Sleep(4 * SECONDS);

	int x = 0, y = 0;
	if(zaap_file_ == "ZaapToZaap/coastOto") {
		ChangeMap(DOWN);
		ChangeMap(LEFT);
		ChangeMap(LEFT);
		ChangeMap(UP);
		ChangeMap(UP);
		ChangeMap(UP);
		ChangeMap(UP);
		ChangeMap(UP);
		ChangeMap(UP);
		ChangeMap(UP);
		x = 764;
		y = 500;
	} else if((zaap_file_ == "ZaapToZaap/amaknaCheLv20") || (zaap_file_ == "ZaapToZaap/gobball") ) {
		ChangeMap(RIGHT);
		ChangeMap(RIGHT);
		ChangeMap(RIGHT);
		ChangeMap(RIGHT);
		ChangeMap(UP);
		ChangeMap(UP);
		ChangeMap(UP);
		ChangeMap(UP);
		ChangeMap(LEFT);
		x = 588;
		y = 231;
	} else if(zaap_file_ == "ZaapToZaap/koalak") {
		ChangeMap(UP);
		ChangeMap(UP);
		ChangeMap(UP);
		ChangeMap(RIGHT);
		x = 765;
		y = 506;
	} else if(zaap_file_ == "ZaapToZaap/moon") {
		ChangeMap(RIGHT);
		ChangeMap(RIGHT);
		ChangeMap(RIGHT);
		ChangeMap(RIGHT);
		ChangeMap(UP);
		x = 1120;
		y = 455;
	} else if(zaap_file_ == "ZaapToZaap/CaniaMassif") {
		ChangeMap(LEFT);
		x = 900;
		y = 470;
	} else if(zaap_file_ == "ZaapToZaap/Dune") {
		x = 814;
		y = 348;
	} else { // Astrub
		x = 815;
		y = 425;
	}	

	Sleep(8 * SECONDS);
	SetCursorPos(x, y);
	mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
	Sleep(30);
	mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);

	Sleep(5 * SECONDS);

	restart_roadmap_ = true;
	first_time_go_to_initial_map_ = true;

	//Sleep(2 * SECONDS);
	//PressCtrlKey('3'); // Pods
	//Sleep(3 * SECONDS);
}