#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>

Uint16 createColorPixel(SDL_PixelFormat *fmt, Uint8 red, Uint8 green, Uint8 blue)
{
	Uint16 value;

	value = ((red >> fmt->Rloss) << fmt->Rshift) +
					((green >> fmt->Rloss) << fmt->Rshift) +
					((blue >> fmt->Bloss) << fmt->Bshift);

	return value;
}

void fillScreen(SDL_Surface *screen)
{
	SDL_LockSurface(screen);

	Uint16 *raw_pixels;
	raw_pixels = (Uint16 *)screen->pixels;

	int x, y;
	for (x = 0; x < 256; x++)
	{
		for (y = 0; y < 256; y++)
		{
			Uint16 pixel_color;
			int offset;

			pixel_color = createColorPixel(screen->format, x, 0, y);
			offset = (screen->pitch / 2 * y + x);
			raw_pixels[offset] = pixel_color;
		}
	}

	SDL_UnlockSurface(screen);
	SDL_UpdateRect(screen, 0, 0, 0, 0);
}

int main(int argc, char *argv[])
{
	SDL_Surface *screen;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Unable to initialise SDL: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	atexit(SDL_Quit);

	screen = SDL_SetVideoMode(640, 480, 16, 0);
	if (screen == NULL)
	{
		printf("Unable to set video mode: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	fillScreen(screen);

	bool loopcontinue = true;
	SDL_Event event;
	while (loopcontinue)
	{
		if (SDL_WaitEvent(&event) == 0)
			break;


		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				loopcontinue = false;
			break;

		case SDL_QUIT:
			loopcontinue = false;
			break;
		}
	}

	return EXIT_SUCCESS;
}

