#include "Utils.h"
#include "Config.h"
#include "Logs.h"

/*
 * Prints the screen size in pixels (resolution: 1920/1080).
 */
void GetScreenSize();

/*
 * Returns a random number between 0 and 9.
 */
int Ruleta10();

/*
 * Returns a random number between x and y.
 * 
 * in: x, minimum range number.
 * in: y, maximum range number.
 */
int	RuletaInput(int x, int y);

/*
 * Returns the pixel color RGB(red, green, blue) of x and y positions (coordenates).
 *
 * in: x, pixel in cordenate x.
 * in: y, pixel in cordenate y.
 */
COLORREF GetColor(int x, int y);

/*
 * Returns the pixel color RGB(red, green, blue) of x and y positions (coordenates).
 *  And it prints the RGB color in the console for debug.
 * 
 * in: x, pixel in cordenate x.
 * in: y, pixel in cordenate y.
 */
COLORREF GetColorCout(int x, int y);