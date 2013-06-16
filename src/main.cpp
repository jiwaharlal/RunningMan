#ifdef __linux__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif
#include <iostream>
#include <vector>
#include <stdio.h>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include "BitmapProvider.h"
#include "GameField.h"
#include "Paths.h"
#include "SdlBitmap.h"
#include "Sprite.h"
#include "SpriteProvider.h"

using namespace std;
namespace fs = boost::filesystem;

void showSdlSurface(const std::string& aFileName)
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

    SDL_FillRect(scr, NULL, SDL_MapRGB(scr->format, 0, 55, 0));

    try {
        SharedPtr(SdlBitmap) bmp = BitmapProvider::getInstance().getBitmap("arbres.png");
        bmp->drawTo(scr, Position(10, 10), Rect(0, 0, bmp->surface().w, bmp->surface().h));
    } catch(...) {
        cout << "Error loading image" << endl;
        exit(0);
    }

    SharedPtr(Sprite) sprite = SpriteProvider::getInstance().getSpriteForSurface(Surface_Sand);
    sprite->renderTo(scr, Position(300, 300));

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
    Paths::getInstance().setProgramPath(argv[0]);
    //fs::path full_path( fs::initial_path<fs::path>() );
    fs::path full_path = fs::system_complete( fs::path( argv[0] ) );
    fs::path programPath(fs::absolute(full_path).remove_filename());
    programPath /= "data";
    programPath /= "img";
    programPath /= "arbres.png";

    std::cout << programPath; //fs::absolute(full_path).remove_filename() + "data" + "img" + "argres.png" << std::endl;

    if (fs::exists(programPath)) {
        cout << "exists" << endl;
    } else {
        cout << "DON'T exists" << endl;
    }
    //Without file name
    //std::cout << full_path.stem() << std::endl;

	GameField gf(10, 10, 3.0f);
	CellPosition pos = gf.getNearestCell(FloatPosition(6.5, 3.5));
	pos = gf.getNearestCell(FloatPosition(2.5f, 3.5f));
	pos = gf.getNearestCell(FloatPosition(2.5f, 2.5f));

	showSdlSurface(programPath.string());

	return 0;
}
