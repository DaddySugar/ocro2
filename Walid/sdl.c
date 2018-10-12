#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "sdl.h"
#include "pixel_operations.h"
#include "pixel_operations.c"

void wait_for_keypressed(void) {
  SDL_Event             event;
  // Infinite loop, waiting for event
  for (;;) {
    // Take an event
    SDL_PollEvent( &event );
    // Switch on event type
    switch (event.type) {
    // Someone pressed a key -> leave the function
    case SDL_KEYDOWN: return;
    default: break;
    }
  // Loop until we got the expected event
  }
}

void init_sdl(void) {
  // Init only the video part
  if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
    // If it fails, die with an error message
    errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
  }
  // We don't really need a function for that ...
}

SDL_Surface* load_image(char *path) {
  SDL_Surface          *img;
  // Load an image using SDL_image with format detection
  img = IMG_Load(path);
  if (!img)
    // If it fails, die with an error message
    errx(3, "can't load %s: %s", path, IMG_GetError());
  return img;
}



SDL_Surface* display_image(SDL_Surface *img) {
  SDL_Surface          *screen;
  // Set the window to the same size as the image
  screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
  if ( screen == NULL ) {
    // error management
    errx(1, "Couldn't set %dx%d video mode: %s\n",
         img->w, img->h, SDL_GetError());
  }
 
  /* Blit onto the screen surface */
  if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());
 
  // Update the screen
  SDL_UpdateRect(screen, 0, 0, img->w, img->h);
 
  // wait for a key
  wait_for_keypressed();
 
  // return the screen for further uses
  return screen;
}

/*int main (int argc, char *argv[])
{
	char *name = argv[argc-2];
	SDL_Surface *img = load_image(name);//"couleurs.bmp"); */

void grey_scale(SDL_Surface *img){
	Uint8 r = 0;
	Uint8 g = 0;
	Uint8 b = 0;
	int x = 0;
	int y = 0;
	Uint32 pixel;
	while (x != img->w)
	{
		while (y != img->h)
		{
			pixel = getpixel(img, x, y);
			SDL_GetRGB(pixel, img->format, &r, &g, &b);
			if ((r + g + b)/3 >= 127)
			{
			r = 255;
			g = 255;
			b = 255;
			pixel = SDL_MapRGB(img->format, r, g, b);			// La double boucle est 100% correcte (certain)
			putpixel(img, x, y, pixel);
			}
			else
			{
			r = 0;
			g = 0;
			b = 0;
			pixel = SDL_MapRGB(img->format, r, g, b);			// La double boucle est 100% correcte (certain)
			putpixel(img, x, y, pixel);
			}
			y++;	
		}
		y = 0;
		x++;
	}
	display_image(img);
}
/*
	if(strcmp(argv[argc-1], "1") == 0){
	//	Line(img);
	}if(strcmp(argv[argc-1], "2") == 0){
	//	display_image(img);
	}if(strcmp(argv[argc-1], "3") == 0){
		dilate_pixel(img);
	}else{ 
		printf("wrong or missing arg. Use 1, 2 or 3.");
	}
	return 0;
}*/


void Line(SDL_Surface *surf)
{
  int Xmin= 0;
  int Ymin= 0;
  int larg = 0;
  int haut = 0;
  int booleen = 0;
  int booleen2 = 0;
  Uint8 r = 0;
  Uint8 g = 0;
  Uint8 b = 0;
  Uint32 pixel;
  int test2nd = 0;
  SDL_LockSurface(surf);
  for(int y=0;y<surf->h;y++)
  {
    for(int x=0;x<surf->w;x++)
    {
      pixel = getpixel(surf, x, y);
      SDL_GetRGB(pixel, surf->format, &r, &g, &b);
      if(r==0 && g==0 && b==0) /* Si c'est noir */
      {
        booleen  = 1;
        booleen2 = 0;
      }
    }
    if(booleen == 0) /*check si c'est une ligne blanche, sinon ça part*/
    {
      if(booleen2 == 1)
      {
        //éviter les doubles lignes blanches: si b2 = 1 alors, on a pas eu un seul pixel noir depuis le dernier envoi
        haut = 0;
        Ymin = y + 1;
      }
      if(booleen2 == 0)
      {
	test2nd++;
        printf(" test de la n-ième ligne ? %d \n", test2nd);
        if(test2nd > 0 ){
                printf("%dieme ligne \n", test2nd);
        	//neurone(surf, Xmin, Ymin, haut, larg); //test a delete ?
       		Char(surf, Xmin, Ymin, haut, larg);
        }
	Ymin = y + 1;
        haut = 0;
        booleen2 = 1;
      }
    }
        //else (tant que il y a du noir)
    haut = haut + 1;
    booleen = 0;
  }
}

void SavePartScreen(const char* nom, SDL_Surface *ecran, int Xmin, int Ymin, int larg, int haut){
  SDL_Surface *image = NULL;
  SDL_Rect rect1, rect2;
  image = SDL_CreateRGBSurface (SDL_HWSURFACE, larg, haut, 16, 0, 0, 0, 0);
  if (image == NULL){ printf("\n FAIL CREATERGB");}
//  SDL_FillRect(image, NULL, SDL_MapRGB(ecran->format, 250, 250, 250));
  rect1.x = Xmin, rect1.y = Ymin, rect1.w = larg, rect1.h = haut;
  rect2.x = 0, rect2.y = 0, rect2.w = larg, rect2.h = haut;
  SDL_UnlockSurface(image);
  SDL_UnlockSurface(ecran);
  printf("\n %d \n", SDL_BlitSurface(ecran, &rect1 , image,&rect2));
  printf("SDL blit surf	ce: %s\n", SDL_GetError());

 SDL_SaveBMP(image, nom);
 display_image(image);
  SDL_FreeSurface(image);
}

void Char(SDL_Surface *surf, int Xmin, int Ymin, int haut, int larg){
 int black =  0;
 int d_white = 0;
 Uint8 r = 0;
 Uint8 g = 0;
 Uint8 b = 0;
 Uint32 pixel;
 int test2nd = 0;
 for(int x = 0; x < surf->w; x++)
  {
    for(int y= 0; y < haut; y++)
    {
      pixel = getpixel(surf, x, y + Ymin);
      SDL_GetRGB(pixel, surf->format, &r, &g, &b);
      if(r==0 && g==0 && b==0) /* Si c'est noir */
      {
        black  = 1;
        d_white  = 0;
      }
    }
    if(black == 0) /*check si c'est une colonne blanche, sinon ça part*/
    {
      if(d_white == 1)
      {
        larg = 0;
        Xmin = x + 1;
      }
      if(d_white == 0)
      {
        test2nd++;
	printf(" test du n°ieme char ? %d \n", test2nd);
        if(test2nd > 0){
           	printf("envoi neurone() \n");
	 	neurone(surf, Xmin, Ymin, haut, larg);
        }
        Xmin = x + 1;
        larg = 0;
        d_white = 1;
      }
    }
    larg = larg + 1;
    black = 0;
  }
}

void neurone(SDL_Surface *surf, int Xmin, int Ymin, int haut, int larg){
  SDL_Rect OneChar;
  OneChar.x = Xmin;
  OneChar.y = Ymin;
  OneChar.w = larg;
  OneChar.h = haut;
  Uint8 r = 0;
  Uint8 g = 0;
  Uint8 b = 0;
  int hauteur_constante=16;
  int largeur_constante=16;
  int tab[hauteur_constante][largeur_constante];
  for(int i = 0; i < hauteur_constante; i++){
	for(int j = 0; j < largeur_constante; j++){
		
                //pixel = getpixel(surf, x, y + Ymin);
   		if(i>=haut || j>=larg)
                {
                    tab[j][i]=0;
                }
                else
                {
                    SDL_GetRGB( getpixel(surf, j+Xmin, i + Ymin), surf->format, &r, &g, &b);
   		    if(r==0 && g==0 && b==0) /* Si c'est noir */
		    {
		            tab[j][i] = 1;
		    }
		    else{
			    tab[j][i] = 0;
		    }
                }
		printf("%d ",tab[j][i]);
	}
	printf("\n");
 }
//  SDL_Surface *disp = SDL_CreateRGBSurface(0, larg-Xmin, haut-Ymin, 32, 0, 0, 0, 0);
  SDL_Rect dstrect;
	dstrect.x = 0;
	dstrect.y = 0;
  printf("x %d, y %d, larg %d, haut %d \n ", Xmin, Ymin, larg, haut);
  printf("surf.x %d, surf.y %d \n ", surf->h, surf->w);
//  char *name = "test.bmp";
 SavePartScreen("THISISOURCHARACTER.bmp", surf, Xmin, Ymin, larg, haut);
//  printf("%d", SDL_BlitSurface(surf, NULL/*&OneChar*/, disp, &dstrect));
//  SDL_SaveBMP(&disp, &name);
//  display_image(&disp);
//  SDL_SaveBMP(&disp, "test.bmp");
//  SDL_FreeSurface(&disp);
	
}
void dilate_pixel(SDL_Surface *surf){
  Uint8 r = 0;
  Uint8 g = 0;
  Uint8 b = 0;
  SDL_Rect blur;
  blur.x = 0;
  blur.y = 0;
//  SavePartScreen("blurred_img.bmp", surf, 0, 0, surf->w, surf->h);

  for(int y = 0; y < surf->h; y++)
  {
	for(int x= 0; x < surf->w; x++)
	{
		SDL_GetRGB( getpixel(surf, x, y), surf->format, &r, &g, &b);
		if(r==0 && g==0 && b==0) /* Si c'est noir */
		{	
			printf("   x = %d \n", x);
			//SDL_Rect *blur;
			if(x == 0){ 
				blur.x = x;
			}
			else if(x > surf->w - 10){ //si on arrive à la fin
				blur.x = surf->w - 10;
				printf(" \n %d > %d - 10", x, surf->w);
				x = surf->w; //éviter des boucles en trop
			}
			else{ blur.x = x-10; }
			blur.w = 10;
			x = x+1; //éviter de passer sur les mêmes pixels noirs créés
			if(y == 0){
                                blur.y = y;
                        }
                        else if(y > surf->h - 10){
                                blur.y = surf->h - 10;
                                y = surf->h;
                        }
			else{ blur.y = y - 10;}
			blur.h = 10;
			y = y + 0; //éviter de passer sur les mêmes pixels noirs créés
			SDL_Rect *blurred = &blur; //Init(&myRect, 5, 5, 50, 20);
//			delete myRect; 
			SDL_FillRect(surf, blurred, 0);
		}
	}
  }
  SavePartScreen("blurred_img.bmp", surf, 0, 0, surf->w, surf->h);

} /*
SDL_Rect *Init(int XPos, int YPos, int Width, int Height)
{
	SDL_Rect *Rect = new SDL_Rect;
	Rect->h = Height;
	Rect->w = Width;
	Rect->x = XPos;
	Rect->y = YPos;

	return Rect;
} */
