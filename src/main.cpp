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
#include "GameViewFrame.h"
#include "Paths.h"
#include "SdlBitmap.h"
#include "Sprite.h"
#include "SpriteProvider.h"

#include "lodepng.h"

using namespace std;
namespace fs = boost::filesystem;

int show(const char* filename)
{
  std::cout << "showing " << filename << std::endl;

  std::vector<unsigned char> buffer, image;
  lodepng::load_file(buffer, filename); //load the image file with given filename
  unsigned w, h;
  unsigned error = lodepng::decode(image, w, h, buffer); //decode the png

  //stop if there is an error
  if(error)
  {
    std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    return 0;
  }

  //avoid too large window size by downscaling large image
  unsigned jump = 1;
  if(w / 1024 >= jump) jump = w / 1024 + 1;
  if(h / 1024 >= jump) jump = h / 1024 + 1;

  //init SDL
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cout << "error, SDL video init failed" << std::endl;
    return 0;
  }
  SDL_Surface* scr = SDL_SetVideoMode(w / jump, h / jump, 32, SDL_HWSURFACE);
  if(!scr)
  {
    std::cout << "error, no SDL screen" << std::endl;
    return 0;
  }
  SDL_WM_SetCaption(filename, NULL); //set window caption

  //plot the pixels of the PNG file
  for(unsigned y = 0; y + jump - 1 < h; y += jump)
  for(unsigned x = 0; x + jump - 1 < w; x += jump)
  {
    //get RGBA components
    Uint32 r = image[4 * y * w + 4 * x + 0]; //red
    Uint32 g = image[4 * y * w + 4 * x + 1]; //green
    Uint32 b = image[4 * y * w + 4 * x + 2]; //blue
    Uint32 a = image[4 * y * w + 4 * x + 3]; //alpha

    //make translucency visible by placing checkerboard pattern behind image
    int checkerColor = 191 + 64 * (((x / 16) % 2) == ((y / 16) % 2));
    r = (a * r + (255 - a) * checkerColor) / 255;
    g = (a * g + (255 - a) * checkerColor) / 255;
    b = (a * b + (255 - a) * checkerColor) / 255;

    //give the color value to the pixel of the screenbuffer
    Uint32* bufp;
    bufp = (Uint32 *)scr->pixels + (y * scr->pitch / 4) / jump + (x / jump);
    *bufp = 65536 * r + 256 * g + b;
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
  return done == 2 ? 1 : 0;
}

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

    /*try {
        SharedPtr(SdlBitmap) bmp = BitmapProvider::getInstance().getBitmap("arbres.png");
        bmp->drawTo(scr, Position(10, 10), Rect(0, 0, bmp->surface().w, bmp->surface().h));
    } catch(...) {
        cout << "Error loading image" << endl;
        exit(0);
    }

    SharedPtr(Sprite) sprite = SpriteProvider::getInstance().getSpriteForSurface(Surface_Sand);
    sprite->renderTo(scr, Position(300, 300));
    */

    GameField field(5, 5, 2.0f);
    GameViewFrame frame(field, scr, 46.0f, FloatPosition(1.3f, 1.7f));

    frame.render(scr);

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
	//if(show("D:\\projects\\RunningMan\\build_vs2012\\data\\img\\arbres.png"))
	//	return 0;
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
