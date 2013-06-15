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


#include "GameField.h"
#include "SdlBitmap.h"

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

    /*fs::path full_path( fs::initial_path<fs::path>() );
    //full_path = fs::system_complete( fs::path( argv[0] ) );
    fs::path programPath(fs::absolute(full_path).remove_filename());
    programPath /= "data";
    programPath /= "img";
    programPath /= "argres.png";*/
    SDL_FillRect(scr, NULL, SDL_MapRGB(scr->format, 0, 55, 0));

    try {
        SdlBitmap bmp(aFileName);
        //bmp.drawTo(scr, Position(10, 10), Rect(0, 0, bmp.surface().w, bmp.surface().h));
        SDL_Rect srcRect;
        SDL_Rect destRect;
        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.h = 200;
        srcRect.w = 200;
        destRect.x = 100;
        destRect.y = 100;
        destRect.h = 300;
        destRect.w = 300;
        SDL_BlitSurface(&bmp.surface(), &srcRect, scr, &destRect);
        srcRect.y = 200;
        srcRect.x = 200;
        SDL_BlitSurface(&bmp.surface(), &srcRect, scr, &destRect);
    } catch(...) {
        cout << "Error loading image" << endl;
        exit(0);
    }

    /*
	for (int row = 0; row < 100; row++)
	{
		for (int col = 0; col < 100; col++)
		{
			Uint32* pixel = (Uint32*)scr->pixels + (row * scr->pitch / 4) + col;
			*pixel = 65536 * 255; // red
		}
	}
    */
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
    fs::path full_path( fs::initial_path<fs::path>() );
    full_path = fs::system_complete( fs::path( argv[0] ) );
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
