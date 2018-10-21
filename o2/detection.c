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
{ // Added no need to go through  all the image. 
	Uint8 r,g,b;
	Uint32 pixel;	
	
	//int pass=1, cut = 1;  whats this??? 
	int startpoint = 0, endpoint = 0;  
	int checked = 0; //Black? 
	int empty = 1; // =empty hight | 
		
	//SDL_Surface* va;
	int counter = 0;
	
	for(int x = 0; x < img->w; x++)
		{
			
			empty =1;
			for(int y = start; y < finish+1; y++)
			{
				pixel = getpixel(img,x,y);
				SDL_GetRGB(pixel,img->format,&r,&g,&b);
				/*if(r==255 && g==255 && b==255 && cut == 1)
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
				JUST NO.
				*/
				
				if(r==0 && g==0 && b==0)
				{
					empty = 0;
					if(!checked)
					{
						checked = 1; 
						startpoint = x; 
						//Vertical_Line(img, x, 0, width); Nolimits  
						//break; // Go to the end of line 
						y = finish+1; 
					}
					else y = finish + 1; //Middle of the line 
					//break;
 				}
			
			
			if (checked && empty)  //char check 
			{
				endpoint = x; 
				checked = 0;
				//Height_Detection(img, startpos, finishpost) what?? 
				//Vertical_Line(img,y,startpoint,endpoint);
				//SAVE CHAR AS IMAGE
				savechar(img, start, startpoint, finish, endpoint);
				printf("saved : %d char\n", counter);
				//SDL_Surface* va = sdlnewchar(img,startpoint,endpoint,start, finish);
				//display_image(va);
				remplissage(img, start, finish, startpoint, endpoint);
				counter++;
			}
		}	
	}
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





void savechar(SDL_Surface* img,int x,int y,int w, int h){
		
		SDL_Rect srcrect;
		srcrect.x = x;
		srcrect.y = y;
		srcrect.w = w ;
		srcrect.h = h;
		
		SDL_Rect dstR;
		dstR.x = x;
		dstR.y = y;
		dstR.w = w ;
		dstR.h = h;
        
		
		SDL_Surface*    dst;
		
		SDL_BlitSurface(img, &srcrect, dst, &dstR);
		/*
		char path[10] = "img/";
		path[5] = (char)c;
		char bm[] = ".bmp";
		
		char file[20];
		path[5] = c;
		
		
		
		
		strcat(file,path);
		strcat(file,bm);
		
		char buffer[15];
		for(int i = 0; i < 10; i++)
			buffer[i] = path[i];
		for(int i = 0; i < 4; i++)
			buffer[10+i] = bm[i];
		
		*/
		
		//SDL_SaveBMP(dst,"imag");
		
		
		

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