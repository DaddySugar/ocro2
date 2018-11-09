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
 
/*void drawH(SDL_Surface* img, int hight, int start, int end)
{	
}*/

//MOVE EASY FUNCTIONS UP
void Horizontal_Line(SDL_Surface* img, int y, int start, int end)
{
	for (int b = start; b < end; b++) 
	{
		putpixel(img, b, y, SDL_MapRGB(img->format, 255, 0, 0));
	}
}

//BEUG
void Vertical_Line(SDL_Surface* img,int w, int start, int end)
{
	for (int b = start; b < end; b++) 
	{
		putpixel(img, w, b, SDL_MapRGB(img->format, 0, 0, 0));
	}
}

void Line_Detection(SDL_Surface* img)
{
	Uint8 r,g,b;
	Uint32 pixel;
	int checked = 0; //If black : check 
	int prev =0;    // is prev line black
	int empty = 1;  // Empty line
	
	// coordinated of the two limits of line : 
	int startpos; 
	int finishpost; 
	
	int width = img->w;
	
	//int x;
	for(int y=0;y<img->h;y++)
		{
			empty = 1;
			for(int x=0;x<width;x++)
			{
				pixel = getpixel(img,x,y);
				SDL_GetRGB(pixel,img->format,&r,&g,&b);
				if(r==0 && g==0 && b==0)
				{
					//checked=1;
					empty = 0;
					if(!prev && !checked)
					{
						prev = 1; 
						checked = 1; 
						startpos = y; 
						Horizontal_Line(img, y, 0, width);   
						//Middle letter taller than first letter, thats why start from0
						break; // Go to the end of line  
					}
					else break; //Middle of the line 
					//
					//break;
 				}
			}
			if (checked && prev && empty)  //char check 
			{
				finishpost = y; 
				checked = 0; 
				prev =0; 
				Horizontal_Line(img,y,0,img->w);
				Height_Detection(img, startpos, finishpost);
			}
		}
}
void Height_Detection(SDL_Surface* img, int start, int finish) 
{
	//bitmap *img2 = loadBmp("index2.bmp");
   // draw(img2);
	int c =0 ;
  int oneblack = 0; 
  printf("%d    %d     %d \n", c, img->w, img->h);
  int startcolum = 0; // first colum to be met  
  int endcolum; // last line to be met 
  int index =0;
  
  for(int x = 0; x < img->w; x++)
  {
    int oneblank = 1;
    for( int y= start; y<= finish; y++)
    {
      Uint32 pixel = getpixel(img, x, y);
      Uint8 r = 0, g = 0, b = 0;
      SDL_GetRGB(pixel, img->format, &r, &g, &b);
      if (r == 0)
      {
        oneblank = 0;
        if (oneblack == 0)
        {
          oneblack = 1;
          startcolum = x;
          y = finish+1;
        }
        else
        {
          y= finish + 1;
        }
      }
    }
    if (oneblack == 1 && oneblank == 1)
    {
		  endcolum = x - 1;
		  c++; 
		  
		  savechar(img,start,finish,startcolum,endcolum,index);
		  index++;
		  oneblack = 0;
    }
  }
}

int **CreateIntMatrix(int width, int height)
{
	int **matrix =
		(int **)malloc(sizeof(int *) * height);
	for (int i = 0; i < height; i++)
	{
		*(matrix + i) = (int *)malloc(sizeof(int) * width);
	}
	return matrix;
}


void savechar(SDL_Surface* img,int x,int y,int w, int h, int index){
	/*SDL_Surface *dst = SDL_CreateRGBSurface(0,y-x, h-w,32,0,0,0,0); 
	Uint32 white = 0xffffffff;
	SDL_FillRect(dst,NULL,white);
	
	SDL_Rect srcrect;
	SDL_Rect dstrect;
	
	srcrect.x = w-1;
	srcrect.y = x;
	srcrect.w = h-w;
	srcrect.h = y-x;
	dstrect.x = 10;
	dstrect.y = 0;
	dstrect.w = 256;
	dstrect.h = 1024;
	

	
	printf("w : %d\n",w); 
	printf("h : %d\n",h); 
	printf("x : %d\n",x); 
	printf("y : %d\n",y); 
	
	SDL_UnlockSurface(img);
	SDL_BlitSurface(img, &srcrect, dst, &dstrect);
	SDL_LockSurface(dst);a
	char buffer[100]; 
	sprintf(buffer,"SaveTMP%d",index); 
	SDL_SaveBMP(dst,buffer);
	SDL_UnlockSurface(dst);*/
	/*unsigned height = y-x; 
	unsigned width = h-w;
	bitmap* srcimg = loadBmp("index.bmp");
	color *content = malloc(sizeof(color) * height * width);
	for (unsigned i = 0; i < height; i++)
	{
		printf("saved %d",i);
		for (unsigned j = 0; j < width; j++)
		  content[i * width + j] = srcimg->content[(i + y) * srcimg->width + j + x];
	  }
	char buffer[100]; 
	
	sprintf(buffer,"tmpqw/SaveTMP%d",index); 
	bitmap *bmp = newBitmap(width, height, content);
	//saveBmp(buffer,bmp);
	resize(bmp);
	draw(bmp);*/
	//int height = y-x; 
	int width = h-w;
	
	printf("w : %d\n",w); 
	printf("h : %d\n",h); 
	printf("x : %d\n",x); 
	printf("y : %d\n",y); 
	
	printf("%d \n +", index);
  for (int i = 0; i < width+ 2; i++)
    printf("-");
  printf("+\n| ");
  Uint32 pixel;
  Uint8 r = 0, g = 0, b = 0;
	
	for(;x<y ;x++)
	{
		for(;w<h;w++)
		{
			pixel = getpixel(img,w,x);
			SDL_GetRGB(pixel,img->format,&r,&g,&b);
			if(r==0) printf("#");
			else printf(" ");
		}
	}
	
	printf("+");
  for (int i = 0; i < width+ 2; i++)
    printf("-");
  printf("+\n| ");
}


void remplissage(SDL_Surface *image, int startline, int endline, int startcolum, int endcolum)
{
  for (int y = startline; y <= endline; y++)
  {
    for (int x = startcolum; x <= endcolum; x++)
    {
      Uint32 pixel = getpixel(image, x, y);
      Uint8 r = 255, g = 0, b = 0;
      pixel = SDL_MapRGB(image->format, r, g, b);
      putpixel(image, x, y, pixel);
    }
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
