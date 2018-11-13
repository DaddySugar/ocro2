#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "treatment.h"
#include "detection.h"


int main(int argc, char ** argv)
{
	//unsigned long param = strtoul(argv[1], NULL, 10);
	SDL_Surface * img;
	
	if(argv[1][0] == '0') {
		img = load_image("lena.bmp");
		greyscale(img);
		display_image(img);
		}
		
	else if(argv[1][0] == '1'){
		img = load_image("lena.bmp");
		greyscale(img);
		makeitblackandwhite(img,img->w,img->h);
		display_image(img);
	}
	else if(argv[1][0] == '3')
		{
			
			img = load_image("index.bmp");
			greyscale(img);
			makeitblackandwhite(img,img->w,img->h);
			Line_Detection(img);
		}
			
	else{
	
		img = load_image("index.bmp");

		if(argv[1][0] == '2') Line_Detection(img);
		
		
		
		else if(argv[1][0] == '4') {
			SDL_Surface *abc = sdlnewchar(img,450,500,200,250);
			display_image(abc);
		}
		
		else if(argv[1][0] == '6')
		{
			img = load_image("pdf_test.bmp");
			greyscale(img);
			makeitblackandwhite(img,img->w,img->h);
			Line_Detection(img);
		}
		
		else if(argv[1][0] == '7')
		{
			img = load_image("pdf_test.bmp");
			greyscale(img);
			makeitblackandwhite(img,img->w,img->h);
			Line_Detection(img);
			//Height_Detection(img);
		}
		else {
			printf("\tThis option does not exist\n");
			return 1; 
		}
}
	
	if(argv[1][0] != '4' && argv[1][0] != '0' && argv[1][0] != '1' )
		display_image(img);
	

	if(argc != 0) return 1; 
	return 0;
}
