#include "primlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define AMOUNT_OF_PRONGS 5
#define AMOUNT_OF_DISKS 37
#define GROUND_HEIGHT 50
#define PRONG_HEIGHT 350
#define HALF_WIDTH_OF_PRONG 5
#define DISC_HEIGHT (PRONG_HEIGHT / (AMOUNT_OF_DISKS + 2))
#define STEP 5
#define HEIGHT_TO_GET 50

typedef struct {
	int discs[AMOUNT_OF_DISKS];
	int topelement;
	int x;
} Prong;

Prong initializeprong(int i);
Prong push(Prong operatingprong, int disc);
Prong pop(Prong operatingprong);
void movedisc(Prong prongs[], int firstprong, int secondprong);
void drawingdiscs(Prong prongs[]);
void initializebackground();
int animationdowntoup(int x, int ystart, int size, Prong prongs[]);
int animationuptodown(int x, int ystart, int size, Prong prongs[]);
void animationlefttoright(int xstart, int xfinish, int ystart, int yfinish,
						  int size, Prong prongs[]);
void animationrighttoleft(int xstart, int xfinish, int ystart, int yfinish,
						  int size, Prong prongs[]);

void victory(Prong prong[]);
void drawrectanglewithborder(int x, int y, int size);
int main(int argc, char* argv[])
{
	Prong prongs[AMOUNT_OF_PRONGS] = {0};
	
	if (gfx_init()) {
		exit(3);
	}
	for (int i = 0; i < AMOUNT_OF_PRONGS; i++) {
		prongs[i] = initializeprong(i);
	}
	while (1) {
		initializebackground();
		drawingdiscs(prongs);
		gfx_updateScreen();
		SDL_Delay(10);
		char firstkey = gfx_getkey();
		if (firstkey == SDLK_ESCAPE || firstkey == SDLK_RETURN) {
			return 0;
		}
		char secondkey = gfx_getkey();
		if (secondkey == SDLK_ESCAPE || secondkey == SDLK_RETURN) {
			return 0;
		}
		firstkey -= 48;
		secondkey -= 48;
		if (firstkey < AMOUNT_OF_PRONGS && secondkey < AMOUNT_OF_PRONGS) {
			movedisc(prongs, firstkey, secondkey);
		}
		victory(prongs);
	}

	return 0;
}
Prong initializeprong(int i)
{
	i++;
	int centerx = i * gfx_screenWidth() / (AMOUNT_OF_PRONGS + 1);
	Prong currentprong = {{0}, 0, centerx};
	if (i == 1) {
		for (int j = 0; j < AMOUNT_OF_DISKS; j++) {
			currentprong.discs[j] = AMOUNT_OF_DISKS - j;
		}
		currentprong.topelement = AMOUNT_OF_DISKS;
	}

	return currentprong;
}

Prong push(Prong operatingprong, int disc)
{
	if (disc != 0) {
		operatingprong.discs[operatingprong.topelement] = disc;
		operatingprong.topelement++;
		return operatingprong;
	}
	return operatingprong;
}

Prong pop(Prong operatingprong)
{
	operatingprong.discs[operatingprong.topelement - 1] = 0;
	operatingprong.topelement--;
	return operatingprong;
}
void movedisc(Prong prongs[], int firstprong, int secondprong)
{
	if (prongs[firstprong].topelement != 0) {
		if (prongs[secondprong].topelement == 0 ||
			prongs[firstprong].discs[prongs[firstprong].topelement - 1] <
				prongs[secondprong].discs[prongs[secondprong].topelement - 1]) {
			Prong temporary = push(
				prongs[secondprong],
				prongs[firstprong].discs[prongs[firstprong].topelement - 1]);
			int xstart = prongs[firstprong].x;
			int xend = prongs[secondprong].x;
			int ystart = prongs[firstprong].topelement * DISC_HEIGHT;
			int yfinish = prongs[secondprong].topelement * DISC_HEIGHT;
			int size =
				prongs[firstprong].discs[prongs[firstprong].topelement - 1];
			prongs[firstprong] = pop(prongs[firstprong]);
			if (firstprong < secondprong) {
				animationlefttoright(xstart, xend, ystart, yfinish, size,
									 prongs);
			}
			else {
				animationrighttoleft(xstart, xend, ystart, yfinish, size,
									 prongs);
			}

			prongs[secondprong] = temporary;
		}
	}
}
void drawingdiscs(Prong prongs[])
{
	for (int i = 0; i < AMOUNT_OF_PRONGS; i++) {
		for (int j = 0; j < prongs[i].topelement; j++) {
			if (prongs[i].discs[j] != 0) {
				int halfdisc =  (gfx_screenWidth() / (AMOUNT_OF_PRONGS + 1) /
							   (AMOUNT_OF_DISKS + 2) / 2);
				drawrectanglewithborder(prongs[i].x, j * DISC_HEIGHT,
										prongs[i].discs[j] * halfdisc);
			}
		}
	}
}
void initializebackground()
{
	gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1, BLACK);
	gfx_filledRect(0, gfx_screenHeight() - GROUND_HEIGHT - 1,
				   gfx_screenWidth() - 1, gfx_screenHeight() - 1, YELLOW);
	for (int i = 1; i <= AMOUNT_OF_PRONGS; i++) {
		int centerx = i * gfx_screenWidth() / (AMOUNT_OF_PRONGS + 1);
		gfx_filledRect(centerx - HALF_WIDTH_OF_PRONG,
					   gfx_screenHeight() - PRONG_HEIGHT - GROUND_HEIGHT - 2,
					   centerx + HALF_WIDTH_OF_PRONG,
					   gfx_screenHeight() - GROUND_HEIGHT - 2, GREEN);
	}
}
void victory(Prong prongs[])
{
	for (int i = 1; i < AMOUNT_OF_PRONGS; i++) {
		if (prongs[i].topelement == AMOUNT_OF_DISKS) {
			initializebackground();
			gfx_textout(gfx_screenWidth() / 2, gfx_screenHeight() / 2,
						"VICTORY", RED);
			drawingdiscs(prongs);
			gfx_updateScreen();

			while (1) {
				if (gfx_getkey() == SDLK_RETURN) {
					exit(3);
				}
			}
		}
	}
}
int animationdowntoup(int x, int ystart, int size, Prong prongs[])
{
	int y = ystart - DISC_HEIGHT;
	int halfdisc =
		gfx_screenWidth() / (AMOUNT_OF_PRONGS + 2) / (AMOUNT_OF_DISKS + 1) / 2;
	for (int i = y; i <= gfx_screenHeight() - GROUND_HEIGHT - PRONG_HEIGHT + 100; i+=STEP) {
		initializebackground();
		drawrectanglewithborder(x, i, size * halfdisc);
		drawingdiscs(prongs);
		gfx_updateScreen();
		SDL_Delay(10);
		y = i;
	}
	return y;
}
int animationuptodown(int x, int yfinish, int size, Prong prongs[])
{
	int y = gfx_screenHeight() - GROUND_HEIGHT - PRONG_HEIGHT + 100 ;
	int halfdisc =
		gfx_screenWidth() / (AMOUNT_OF_PRONGS + 1) / (AMOUNT_OF_DISKS + 2) / 2;
	for (int i = y; i >= yfinish; i -= STEP) {
		initializebackground();
		drawrectanglewithborder(x, i, size * halfdisc);
		drawingdiscs(prongs);
		gfx_updateScreen();
		SDL_Delay(10);
		y = i;
	}
	return y;
}

void animationlefttoright(int xstart, int xfinish, int ystart, int yfinish,
						  int size, Prong prongs[])
{
	int halfdisc =
		gfx_screenWidth() / (AMOUNT_OF_PRONGS + 2) / (AMOUNT_OF_DISKS + 1) / 2;
	int y = ystart;
	int x = xstart;
	y = animationdowntoup(x, y, size, prongs);
	for (int i = x; i <= xfinish; i += STEP) {
		initializebackground();
		drawrectanglewithborder(i, y, size * halfdisc);
		drawingdiscs(prongs);
		gfx_updateScreen();
		SDL_Delay(10);
		x = i;
	}
	y = animationuptodown(x, yfinish, size, prongs);
}
void animationrighttoleft(int xstart, int xfinish, int ystart, int yfinish,
						  int size, Prong prongs[])
{
	int halfdisc =
		gfx_screenWidth() / (AMOUNT_OF_PRONGS + 2) / (AMOUNT_OF_DISKS + 1) / 2;
	int y = ystart;
	int x = xstart;
	y = animationdowntoup(x, y, size, prongs);
	for (int i = x; i >= xfinish; i -= STEP) {
		initializebackground();
		drawrectanglewithborder(i, y, size * halfdisc);
		drawingdiscs(prongs);
		gfx_updateScreen();
		SDL_Delay(10);
		x = i;
	}
	y = animationuptodown(x, yfinish, size, prongs);
}
void drawrectanglewithborder(int x, int y, int size)
{	
	size += HALF_WIDTH_OF_PRONG;
	gfx_filledRect(
		x - size, gfx_screenHeight() - GROUND_HEIGHT - y - 2,
		x + size - 1,
		gfx_screenHeight() - GROUND_HEIGHT - (y + DISC_HEIGHT) - 1, BLUE);
	gfx_rect(x - size, gfx_screenHeight() - GROUND_HEIGHT - y - 1,
			 x + size +1,
			 gfx_screenHeight() - GROUND_HEIGHT - (y + DISC_HEIGHT) - 1,
			 RED);
}
