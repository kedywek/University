#include "primlib.h"
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#define AMOUNTOFVERTICLES 5
#define ANGLECHANGE 2
#define GROWINGSPEED 2

float rad(int angle, float number, float amount)
{
	if (angle + (number / amount * 360.0) >= 360.0) {
		angle -= 360;
	}
	angle = angle + (number / amount * 360.0);
	float rad = angle * M_PI / 180.0;
	return rad;
}
int main(int argc, char* argv[])
{
	if (gfx_init()) {
		exit(3);
	}
	int distance = 20;
	int status = 1;
	int change = GROWINGSPEED;
	int amount = AMOUNTOFVERTICLES;
	while (1) {
		for (int i = 0; i < 360; i += ANGLECHANGE) {
			if (status == 1) {
				if (distance + change >= gfx_screenHeight() / 2 - 1) {
					status = 0;
					change = -change;
				}
			}
			else {
				if (distance + change <= 20) {
					status = 1;
					change = -change;
				}
			}
			distance += change;
			gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1,
						   BLACK);
			for (int j = 0; j < amount; j++) {
				gfx_line(
					gfx_screenWidth() / 2 + cos(rad(i, j, amount)) * distance,
					gfx_screenHeight() / 2 + sin(rad(i, j, amount)) * distance,
					gfx_screenWidth() / 2 +
						cos(rad(i, j + 1, amount)) * distance,
					gfx_screenHeight() / 2 +
						sin(rad(i, j + 1, amount)) * distance,
					YELLOW);
			}
			gfx_updateScreen();
			SDL_Delay(10);
			if (gfx_pollkey() == SDLK_ESCAPE) {
				return 0;
			}
		}
	}

	gfx_getkey();
	return 0;
}
