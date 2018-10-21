#ifndef treatment
#define treatment

SDL_Surface* load_image(char *path) ;
void display_image(SDL_Surface *image);
Uint32 getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void greyscale(SDL_Surface* img);
void makeitblackandwhite(SDL_Surface *surface, int maxx, int maxy);
#endif
