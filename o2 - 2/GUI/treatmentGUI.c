#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../treatment.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void new_format(char text[], char format[], char buffer[])
{
	char tmp[strlen(text)];
	size_t i = 0;
	//printf("[new_format] - while loop: ");
	while(i < strlen(text)-4 && (text[i] != '.' || text[i+1] != 'b'))
	{
		tmp[i] = text[i];
		//printf("%c",text[i]);
		i++;
	}
	tmp[i] = 0;
	printf("\n");
	sprintf (buffer,"%s%s%s",tmp,format,".bmp");
}

void grayscale_GUI(char *input)
{
	SDL_Surface * img;
	img = load_image(input);
	greyscale(img);
	/*
	char path[200];
	for(uint j = 0; j < strlen(input); j++)
		path[j] = input[j];
	char format[] = "_grayed";
	char buffer[strlen(input) + strlen(format)];
	new_format(path,format,buffer);
	*/
	SDL_SaveBMP(img,input);
}


void binarize_GUI(char *input)
{
	SDL_Surface * img;
	img = load_image(input);
	expansiondynamique(img);
	wholefunction(img);
	/*
	char path[200];
	for(uint j = 0; j < strlen(input); j++)
		path[j] = input[j];
	char format[] = "_bin";
	char buffer[strlen(input) + strlen(format)];
	new_format(path,format,buffer);
	*/
	SDL_SaveBMP(img,input);
}

SDL_Surface* rotate90_l(SDL_Surface* img)
{
	Uint32 pixel;
	Uint8 r,g,b;
	SDL_Surface* img2=SDL_CreateRGBSurface(0,img->h,img->w,32,0,0,0,0);
	for(int y = 0;y<img->h;y++)
    {
        for(int x = 0;x<img->w;x++)
		{
			 pixel=getpixel(img,x,y);
             SDL_GetRGB(pixel,img->format,&r,&g,&b);
             putpixel(img2,y,(img2->h)-x,SDL_MapRGB(img->format,r,g,b));
		}
	}
	return img2;
}

SDL_Surface* rotate90_r(SDL_Surface* img)
{
	Uint32 pixel;
	Uint8 r,g,b;
	SDL_Surface* img2=SDL_CreateRGBSurface(0,img->h,img->w,32,0,0,0,0);
	for(int y = 0;y<img->h;y++)
    {
        for(int x = 0;x<img->w;x++)
		{
			 pixel=getpixel(img,x,y);
             SDL_GetRGB(pixel,img->format,&r,&g,&b);
             putpixel(img2,(img2->w)-y,x,SDL_MapRGB(img->format,r,g,b));
		}
	}
	return img2;
}
