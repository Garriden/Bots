#include "FightPreparation.h"
#include "Roadmap.h"

/* 
 * from right to left, down to up 
 *
 * in: x,       how many horitzontal maps do you want to run. 
 * in: y,       how many vertical maps do you want to run. 
 * in: reverse, the same run but backwards. 
 */
void LookForTrouble(int x, int y, bool reverse);

/*
 * Find al transparent entities, cell by cell, until it is a moob.
 */
void WatchCells();

/*
 * Go to the specific map, and start killing moobs.
 */
void GoKillMonsters();
void GoKillPiwis();
void GoKillGobballs();
void GoKillChamps();
void GoKillCaniaMassifRobots();
void GoKillDune();