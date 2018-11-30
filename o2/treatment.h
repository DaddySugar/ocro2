#ifndef treatment
#define treatment

SDL_Surface* load_image(char *path) ;
void display_image(SDL_Surface *image);
Uint32 getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void greyscale(SDL_Surface* img);
//void makeitblackandwhite(SDL_Surface *surface, int maxx, int maxy);
void wholefunction(SDL_Surface *img);
int otsu( int* histo,int total);
int histogramme(SDL_Surface *img);
void expansiondynamique(SDL_Surface* img);
void kernel2(SDL_Surface* img,float arr[3][3]);
void kernel(SDL_Surface* img);
#endif
