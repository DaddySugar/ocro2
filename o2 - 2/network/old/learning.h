# ifndef LEARNING_H_
# define LEARNING_H_
# include "../bitmap.h"
# include "network.h"
# include "../queue.h"
# include <SDL2/SDL_image.h>


//void learning(char learnFiles[], SDL_Surface *pathImg, size_t nbFile);
void learning();
void learningChar();
int createSamples(queue *,float** samples);
float **createResults(char[], int);
void freeSamples(float **, int);
queue* getFilesFromDir(queue*);
# endif
