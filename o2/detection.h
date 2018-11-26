#ifndef DETECTION_H
#define DETECTION_H

# include "queue.h"

void Line_Detection(SDL_Surface* img,queue *q);
void Height_Detection(SDL_Surface* img, int start, int finish, queue* q);
void Horizontal_Line(SDL_Surface* img, int w, int start, int end);
void Vertical_Line(SDL_Surface* img, int x, int start, int end);
SDL_Surface* sdlnewchar(SDL_Surface* img,int minw,int maxw,int minh, int maxh);
void savechar(SDL_Surface*, int x,int y,int w, int h, queue* q);
void remplissage(SDL_Surface *image, int startline, int endline, int startcolum, int endcolum);
#endif
