#include <stdio.h>
#include <SDL2/SDL.h>
#include"binary.h"
SDL_Surface* greyscale(SDL_Surface* img)
{
  Uint8=r,g,b;
  for(int x=0;x<img->w;x++)
    {
      for(int y=0;y<img->h;y++)
	{
	  pixel = getpixel(img,x,y)
	  SDL_GetRGB(pixel,img->format,&r,&g,&b)
	  gray = (Uint8) (r*0.2126+g*0.7152+b*0.0722)
	  putpixel(img,x,y,SDL_MapRGB(img->format,gray,gray,gray))  
	 }  
      return img

	}
