#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "detection.h"
#include "network/NeuralNetwork.h"
#include "treatment.h"
#include "bitmap.h"
#include "ocr.h"
/*
Matrix surfaceToMatrix(SDL_Surface *downloadBMP)
{
	Uint32 pixel;
	int w = downloadBMP->w;    
	int h = downloadBMP->h;
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Matrix mat = ConstructMatrix(w,h);
	initMatrix(mat);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			pixel = getpixel(downloadBMP, j, i);
			SDL_GetRGB(pixel, downloadBMP->format, &r, &g, &b);
			if (r > 127)
			{
				mat.mat[j + i * mat.y] = 1;
			}
			else
			{
				mat.mat[j + i * mat.y] = 0;
			}
		}
	}
	return mat;
}*/

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
		putpixel(img, w, b, SDL_MapRGB(img->format, 0, 255, 0));
	}
}

void Line_Detection(SDL_Surface* img,queue *q, int* length)
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
					startpos = y-1; 
					//Horizontal_Line(img, y, 0, width);   
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

	                queue *line = newQueue();
			finishpost = y+1; 
			checked = 0; 
			prev =0; 
			//Horizontal_Line(img,y,0,img->w);
			Height_Detection(img, startpos, finishpost,line, length);
			enQueue(q, line);
			
		}
	}
	

		
}


void Height_Detection(SDL_Surface* img, int start, int finish, queue* q, int* length) 
{
	//bitmap *img2 = loadBmp("index2.bmp");
   // draw(img2);
	int c =0 ;
  int oneblack = 0; 
  int startcolum = 0; // first colum to be met  
  int endcolum =0; // last line to be met 
  
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
          startcolum = x-1;
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
		  endcolum = x +1;
		  c++;
		  *length += 1; 
		  savechar(img,start,finish,startcolum,endcolum, q);
		  oneblack = 0;
    }
  } 
}

/*  

void save_char(int width, int height, SDL_Surface* image, int a[],int c[]){
	int j=0;
	for(int i=0;i<50;i++){
		if(a[i]==-1){break;}
		while(c[j]!=-1){
				if(c[j]==-2){break;}
				else{
					int width1= get_width(c[j],a[i],width,image);
					int height2 = get_height(a[i],height,image);
					SDL_Surface* new_surface=SDL_CreateRGBSurface(0,width1-1,height2-1,32,0,0,0,0);
					SDL_Rect first;
					first.x=c[j];
					first.y=a[i];
					first.w=width1;
					first.h=height2;
					SDL_BlitSurface(image,&first,new_surface,NULL);
					char Output[30];
					sprintf (Output,"%s%d%s","file/", j,"_pic.bmp");
					SDL_SaveBMP(new_surface,Output);
				}
				j++;
			}
		j++;
		}
	}
}*/

void savechar(SDL_Surface* img,int x,int y,int w, int h, queue* q){
	SDL_Surface *dst = SDL_CreateRGBSurface(0,h-w,y-x,32,0,0,0,0); 
	Uint32 white = 0xffffffff;
	SDL_FillRect(dst,NULL,white);
	
	SDL_Rect srcrect;
	//SDL_Rect dstrect;
	
	srcrect.x = w-1;
	srcrect.y = x;
	srcrect.w = h-w ;
	srcrect.h = y-x;
	/*
	dstrect.x = 10;
	dstrect.y = 0;
	dstrect.w = 256;
	dstrect.h = 1024;*/
	
	SDL_UnlockSurface(img);
	SDL_BlitSurface(img, &srcrect, dst, NULL);
	enQueue(q, dst);
	SDL_LockSurface(dst);
	char buffer[100]; 
	sprintf (buffer,"%s%d%s","tmpchar/", q->length,"_pic.bmp");
	//printf("Char: %s Saved. \n",buffer);
	SDL_SaveBMP(dst,buffer);
	SDL_UnlockSurface(dst);
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
	printf("GG");
	return abc;
}

int segmentation_GUI(SDL_Surface* img, char txt[] ){
	queue* q = newQueue(); 
	int len = 0; 
	segmentation(img, q, &len,txt);
	return len;
	
}


char* segmentation(SDL_Surface* img,queue *q, int* len, char txt[] ){
	//network *n = loadNetwork("network.save");
	int i = 0;
	

	greyscale(img);
	expansiondynamique(img);
	wholefunction(img);
//	makeitblackandwhite(img,img->w,img->h);
	Line_Detection(img,q, len);
	
	//char txt[*len * 2 + 1];
	txt = malloc(sizeof(char) * (*len * 2+1));
	txt[(*len * 2)] = 0;
	
	
	while (q->length > 0)
	{
		queue *line = deQueue(q);
		while (line->length > 0)
		{
			bitmap* letter = loadBmp(deQueue(line));
			char tmp; 
			
			resize(letter);
			autoContrast(letter);
			binarize(letter);
			draw(letter);
			//printf("\n %d -- \n", q->length);
			tmp = ocrGetChar(letter);
			//tmp = 'e';
			txt[i] = tmp; 
		//	printf("\n %d -- \n", line->length);
			printf("%c\n", tmp);
				i++;
			
			freeBitmap(letter);
			
			
		}

		txt[i] = '\n'; 
		i++; 
	}	
	free(q);
	txt[i] = 0;
	printf("\nOCR done!\n");
	printf("We have found %d Character.\n", *len);
	printf("Text Found: \n%s\n", txt);
	saveText("../OUTPUT.txt",txt);
	return txt; 
} 
