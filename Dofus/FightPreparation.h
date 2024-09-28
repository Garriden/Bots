#include "BasicOperations.h"
#include "Checks.h"
#include "Inputs.h"
#include "Zaap.h"
#include "FightMenuPositions.h"

/*
 * Check if the pj in the menu fight position is friend. (red)
 * 
 * in: pos, the position of the fight menu to check. 
 */
static bool IsThatPersonInTheFightMenuFriend(int pos);

/*
 * Find a friend in the menu fight position.
 */
int FindMyselfInTheMenuFight();

/*
 * Look for a friend in the arena (pre fight).
 * Keep recorring all the cells until the cursor is in my pj,
 *  then check if the color in the menu bar has changes 
 */
std::pair<int, int> FindMyselfInTheArena();

/*
 * Click on me in the menu fight
 */
void DefendMe();

/*
 * Atack the desired enemy
 * 
 * in: key, the number or attack that you want to do.
 * in: pos, the position of the enemy in the fight menu that you want to attack.  
 */
void AttackOneEnemy(int key, int pos);

/*
 * Atack all the posible enemies
 *
 * in: key, the number or attack that you want to do.
 */
void AttackTheEnemy(int key);

/*
 * How many bars in the menu I want to push or down.
 * 
 * in: changes, how many changes do I want to make.
 * in: up, if i want to change up or down. 
 */
void PutMenuBar(int changes, bool up);

/*
 * Preparation (set) to fight (I am in pre fight).
 */
void PrepareForFighting();

/*
 * Preparation (set) to fight (I am in pre fight).
 * Search some red cell and put it there to know where to invo.
 * It will not move. 
 */
void PrepareForFightingInvocar();

/*
 * Preparation (set) after the fight.
 */
void AfterFighting();

/*
 * After the fight (rest) (same set).
 */
void AfterFightingLevear();
