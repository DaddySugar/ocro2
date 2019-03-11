#ifndef treatmentGUI_H
#define treatmentGUI_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void grayscale_GUI(char* input);
void new_format(char *init_path, char *format, char[]);
void binarize_GUI(char *input);
SDL_Surface* rotate90_l(SDL_Surface* img);
SDL_Surface* rotate90_r(SDL_Surface* img);

#endif
