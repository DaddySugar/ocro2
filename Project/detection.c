#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "treatment.h"
#include "detection.h"


/* Draws a red line on the image at certain height between point 'A' and 'B'
 * PARAM : 
 * img : Simply the image 
 * start_$ : Point 'A'
 * end_$ : Point 'B' 
 * int $ : Height or width
 */











void Line_Detection(SDL_Surface* img)
{
	Uint8 r,g,b;
	Uint32 pixel;
	int checked;
	int x;
	for(int y=0;y<img->h;y++)
		{
			checked=0;
			for(x=0;x<img->w;x++)
			{
				pixel = getpixel(img,x,y);
				SDL_GetRGB(pixel,img->format,&r,&g,&b);
				if(r==0 && g==0 && b==0)
				{
					checked=1;
					break;
				}
				
			}
			if (checked==0)
			{
				Horizontal_Line(img,y,0,img->w);
			}
		}
	}
void Height_Detection(SDL_Surface* img)
{
Uint8 r,g,b;
	Uint32 pixel;	
	int pass=1, cut = 1;
	int startpoint = 0, endpoint = 0;
	for(int x=0;x<img->w;x++)
		{
			for(int y=0;y<img->h;y++)
			{
				pixel = getpixel(img,x,y);
				SDL_GetRGB(pixel,img->format,&r,&g,&b);
				if(r==255 && g==255 && b==255 && cut == 1)
				{
					cut = 0;
					startpoint = y;
					endpoint = y;
				}
				if(r==255 && g==0 && b==0 && cut == 0)
				{
					Vertical_Line(img,x,startpoint,endpoint);
					cut = 1;
					pass = 1;
				}
				if(r==0 && g==0 && b==0 && pass == 1)
				{
					pass = 0;
					startpoint = 0;
					endpoint = 0;
				}
				if(r==255 && g==0 && b==0 && cut == 0 && pass == 0)
				{
					pass = 1;
				}
				if(r==255 && g==255 && b==255 && cut == 0 && pass == 1)
				{
					endpoint += 1;
				}
			}			
		}
}
void Horizontal_Line(SDL_Surface* img, int y, int start, int end)
{
	for (int b = start; b < end; b++) 
	{
		putpixel(img, b, y, SDL_MapRGB(img->format, 255, 0, 0));
	}
}
void Vertical_Line(SDL_Surface* img,int x, int start, int end)
{
	for (int b = start; b < end; b++) 
	{
		putpixel(img, x, b, SDL_MapRGB(img->format, 0, 255, 0));
	}
}
SDL_Surface* sdlnewchar(SDL_Surface* img,int minw,int maxw,int minh, int maxh)
{
	Uint8 r,g,b;
	Uint32 pixel;
	SDL_Surface *abc = SDL_CreateRGBSurface(0,maxw-minw,maxh - minh,32,0,0,0, 0);
	for (int x=0;x<abc->w;x++)
	{
		for (int y=0; y<abc->h;y++)
		{
			pixel = getpixel(img,x+minw,y+minh);
			SDL_GetRGB(pixel,img->format,&r,&g,&b);
			putpixel(abc,x,y,SDL_MapRGB(img->format, r, g, b));
			
		}
		
		
		
		
	}
	return abc;
	
	
}

