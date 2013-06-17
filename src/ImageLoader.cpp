#include "ImageLoader.h"

#include <vector>
#include <lodepng.h>

//#include "LodePngImageLoader.h"

ImageLoader::ImageLoader()
{}

ImageLoader&
ImageLoader::getInstance()
{
	static SharedPtr(ImageLoader) instance(new ImageLoader());

	return *instance;
}

SDL_Surface*	
ImageLoader::loadImage(const std::string& aFilePathName)
{
	std::vector<unsigned char> buffer, image;
	lodepng::load_file(buffer, aFilePathName); //load the image file with given filename
	unsigned w, h;
	unsigned error = lodepng::decode(image, w, h, buffer); //decode the png

	//stop if there is an error
	if(error)
	{
		std::string errorText(lodepng_error_text(error));
		std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
		return NULL;
	}

	//init SDL
	/*if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "error, SDL video init failed" << std::endl;
		return 0;
	}
	SDL_Surface* scr = SDL_SetVideoMode(w, h, 32, SDL_HWSURFACE);
	if(!scr)
	{
		std::cout << "error, no SDL screen" << std::endl;
		return 0;
	}
	SDL_WM_SetCaption(filename, NULL); //set window caption
	*/
    Uint32 rmask, gmask, bmask, amask;

    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    //surface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32,
    //                               rmask, gmask, bmask, amask);
	SDL_Surface *surface = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCCOLORKEY | SDL_SRCALPHA,	w, h, 32, rmask, gmask, bmask, amask);

	if(surface == NULL) {
        fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
        exit(1);
    }
	
	//plot the pixels of the PNG file
	for(unsigned y = 0; y < h; y++)
	{
		for(unsigned x = 0; x < w; x++)
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
			bufp = (Uint32 *)surface->pixels + (y * surface->pitch / 4) + x;
			*bufp = 65536 * r + 256 * g + b;
		}
	}

	return surface;
}