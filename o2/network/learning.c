/**
 * \file learning.c
 * \brief All functions for learn and use a neural network
 * \author amsall_f
 * \date 09/17/2016
 */
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

/**
 * \brief suffle the samples and results table
 *
 * \param samples the table of samples
 * \param result the table of results
 * \param length the length of both table
 */
 
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

/**
 * \brief randomize the weight and thresholds of a network
 *
 * \param n the network
 * \param r the ratio of the randomization
 */
 
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

/**
 * \brief entrain a neural network with a batch of samples
 *
 * \param n the neural network
 * \param samples the inputs of samples
 * \param results the outputs of samples
 * \param nbSample the number of samples
 */
 
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

/**
 * \brief learn to the network "network.save"
 *
 * \param learnFiles the table of path to learn files
 * \param nbFile the number of file
 */
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
	char pathImg[] = "res/learnWalid.bmp";
    SDL_Surface* sdlimg = SDL_LoadBMP(pathImg);
    queue * segmentedImg = newQueue();
    Line_Detection(sdlimg, segmentedImg, &length);
	
// TEST IMAGE : 
    /*
    while (segmentedImg->length > 0)
    {
        queue *line = deQueue(segmentedImg);
    	while (line->length > 0)
				{
		bitmap* letter = loadBmp(deQueue(line));
				
		//bitmap *letter = loadBmp(letter); 	
			
                    resize(letter);
		    autoContrast(letter);
		    binarize(letter);
		    draw(letter);
		    printf("\n %d -- \n", segmentedImg->length);
		printf("\n %d -- \n", line->length);
					
					
                        freeBitmap(letter);
					
					
				}
			}	


*/ // END TEST IMAGE

	float **inputs = malloc(sizeof(float *) * length);
	int nbEnqueue = createSamples(segmentedImg, inputs);
	(void)nbEnqueue;

	//char text[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	//char text[] = "THEWALIDYOUNEED";
	char text[] = "WALID";
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

/**
 * \brief Create the results of samples
 *
 * \param text the expected text
 * \param nbsample the length of the text
 * \param nbOutput the number of possibile outputs
 */
float **createResults(char text[], int nbSample)
{
  size_t nbOutput = 93;
  float **results = malloc(sizeof(float *) * nbSample);
  for (int i = 0; i < nbSample; i++)
  {
    if (text[i] == 0)
      errx(1, "The expected output is not valid");

    results[i] = malloc(sizeof(float) * nbOutput);
    for (size_t j = 0; j < nbOutput; j++)
      results[i][j] = 0;
  //printf("Created resultas for %c\n", text[i]);
    results[i][getCharIndex(text[i])] = 1;
	printSample(results); 
  }
  return results;
}

/*#############################################################*/

/**
 * \brief free all components of a sample
 *
 * \param samples the inputs or outputs of a sample
 * \param nbSample the number of character in the sample
 */
void freeSamples(float **samples, int nbSample)
{
  for (int i = 0; i < nbSample; i++)
    free(samples[i]);
  free(samples);
}
