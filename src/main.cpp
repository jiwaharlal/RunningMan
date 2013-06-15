#ifdef __linux__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif
#include <iostream>
#include <vector>

#include "GameField.h"

using namespace std;

class Screen;
class Position;
class Direction;

class Sprite
{
public:
	void DrawAt(Screen& aScreen, const Position& aOrigin);
	void SetDirection(const Direction& aDirection);
private:
};

class StaticSprite
{
public:
	void DrawAt(Screen& aScreen, const Position& aOrigin);
};


class Rect;


class GameWorld
{
};

class GameViewFrame
{
public:
	void SetPosition(const Position& aPosition);
	void SetViewDirection(const Direction& aDirection);
	void GetObjectsInZOrder();
};

void showSdlSurface()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "error, cannot init SDL" << endl;
		return;
	}
	SDL_Surface* scr = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);

	if (!scr)
	{
		cout << "error creating SDL screen" << endl;
		return;
	}
	SDL_WM_SetCaption("sdl window", NULL);

	for (int row = 0; row < 100; row++)
	{
		for (int col = 0; col < 100; col++)
		{
			Uint32* pixel = (Uint32*)scr->pixels + (row * scr->pitch / 4) + col;
			*pixel = 65536 * 255; // red
		}
	}

	//pause until you press escape and meanwhile redraw screen
	SDL_Event event;
	int done = 0;
	while(done == 0)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT) done = 2;
			else if(SDL_GetKeyState(NULL)[SDLK_ESCAPE]) done = 2;
			else if(event.type == SDL_KEYDOWN) done = 1; //press any other key for next image
		}
		SDL_UpdateRect(scr, 0, 0, 0, 0); //redraw screen
		SDL_Delay(5); //pause 5 ms so it consumes less processing power
	}

	SDL_Quit();
	//return done == 2 ? 1 : 0;
}

int main(int argc, char* argv[])
{
	GameField gf(10, 10, 3.0f);
	CellPosition pos = gf.getNearestCell(FloatPosition(6.5, 3.5));
	pos = gf.getNearestCell(FloatPosition(2.5f, 3.5f));
	pos = gf.getNearestCell(FloatPosition(2.5f, 2.5f));

	showSdlSurface();

	return 0;
}
