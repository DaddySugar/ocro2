#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "treatment.h"

int main(int argc, char ** argv)
{
	grayscale_BMP("lea.bmp");
	if(argc != 0) return 1; 
	return 0;
}
