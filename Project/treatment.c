#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


SDL_Surface *load_image(char *path)
{
  SDL_Surface          *img;
  img = SDL_LoadBMP(path);
  if (!img)
    printf("can't load");
  return img;
}

void display_image(SDL_Surface *image)
{
	
    int quit = 0;
    SDL_Event event;
 
    SDL_Init(SDL_INIT_VIDEO);
 
    SDL_Window * window = SDL_CreateWindow("SDL2 Displaying Image",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
        
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
 
    while (!quit)
    {
        SDL_WaitEvent(&event);
 
        switch (event.type)
        {
            case SDL_QUIT:
                quit = 1;
                break;
        }
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        
    }
 
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
 
    SDL_Quit();
}

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    return *(Uint32 *)p;
}

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
  
  int bpp = surface->format->BytesPerPixel;
  Uint8 *p=(Uint8 *)surface->pixels+y*surface->pitch+x*bpp;

  switch(bpp)
    {
    case 1:
      *p=pixel;
      break;

    case 2:
      *(Uint16 *)p = pixel;
      break;

    case 3:
      
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;


    case 4:
      *(Uint32 *)p = pixel;
      break;
    }
}


void greyscale(SDL_Surface* img)
{
  Uint8 r,g,b;
  Uint32 pixel;
  Uint8 gray;
  for(int x=0;x<img->w;x++)
    {
      for(int y=0;y<img->h;y++)
	{
	  pixel = getpixel(img,x,y);
	  SDL_GetRGB(pixel,img->format,&r,&g,&b);
	  gray = (r*0.2126 + g*0.7152 + b*0.0722);
	  putpixel(img,x,y,SDL_MapRGB(img->format,gray,gray,gray));
	 }  
	}
}
