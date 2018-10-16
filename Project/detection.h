#ifndef DETECTION_H
#define DETECTION_H

SDL_Surface* drawLine(SDL_Surface *img, int start_x, int end_x, int y);
SDL_Surface* drawColumn(SDL_Surface *img, int start_y, int end_y, int x);
int Line_Detection(SDL_Surface* img); 


#endif
