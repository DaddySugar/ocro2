#ifndef DETECTION_H
#define DETECTION_H



void Line_Detection(SDL_Surface* img);
void Height_Detection(SDL_Surface* img, int start, int finish);
void Horizontal_Line(SDL_Surface* img, int w, int start, int end);
void Vertical_Line(SDL_Surface* img, int x, int start, int end);
SDL_Surface* sdlnewchar(SDL_Surface* img,int minw,int maxw,int minh, int maxh);
void savechar(SDL_Surface* img,int x,int y,int w, int h);
void remplissage(SDL_Surface *image, int startline, int endline, int startcolum, int endcolum);
#endif
