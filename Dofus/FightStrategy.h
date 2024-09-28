#include "FightMenuPositions.h"
#include "FightPreparation.h"
#include "GhostRoadmap.h"
#include "Utils.h"
#include "Checks.h"
#include "Zaap.h"

/*
 * Start fighting, desired strategy, check if it is finished.
 */
void EnterFightMode();

/*
 * If it is my turn, call strategy and fight.
 */
void SimpleTurnMode();

/*
 * Fight, focus strategy.
 */
void ClickFightFocus();

/*
 * Fight, sequential strategy.
 * 
 * in: little, just do some attacks, called from focus when there are few enemies.
 */
void ClickFightSequential(bool little);

/*
 * Look if I entered in a fight, If so, prepare to fight.
 */
void CheckFight();

/*
 * Look if I entered in a fight, If so, prepare to fight.
 * Change set and invo strategy.
 */
void CheckFightInvocar();

/*
 * Look if I entered in a fight, If so, prepare to fight.
 * While leveling (don't change set).
 */
void CheckFightLevear();

/*
 * Random clicks at the arena, expecting to move.
 *
 * in: moves, how many random moves do you want to try.
 */
void RandomClicksMove(int moves);