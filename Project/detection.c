#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "treatment.h"


/* Draws a red line on the image at certain height between point 'A' and 'B'
 * PARAM : 
 * img : Simply the image 
 * start_$ : Point 'A'
 * end_$ : Point 'B' 
 * int $ : Height or width
 */

SDL_Surface* drawLine(SDL_Surface *img, int start_x, int end_x, int y)
{
	int k = start_x; 
	for (; k < end_x; k++) putpixel(img, start_x, y, SDL_MapRGB(img->format, 255, 0, 0));
	return img;
}

SDL_Surface* drawColumn(SDL_Surface *img, int start_y, int end_y, int x)
{
       	for (; start_y < end_y; start_y++) putpixel(img, x, start_y, SDL_MapRGB(img->format, 255, 0, 0));
	return (img);
}

int Line_Detection(SDL_Surface* img)
{
int list_lines[img->h];
  Uint32      pxl;
  Uint8       pxlcolor;
  for (int x = 0; x < img->h; x++)
    list_lines[x] = -1;
  int         i = 0; //list index
  int         prev_pxl = 0;
  for (int y = 0; y < img->h; y++)
  {
    for (int x = 0; x < img->w; x++)
    {
      pxl = getpixel(img, x, y);
      SDL_GetRGB(pxl, img->format, &pxlcolor, &pxlcolor, &pxlcolor);
      if (pxlcolor == 0)
      {
        if(prev_pxl == 1) //is previous pixel black?
        {
          list_lines[y] = 1;
          i++;
	drawLine(img,0, img->w, y);
break;
        }
        else
          prev_pxl = 1;
      }
      else
        prev_pxl = 0;
    }
  }
  return list_lines[img->h];
}
