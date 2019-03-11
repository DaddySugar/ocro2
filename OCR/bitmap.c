/**
 * \file bitmap.c
 * \brief Structs and fonctions on bitmap
 * \author astain_d and issarn_t
 * \date 10/04/2016
 *
 */

# include <SDL2/SDL_image.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <err.h>

#include "treatment.h"
# include <math.h>
# include "bitmap.h"

/*#############################################################*/

color newColor(unsigned char r, unsigned char g, unsigned char b)
{
  color col;
  col.r = r;
  col.g = g;
  col.b = b;
  return col;
}

/*#############################################################*/


bitmap *newBitmap(unsigned width, unsigned height, color *content)
{
  bitmap *img = malloc(sizeof(bitmap));
  img->width = width;
  img->height = height;
  img->content = content;
  return img;
}

void freeBitmap(bitmap *img)
{
  free(img->content);
  free(img);
}

/*#############################################################*/

 void draw(bitmap *img)
{
  printf("+");
  for (unsigned i = 0; i < img->width + 2; i++)
    printf("-");
  printf("+\n| ");
  for (unsigned i = 0; i < img->width * img->height; i++)
  {
		if (i % img->width == 0 && i != 0)
      printf(" |\n| ");
    char c = img->content[i].r == 0 ? '#' : ' ';
    printf("%c", c);
  }
  printf(" |\n+");
  for (unsigned i = 0; i < img->width + 2; i++)
    printf("-");
  printf("+\n");
}

/*#############################################################*/

void binarize(bitmap *img)
{
  unsigned short c = 0;
  for (unsigned i = 0; i < img->width * img->height; i++)
  {
    c = img->content[i].r + img->content[i].g + img->content[i].b;
    c = c > 384 ? 255 : 0;
    img->content[i].r = c;
    img->content[i].g = c;
    img->content[i].b = c;
  }
}


void resize(bitmap *img)
{
  unsigned newWidth = 16;
  unsigned newHeight = 16;
  unsigned pos, pos2;
  unsigned count;
  unsigned short sumR, sumG, sumB;
  float rWidth = (float) img->width / newWidth;
  float rHeight = (float) img->height / newHeight;
  color *cont = malloc(sizeof(color) * newWidth * newHeight);
  for (unsigned y = 0; y < newHeight; y++)
  {
    for (unsigned x = 0; x < newWidth; x++)
    {
      sumR = 0;
      sumG = 0;
      sumB = 0;
      count = 0;
      for (unsigned i = x * rWidth; i < x * rWidth + rWidth; i++)
        for (unsigned j = y * rHeight; j < y * rHeight + rHeight; j++)
        {
          pos = i + j * img->width;
          sumR += img->content[pos].r;
          sumG += img->content[pos].g;
          sumB += img->content[pos].b;
          count++;
        }
      pos2 = x + y * newWidth;
      cont[pos2].r = sumR / count;
      cont[pos2].g = sumG / count;
      cont[pos2].b = sumB / count;
    }
  }
  free(img->content);
  img->content = cont;
  img->width = newWidth;
  img->height = newHeight;
}

/*#############################################################*/

bitmap *loadBmp(SDL_Surface *downloadBMP)
{
	Uint32 pixel;
	
	unsigned char  r;
	unsigned char  g;
	unsigned char  b;

	bitmap *bmp = malloc(sizeof(bitmap));

  bmp->width = downloadBMP->w;    
  bmp->height = downloadBMP->h;
  bmp->content = malloc(sizeof(color) * bmp->width * bmp->height);

  int padding = 4 - (bmp->width * 3) % 4;
  if (padding == 4)
    padding = 0;

  color px;
  for (int i = bmp->height - 1; i >= 0; i--)
  {
    for (unsigned j = 0; j < bmp->width; j++)
    {
		
		pixel = getpixel(downloadBMP, j, i);
		SDL_GetRGB(pixel, downloadBMP->format, &r, &g, &b);
		
		px.r = r;
		px.g = g; 
		px.b = b;
		bmp->content[i * bmp->width + j] = px;
		
    }
  }
  return bmp;
}

/*#############################################################*/

void autoContrast(bitmap *img)
{
  unsigned *histoR = malloc(256 * sizeof(unsigned ));
  unsigned *histoG = malloc(256 * sizeof(unsigned ));
  unsigned *histoB = malloc(256 * sizeof(unsigned ));

  unsigned *histoRC = malloc(256 * sizeof(unsigned));
  unsigned *histoGC = malloc(256 * sizeof(unsigned));
  unsigned *histoBC = malloc(256 * sizeof(unsigned));

  unsigned cR = 0;
  unsigned cG = 0;
  unsigned cB = 0;

  unsigned j;  
  unsigned n = img->width * img->height;

  for (j = 0; j < 256; j++)
  {
    histoR[j] = 0;
    histoG[j] = 0;
    histoB[j] = 0;
  }
  for (j = 0; j < 256; j++)
  {
    histoRC[j] = 0;
    histoGC[j] = 0;
    histoBC[j] = 0;
  }
  for (j = 0; j < n; j++)
  {
    histoR[img->content[j].r]++;
    histoG[img->content[j].g]++;
    histoB[img->content[j].b]++;
  }

  for (j = 0; j < 256; j++) 
  {
    cR += histoR[j];
    histoRC[j] = cR;
    cG += histoG[j];
    histoGC[j] = cG;
    cB += histoB[j];
    histoBC[j] = cB;
  }
  
  for (j = 0; j < n; j++)
  {
    img->content[j].r = 255 * histoRC[img->content[j].r] / n;
    img->content[j].g = 255 * histoGC[img->content[j].g] / n;
    img->content[j].b = 255 * histoBC[img->content[j].b] / n;
  }

  free(histoR);
  free(histoG);
  free(histoB);
  free(histoRC);
  free(histoGC);
  free(histoBC);
}

/*#############################################################*/
