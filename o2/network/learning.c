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
size_t getlen(queue *q){
	
	size_t res = 0;
	for(int i = 0; i < q->length; i++){
		
		queue *qq = deQueue(q);
		for(int j = 0; j < qq->length; j++)
			res++; 
		free(qq);
		
	}
	return res; 
	
}

/**
 * \brief learn to the network "network.save"
 *
 * \param learnFiles the table of path to learn files
 * \param nbFile the number of file
 */
 
void learning()
{
	
  network *n = loadNetwork("network.save");
  size_t length = 0;
  size_t *nbCharacter = malloc(sizeof(size_t));
  size_t *useless = malloc(sizeof(size_t));
  queue *segmented = newQueue();
  
   char pathImg[] = "res/learn1.bmp";
   printf("Path %s\n",pathImg);
   
    
	SDL_Surface* sdlimg = SDL_LoadBMP(pathImg);
    bitmap *img = loadBmp(sdlimg);
    queue * segmentedImg = newQueue();
    Line_Detection(sdlimg, segmentedImg);
    enQueue(segmented, segmentedImg);
    freeBitmap(img);
    length = getlen(segmentedImg);
  
  //Problem after here
  
  free(useless);
  free(nbCharacter);
  float **inputs = malloc(sizeof(float *) * length);
  int nbEnqueue = 0;
  
 
 


   printf("Path problem ? Create simple\n\n");
    nbEnqueue = createSamples((queue*) deQueue(segmentedImg), inputs + nbEnqueue);
	printf("jaajajja %d", nbEnqueue);
	
  
  
  free(segmented);

  char text[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
   printf("Path %s\n",text);
  
  //size_t i = 0;

  float **outputs = createResults(text, length);
printf("Strat procisdure 5\n");
  //clock_t chrono = clock();
  float error = evaluate(n, inputs, outputs, length);
  printf("Strat procisdure 6 \n");
  float bestError = error;
  float goal = .001;
  printf("LEARNING :\n");
  printf("Strat procisdure 4 \n");
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
  //printf("  - Time : %.6f (seconds)\n", (clock() - chrono) / 1000000.0F);

  printf("DONE\n");

  freeSamples(inputs, length);
  freeSamples(outputs, length);
  freeNetwork(n);
}



int createSamples(queue *q, float **samples)
{  float **origin = samples;
	printf("Create Sample : %d\n",q->length);
	while (q->length > 0)
			{
				queue *line = deQueue(q);
				printf("Create Sample : %d\n",line->length);
				
				while (line->length > 0)
				{
					bitmap* letter = loadBmp(deQueue(line));
					
					
					//bitmap *letter = loadBmp(letter); 	
					
					resize(letter);
					autoContrast(letter);
					binarize(letter);
					draw(letter);
					printf("\n %d -- \n", q->length);
					printf("\n %d -- \n", line->length);
					
					freeBitmap(letter);
					for (int i = 0; i < 256; i++)
						  (*samples)[i] = letter->content[i].r == 255 ? 1 : 0;
					samples++;
					
					
				}
			}	
			free(q);

  return samples - origin;
}

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
    results[i][getCharIndex(text[i])] = 1;
  }
  return results;
}

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
