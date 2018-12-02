# include <stdio.h>
# include <SDL2/SDL.h>
# include <stdlib.h>
# include <time.h>
# include <math.h>
# include <err.h>
# include "../bitmap.h"
# include "../detection.h"
# include "network.h"
# include "../queue.h"
# include "learning.h"
#include <dirent.h> 
#include <stdio.h> 

/*
void getFileRes(char file[],char res[]){
	size_t i = 0; 
	while( i < strlen(file) && 
		(file[i] != '.' || file[i] != 'b')){
		res[i] = file[i]; 
		i++;
		}
	printf("--  %s\n",res);
}

queue* getFilesFromDir(queue* res) {
	DIR *d;
	queue* samples = newQueue(); 
	struct dirent *dir;
	d = opendir("./res/Alphabet");
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			enQueue(samples,dir->d_name);
			char ttt[strlen(dir->d_name)];
			getFileRes(dir->d_name, ttt);
			enQueue(res,ttt);
			printf("%s\n", dir->d_name);
		}
		closedir(d);
	}
	
	while(samples->length > 0){
		char *s = deQueue(samples);
		printf("%s\n",s);
	}
	
	return samples;
}*/

 /*#############################################################*/
 
void shuffleSample(float **samples, float **results, unsigned length)
{
	for (unsigned i = length - 1; i > 0; i--)
	{
		int r = rand() % i;
		float *swap = samples[r];
		samples[r] = samples[i];
		samples[i] = swap;
		swap = results[r];
		results[r] = results[i];
		results[i] = swap;
	}
}

 /*#############################################################*/
void randomize(network *n, float r)
{
  for (unsigned i = 0; i < n->nblayer - 1; i++)
  {
    for (unsigned j = 0; j < n->layers[i + 1]; j++)
      n->threshold[i][j] += r * ((float) rand() / (float) RAND_MAX * 2 - 1);
    for (unsigned j = 0; j < n->layers[i]; j++)  
      for (unsigned k = 0; k < n->layers[i+1]; k++)
        n->weight[i][j][k] += r * ((float) rand() / (float) RAND_MAX * 2 - 1);
  }
}

 /*#############################################################*/
 
float learn(network *n, float **samples, float **results, unsigned nbSample,
    float speed, size_t sizeBatch)
{
  shuffleSample(samples, results, nbSample);
  sizeBatch = sizeBatch < nbSample ? sizeBatch : nbSample;
  for (int i = 0; i < 2000; i++)
    for (size_t j = 0; j < sizeBatch; j++)
    {
      feedForward(n, samples[j]);
      backPropagation(n, results[j]);
      update(n, speed);
    }
  return evaluate(n, samples, results, nbSample);
}

/*
size_t getlen(queue *q){
	
	size_t res = 0;
	for(int i = 0; i < q->length; i++)
		res + 
	}
	return res; 
	
}*/


 /*#############################################################*/
 
 void learning(char *learnFiles[], size_t nbFile)
{
  network *n = loadNetwork("network.save");
  size_t length = 0;
  int *nbCharacter = malloc(sizeof(int));
  queue *segmented = newQueue();
  for (size_t j = 0; j < nbFile; j++)
  {
    char pathImg[100];
    size_t i = 0;

    FILE *fp = fopen(learnFiles[j] ,"r");
    int r;
		do
    {
      r = fread(pathImg + i, 1, 1, fp);
      i++;
    } while (r !=0 && pathImg[i-1] != '\n');
    pathImg[i-1] = 0;
    fclose(fp);
   
	SDL_Surface* sdlimg = SDL_LoadBMP(pathImg);
    queue * segmentedImg = newQueue();
    Line_Detection(sdlimg, segmentedImg, nbCharacter);
   
    enQueue(segmented, segmentedImg);
    length += *nbCharacter;
  }
  
  free(nbCharacter);
  float **inputs = malloc(sizeof(float *) * length);
  int nbEnqueue = 0;
  for (size_t j = 0; j < nbFile; j++)
    nbEnqueue += createSamples((queue*) deQueue(segmented), inputs + nbEnqueue);
  free(segmented);

  char text[length + 1];
  size_t i = 0;
	int r;
  for (size_t j = 0; j < nbFile; j++)
  {
    FILE *fp = fopen(learnFiles[j] ,"r");
    text[i] = ' ';
    while (text[i] != '\n'){
      r = fread(text + i, 1, 1, fp);
			if (r == 0)
				return;
		}
    while (fread(text + i, 1, 1, fp))
      if (text[i] != '\n' && text[i] != ' ')
        i++;
    fclose(fp);
  }
  text[i] = 0;
  float **outputs = createResults(text, length);

  clock_t chrono = clock();
  float error = evaluate(n, inputs, outputs, length);
  float bestError = error;
  float goal = .001;
  printf("LEARNING :\n");
  printf("  - STATUS : %d%%\n", (int) ((1 - error) / (1 - goal) * 100));
  while (error > goal)
  {
    error = learn(n, inputs, outputs, length, .3, 50);
    error = error < goal ? goal : error;
    printf("  - STATUS : %d%% ", (int) ((1 - error) / (1 - goal) * 100));
    if (error < bestError)
    {
      bestError = error;
      printf("(Update of network.save)");
      saveNetwork("network.save", n);
    }
    printf("\n");
  }
  printf("  - Time : %.6f (seconds)\n", (clock() - chrono) / 1000000.0F);

  printf("DONE\n");

  freeSamples(inputs, length);
  freeSamples(outputs, length);
  freeNetwork(n);
}


/*#############################################################*/

void learningChar()
{
    network *n = loadNetwork("network.save");
	int length = 0;
	char pathImg[] = "res/A.bmp";
	
    SDL_Surface* sdlimg = SDL_LoadBMP(pathImg);
    queue * segmentedImg = newQueue();
    Line_Detection(sdlimg, segmentedImg, &length);

	float **inputs = malloc(sizeof(float *) * length);
	int nbEnqueue = createSamples(segmentedImg, inputs);
	(void)nbEnqueue;

	//char text[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	//char text[] = "THEWALIDYOUNEED";
	char text[] = "A";
	float **outputs = createResults(text, length);
	float error = evaluate(n, inputs, outputs, length);
	
	float bestError = error;
	float goal = .0001;
	
	printf("  - STATUS : %d%%\n", (int) ((1 - error) / (1 - goal) * 100));
	
	while (error > goal)
	{
		error = learn(n, inputs, outputs, length, .3, 50);
		error = error < goal ? goal : error;
		printf("  - STATUS : %d%%  \n", (int) ((1 - error) / (1 - goal) * 100));
		printf("  - Error : %f -|- %f \n ", error, bestError);
		if (error < bestError)
		{
			bestError = error;
			printf("(Update of network.save)");
			saveNetwork("network.save", n);
			printf("\n");
		}
	}
	
	printf("DONE\n");
	freeSamples(inputs, length);
	freeSamples(outputs, length);
	freeNetwork(n);
	}
	/*
	void learningChar()
{
    network *n = loadNetwork("network.save");
	int length = 0;
	int length2 = 0;
	
	char pathImg[] = "res/A.bmp";
	char pathImg2[] = "res/B.bmp";
	
    SDL_Surface* sdlimg = SDL_LoadBMP(pathImg);
	SDL_Surface* sdlimg2 = SDL_LoadBMP(pathImg2);
	
    queue * segmentedImg = newQueue();
	queue * segmentedImg2 = newQueue();
	
    Line_Detection(sdlimg, segmentedImg, &length);
	Line_Detection(sdlimg2, segmentedImg2, &length2);

	length += length2;
	
	float **inputs = malloc(sizeof(float *) * length);
	int nbEnqueue = 0;
		
	nbEnqueue = createSamples(segmentedImg, inputs);
	nbEnqueue = createSamples(segmentedImg2, inputs+nbEnqueue);
	(void)nbEnqueue;

	//char text[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	//char text[] = "THEWALIDYOUNEED";
	char text[] = "AW";
	float **outputs = createResults(text, length);
	float error = evaluate(n, inputs, outputs, length);
	
	float bestError = error;
	float goal = .0001;
	
	printf("  - STATUS : %d%%\n", (int) ((1 - error) / (1 - goal) * 100));
	
	while (error > goal)
	{
		error = learn(n, inputs, outputs, length, .3, 50);
		error = error < goal ? goal : error;
		printf("  - STATUS : %d%%  \n", (int) ((1 - error) / (1 - goal) * 100));
		printf("  - Error : %f -|- %f \n ", error, bestError);
		if (error < bestError)
		{
			bestError = error;
			printf("(Update of network.save)");
			saveNetwork("network.save", n);
			printf("\n");
		}
	}
	
	printf("DONE\n");
	freeSamples(inputs, length);
	freeSamples(outputs, length);
	freeNetwork(n);
	}*/

/*#############################################################*/

void printSample(float** samples){
		for (int i = 0; i < 256; i++){
			  if((*samples)[i] == 0)printf("#");
			  else printf(" ");
			  if(i%16 == 0) printf("\n");
		}
}

/*#############################################################*/

int createSamples(queue *line, float** samples)
{  
	float **origin = samples;
		while (line->length > 0)
		{
		  queue *word = deQueue(line);
		  while (word->length > 0)
		  {
			bitmap* letter = loadBmp(deQueue(word));
			resize(letter);
			autoContrast(letter);
			binarize(letter);
			//draw(letter);
			*samples = malloc(sizeof(float) * 256);
			for (int i = 0; i < 256; i++){
			  (*samples)[i] = letter->content[i].r == 255 ? 1 : 0;
			  //printf("Sample i = %d -- Value = %f.0\n", i,(*samples)[i]);
			}
			//printSample(samples);
			samples++;
		  freeBitmap(letter);
		  }
		  free(word);
		}
		free(line);
	return samples - origin;
}

/*#############################################################*/


float **createResults(char text[], int nbSample)
{
  size_t nbOutput = 93;
  float **results = malloc(sizeof(float *) * nbSample);
  for (int i = 0; i < nbSample; i++)
  {
    if (text[i] == 0)
      errx(1, "learning.c::createResults: \
	The expected results is not right!");

    results[i] = malloc(sizeof(float) * nbOutput);
    for (size_t j = 0; j < nbOutput; j++)
      results[i][j] = 0;
  //printf("Created resultas for %c\n", text[i]);
	//printSample(results); 
    results[i][getCharIndex(text[i])] = 1;
  }
  return results;
}

/*#############################################################*/

void freeSamples(float **samples, int nbSample)
{
  for (int i = 0; i < nbSample; i++)
    free(samples[i]);
  free(samples);
}
