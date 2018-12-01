#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>

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
 
    SDL_Window * window = SDL_CreateWindow("SDL2 Displaying Image", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, image->w, image->h, 0);
        
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

void grayscale(SDL_Surface* img)
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

void makeitblackandwhite(SDL_Surface *surface, int maxx, int maxy)
{
  for(int x=0; x!=maxx; x++)
    {
      for(int y=0; y!=maxy; y++)
	{
	  Uint8 red;
	  Uint8 blue;
	  Uint8 green;
	  Uint32 pixel = getpixel(surface, x, y);
	  SDL_GetRGB(pixel, surface->format, &red, &blue, &green);
	  if(red < 130)
	    {
	      Uint32 noir= SDL_MapRGB(surface->format, 0,0,0);
	      putpixel(surface,x,y,noir);
	    }
	  else
	    {
	      Uint32 blanc= SDL_MapRGB(surface->format,255,255,255);
	      putpixel(surface,x,y,blanc);
	    }
	}
    }
}

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
	grayscale(img);
	char path[200];
	for(uint j = 0; j < strlen(input); j++)
		path[j] = input[j];
	char format[] = "_grayed";
	char buffer[strlen(input) + strlen(format)];
	new_format(path,format,buffer);
	SDL_SaveBMP(img,buffer);
}

int histogramme(SDL_Surface *img,int* histo)
{
Uint32 pixel;
Uint8 r,g,b;
int total=0;

for(int x=0;x<img->w;x++)
    {
        for(int y=0;y<img->h;y++)
            {
                pixel = getpixel(img,x,y);
                SDL_GetRGB(pixel,img->format,&r,&g,&b);
                histo[r]+=1;
                total+=1;
            }
        }
        return total;
}

int otsu( int* histo,int total)
{
 double q1=0,q2=0,m1=0,m2=0,w1=0,w2=0;
    double sum1=0,sum2=0,between=0,max=0;
    int pos=0;
    for(int i = 0; i<256;i++)
    {
        sum1+=histo[i];
        sum2+=histo[256-i];
        w1=sum1/total;
        w2=sum2/total;
        q1+=i*histo[i];
        q2+=(256-i)*histo[256-i];
        m1=q1/sum1;
        m2=q2/sum2;
        between = w1*w2*(m1-m2)*(m1-m2);
        if(between>max)
        {
            max=between;
            pos = i;
        }

    }
    return pos;
}

void wholefunction(SDL_Surface* img)
{
    int pos=0;
    int total=0;
    int *histo=calloc(256,sizeof(int));
    total=histogramme(img, histo);
    pos=otsu(histo,total);
    Uint32 pixel;
    Uint8 r,g,b;
    for(int x=0;x<img->w;x++)
    {
        for(int y = 0;y<img->h;y++)
        {
            pixel=getpixel(img,x,y);
            SDL_GetRGB(pixel,img->format,&r,&g,&b);
            if (r>pos)
                putpixel(img,x,y,SDL_MapRGB(img->format,255,255,255));
            else
            {
                putpixel(img,x,y,SDL_MapRGB(img->format,0,0,0));
            }
}
}
}

void expansiondynamique(SDL_Surface* img)
{
    int total=0;
    int *hist=calloc(256,sizeof(int));
    total=histogramme(img, hist);
    Uint32 pixel;
	total+=1;
    Uint8 r,g,b;
    int i = 0;
    int mini=0;
    int maxi=255;
    int n;

    while(i<256)
    {
        if (hist[i]!=0)
        {
            mini = i;
            break;
        }
        i+=1;
    }
    i=255;
    while(i>0)
    {
        if (hist[i]!=0)
        {
            maxi = i;
            break;
        }
        i-=1;

    }
    for(int x = 0;x<img->w;x++)
    {
        for(int y = 0;y<img->h;y++)
        {
            pixel=getpixel(img,x,y);
            SDL_GetRGB(pixel,img->format,&r,&g,&b);
            n=r;
            n=(int)(255*(n-mini)/(maxi-mini));
            putpixel(img,x,y,SDL_MapRGB(img->format,n,n,n));

        }

    }
}

void kernel2(SDL_Surface* img,float arr[3][3])
{
    Uint32 pixel;
    Uint8 r,g,b;
    int accumulator;
    for(int y = 1;y<img->h-1;y++)
    {
        for(int x = 1;x<img->w-1;x++)
        {
            accumulator = 0;
            for(int j = 0;j<2;j++)
            {
                for(int i = 0;i<2;i++)
                {
                    pixel=getpixel(img,x-1+i,y-1+j);
                    SDL_GetRGB(pixel,img->format,&r,&g,&b);
                    accumulator+=r*arr[i][j];

                }
            }
            putpixel(img,x,y,SDL_MapRGB(img->format,accumulator,accumulator,accumulator));
        }
    }

}

void kernel(SDL_Surface* img)
{
	float arr[3][3] = {{0,0,0},{0,1,0},{0,0,0}};
	kernel2(img, arr);
}

void binarize_GUI(char *input)
{
	SDL_Surface * img;
	img = load_image(input);
	expansiondynamique(img);
	wholefunction(img);
	char path[200];
	for(uint j = 0; j < strlen(input); j++)
		path[j] = input[j];
	char format[] = "_bin";
	char buffer[strlen(input) + strlen(format)];
	new_format(path,format,buffer);
	SDL_SaveBMP(img,buffer);
}
SDL_Surface* rotate90(SDL_Surface* img)
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
