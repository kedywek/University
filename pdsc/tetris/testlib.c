#include "pieces.inl"
#include "primlib.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NUM_COLS 10
#define NUM_ROWS 20
#define BORDER_MARGIN_Y 100
#define BORDER_MARGIN_X 50
#define FIXED_BLOCK 9

typedef struct {
	int x;
	int y;
} Point;

typedef struct {
	Point center;
	Point pivot;
	Point blocks[4];
	int type;
	int rotation;
} Piece;

Piece handleKeys(Piece piece);
int calculateBlockSize();
void drawGame(Piece piece);
void drawBorder();
void drawGrid();
Piece newPiece();
void drawPiece();
void drawSqaure(Piece piece, int i, int j);
Piece pieceFall(Piece piece);
void drawFixedPieces();
Piece movePieceRight(Piece piece);
Piece movePieceLeft(Piece piece);
Piece rotatePiece(Piece piece);
Piece fallTillDown(Piece piece);
bool checkRow(int y);
void clearRow();
void moveRows(int from);
Piece nextPiece();
void lose();

int gameField[NUM_ROWS][NUM_COLS];
int currentType;
int currentRotation;
int nextType;
int nextRotation;
int block_size;

int main(int argc, char* argv[])
{
	time_t tt;
	int seed = time(&tt);
	srand(seed);
	currentType = rand() % 7;
	currentRotation = rand() % 4;
	nextType = rand() % 7;
	nextRotation = rand() % 4;
	if (gfx_init()) {
		exit(3);
	}
	block_size = calculateBlockSize();
	Piece piece = newPiece();
	while (1) {
		drawGame(piece);
		for (int i = 0; i < 10; i++) {
			SDL_Delay(50);
			drawGame(piece);
			piece = handleKeys(piece);
			gfx_updateScreen();
		}
		lose();
		piece = pieceFall(piece);
		clearRow();
	}
}
Piece handleKeys(Piece piece)
{

	int key = gfx_pollkey();
	if (key == SDLK_ESCAPE) {
		exit(0);
	}
	else if (key == SDLK_RIGHT) {
		key = 10;
		piece = movePieceRight(piece);
	}
	else if (key == SDLK_LEFT) {
		key = 10;
		piece = movePieceLeft(piece);
	}
	else if (key == SDLK_SPACE) {
		key = 10;
		piece = rotatePiece(piece);
	}
	else if (key == SDLK_DOWN) {
		key = 10;
		piece = fallTillDown(piece);
	}
	return piece;
}

int calculateBlockSize()
{
	int blockSizeWidth = (gfx_screenWidth() - BORDER_MARGIN_X * 2) / NUM_COLS;
	int blockSizeHeight = (gfx_screenHeight() - BORDER_MARGIN_Y) / NUM_ROWS;
	int blockSize = fmin(blockSizeWidth, blockSizeHeight);

	return blockSize;
}
void drawGame(Piece piece)
{
	gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1, BLACK);
	drawBorder();
	drawGrid();
	drawPiece(piece);
	drawFixedPieces();
	drawPiece(nextPiece());
}
void drawFixedPieces()
{
	int blockSize = calculateBlockSize();
	int borderMarginX = (gfx_screenWidth() - NUM_COLS * blockSize) / 2;
	int borderMarginY = (gfx_screenHeight() - NUM_ROWS * blockSize);

	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLS; j++) {
			if (gameField[i][j] != 0) {
				int x = borderMarginX + j * blockSize;
				int y = borderMarginY + i * blockSize;
				if (gameField[i][j] == 9) {
					gfx_filledRect(x, y, x + blockSize, y + blockSize, RED);
				}
			}
		}
	}
}
void drawBorder()
{
	int borderMarginX = (gfx_screenWidth() - NUM_COLS * block_size) / 2;
	int borderMarginY = (gfx_screenHeight() - NUM_ROWS * block_size);

	gfx_line(borderMarginX, borderMarginY, borderMarginX,
			 gfx_screenHeight() - 1, YELLOW);
	gfx_line(borderMarginX + NUM_COLS * block_size, borderMarginY,
			 borderMarginX + NUM_COLS * block_size, gfx_screenHeight() - 1,
			 YELLOW);
}

void drawGrid()
{
	int borderMarginX = (gfx_screenWidth() - NUM_COLS * block_size) / 2;
	int borderMarginY = (gfx_screenHeight() - NUM_ROWS * block_size);

	for (int i = 0; i <= NUM_COLS; i++) {
		int x = borderMarginX + i * block_size;
		gfx_line(x, borderMarginY, x, borderMarginY + NUM_ROWS * block_size,
				 WHITE);
	}

	for (int i = 0; i <= NUM_ROWS; i++) {
		int y = borderMarginY + i * block_size;
		gfx_line(borderMarginX, y, borderMarginX + NUM_COLS * block_size, y,
				 WHITE);
	}
}
Piece newPiece()
{
	int counter = 1;
	Piece newPiece;
	newPiece.type = currentType;
	newPiece.rotation = currentRotation;
	int borderMarginX = (gfx_screenWidth() - NUM_COLS * block_size) / 2;
	int borderMarginY = (gfx_screenHeight() - NUM_ROWS * block_size);
	newPiece.center.x = borderMarginX + NUM_COLS / 2 * block_size;
	newPiece.center.y = borderMarginY + 2 * block_size;
	newPiece.blocks[0].x = NUM_COLS / 2;
	newPiece.blocks[0].y = 2;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (pieces[newPiece.type][newPiece.rotation][i][j] == 2) {
				newPiece.pivot.x = j;
				newPiece.pivot.y = i;
				goto secondloop;
			}
		}
	}
secondloop:
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (pieces[newPiece.type][newPiece.rotation][i][j] == 1) {
				Point block;
				block.x = newPiece.blocks[0].x - newPiece.pivot.x + j;
				block.y = newPiece.blocks[0].y - newPiece.pivot.y + i;
				newPiece.blocks[counter] = block;
				counter++;
			}
		}
	}
	return newPiece;
}
Piece nextPiece()
{
	int counter = 1;
	Piece newPiece;
	newPiece.type = nextType;
	newPiece.rotation = nextRotation;
	newPiece.center.x = gfx_screenWidth() - NUM_COLS * block_size + 100;
	newPiece.center.y = (gfx_screenHeight() - NUM_ROWS * block_size);
	newPiece.blocks[0].x = 0;
	newPiece.blocks[0].y = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (pieces[newPiece.type][newPiece.rotation][i][j] == 2) {
				newPiece.pivot.x = j;
				newPiece.pivot.y = i;
				goto secondloop;
			}
		}
	}
secondloop:
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (pieces[newPiece.type][newPiece.rotation][i][j] == 1) {
				Point block;
				block.x = newPiece.blocks[0].x - newPiece.pivot.x + j;
				block.y = newPiece.blocks[0].y - newPiece.pivot.y + i;
				newPiece.blocks[counter] = block;
				counter++;
			}
		}
	}
	return newPiece;
}
void drawPiece(Piece piece)
{

	for (int i = 0; i < 4 - piece.pivot.y; i++) {
		for (int j = 0; j < 4 - piece.pivot.x; j++) {
			drawSqaure(piece, i, j);
		}
	}

	for (int i = 0; i < 4 - piece.pivot.y; i++) {
		for (int j = 0; j >= -piece.pivot.x; j--) {
			drawSqaure(piece, i, j);
		}
	}

	for (int i = 0; i >= -piece.pivot.y; i--) {
		for (int j = 0; j < 4 - piece.pivot.x; j++) {
			drawSqaure(piece, i, j);
		}
	}

	for (int i = 0; i >= -piece.pivot.y; i--) {
		for (int j = 0; j >= -piece.pivot.x; j--) {
			drawSqaure(piece, i, j);
		}
	}
}

void drawSqaure(Piece piece, int i, int j)
{

	if (pieces[piece.type][piece.rotation][piece.pivot.y + i]
			  [piece.pivot.x + j] == 2) {
		gfx_filledRect(piece.center.x + j * block_size,
					   piece.center.y + i * block_size,
					   piece.center.x + (j + 1) * block_size,
					   piece.center.y + (i + 1) * block_size, YELLOW);
	}
	else if (pieces[piece.type][piece.rotation][piece.pivot.y + i]
				   [piece.pivot.x + j] == 1) {
		gfx_filledRect(piece.center.x + j * block_size,
					   piece.center.y + i * block_size,
					   piece.center.x + (j + 1) * block_size,
					   piece.center.y + (i + 1) * block_size, GREEN);
	}
}
Piece pieceFall(Piece piece)
{
	bool overlap = 0;
	for (int i = 0; i < 4; i++) {
		if (piece.blocks[i].y + 1 >= NUM_ROWS) {
			overlap = 1;
			break;
		}
		if (gameField[piece.blocks[i].y + 1][piece.blocks[i].x] != 0) {
			overlap = 1;
			break;
		}
	}
	if (overlap == 0) {
		for (int i = 0; i < 4; i++) {
			piece.blocks[i].y++;
		}
		piece.center.y += block_size;
	}
	else {
		currentType = nextType;
		currentRotation = nextRotation;
		nextType = rand() % 7;
		nextRotation = rand() % 4;
		for (int i = 0; i < 4; i++) {
			if (piece.blocks[i].y >= 0) {
				gameField[piece.blocks[i].y][piece.blocks[i].x] = 9;
			}
		}
		piece = newPiece();
	}
	return piece;
}
Piece fallTillDown(Piece piece)
{
	bool overlap = 0;
	while (overlap == 0) {
		for (int i = 0; i < 4; i++) {
			if (piece.blocks[i].y + 1 >= NUM_ROWS ||
				gameField[piece.blocks[i].y + 1][piece.blocks[i].x] == 9) {
				overlap = 1;
				break;
			}
		}
		piece = pieceFall(piece);
	}
	return piece;
}
Piece movePieceRight(Piece piece)
{
	for (int i = 0; i < 4; i++) {
		if (piece.blocks[i].x + 1 >= NUM_COLS ||
			gameField[piece.blocks[i].y][piece.blocks[i].x + 1] == FIXED_BLOCK)
			return piece;
	}
	for (int i = 0; i < 4; i++) {
		piece.blocks[i].x++;
	}
	piece.center.x += block_size;
	return piece;
}
Piece movePieceLeft(Piece piece)
{
	for (int i = 0; i < 4; i++) {
		if (piece.blocks[i].x - 1 < 0 ||
			gameField[piece.blocks[i].y][piece.blocks[i].x - 1] ==
				FIXED_BLOCK) {
			return piece;
		}
	}
	for (int i = 0; i < 4; i++) {
		piece.blocks[i].x--;
	}
	piece.center.x -= block_size;
	return piece;
}
Piece rotatePiece(Piece piece)
{
	Piece newPiece = piece;
	newPiece.rotation = (newPiece.rotation + 1) % 4;
	int counter = 1;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (pieces[newPiece.type][newPiece.rotation][i][j] == 2) {
				newPiece.pivot.x = j;
				newPiece.pivot.y = i;
				goto secondloop;
			}
		}
	}
secondloop:
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (pieces[newPiece.type][newPiece.rotation][i][j] == 1) {
				Point block;
				block.x = newPiece.blocks[0].x - newPiece.pivot.x + j;
				block.y = newPiece.blocks[0].y - newPiece.pivot.y + i;
				newPiece.blocks[counter] = block;
				counter++;
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		if (newPiece.blocks[i].x < 0 || newPiece.blocks[i].x >= NUM_COLS ||
			newPiece.blocks[i].y >= NUM_ROWS ||
			gameField[newPiece.blocks[i].y][newPiece.blocks[i].x] != 0) {
			return piece;
		}
	}
	return newPiece;
}
bool checkRow(int y)
{
	for (int x = 0; x < NUM_COLS; x++) {
		if (gameField[y][x] != FIXED_BLOCK) {
			return false;
		}
	}
	return true;
}

void clearRow()
{
	for (int y = NUM_ROWS - 1; y > 0; y--) {
		if (checkRow(y)) {
			moveRows(y);
			clearRow();
		}
	}
}

void moveRows(int from)
{
	for (int x = 0; x < NUM_COLS; x++) {
		for (int y = from - 1; y > 0; y--) {
			gameField[y + 1][x] = gameField[y][x];
		}
	}
}
void lose(Piece piece)
{
	bool overlap = 0;
	for (int i = 0; i < 4; i++) {
		if (gameField[piece.blocks[i].y + 1][piece.blocks[i].x] != 0) {
			overlap = 1;
			break;
		}
	}
	if (overlap == 1) {
		gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1,
					   BLACK);
		gfx_textout(gfx_screenWidth() / 2, gfx_screenHeight() / 2, "TRY AGAIN",
					RED);
					
		gfx_updateScreen();
		int key;
		do {
			key = gfx_getkey();

		} while (key != SDLK_RETURN && key != SDLK_ESCAPE);
		exit(3);
	}
}
