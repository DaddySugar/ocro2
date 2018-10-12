#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "treatment.h"


int main(int argc, char ** argv)
{
	SDL_Surface * img = load_image("images/index.bmp");
	greyscale(img);
	display_image(img);
	return 0;
}
