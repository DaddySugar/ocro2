
# include <stdio.h>
# include <stdlib.h>
# include <err.h>
# include <math.h>
# include <time.h>
# include "xortools.h"
# include "network.h"


char characters[93] = 
"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQR"
"STUVWXYZ0123456789.,?!_-&#{([|\'\\@)]}+=$%*;/:<>";

/*#######################################################*/
/**
 * Creates a new neural network structure
 * nblayer : the number of layers
 * layers : a table of the number of neurone in each layer
 */
network *newNetwork(unsigned nblayer, unsigned *layers)
{
  network *n = (network *) malloc(sizeof(network));

  //INIT BIAS + DELTA
  float **bias = (float **) malloc(sizeof(float *) * (nblayer - 1));
  float **d = (float **) malloc(sizeof(float *) * (nblayer - 1));
  for (unsigned i = 1; i < nblayer; i++)
  {
	  float *biasinput = (float *) malloc(sizeof(float) * layers[i]);
	  float *deltaneurone = (float *) malloc(sizeof(float) * layers[i]);
	  for (unsigned j = 0; j < layers[i]; j++){
		  biasinput[j] = (float)rand() / RAND_MAX - 1;;
		  deltaneurone[j] = 0;
	  }
	  bias[i - 1] = biasinput;
	  d[i - 1] = deltaneurone;
  }

  //OUTPUT - ACTIVATION VALUE FOR EACH NEURONE
  float **output = (float **) malloc(sizeof(float *) * nblayer);
  for (unsigned i = 0; i < nblayer; i++)
  {
		float *neurone = (float *) malloc(sizeof(float) * layers[i]);
		for (unsigned j = 0; j < layers[i]; j++)
		  neurone[j] = 0;
		output[i] = neurone;
  }


  // INT WEIGHT 
  float ***w = (float ***) malloc(sizeof(float **) * (nblayer - 1));
  for (unsigned i = 0; i < nblayer - 1; i++)
  {
    float **origin = (float **) malloc(sizeof(float **) * layers[i]);
    for (unsigned j = 0; j < layers[i]; j++)
    {
      float *target = (float *) malloc(sizeof(float) * layers[i+1]);
      for (unsigned k = 0; k < layers[i+1]; k++)
        target[k] = (float)rand() / RAND_MAX - 1;;
      origin[j] = target;
    }
    w[i] = origin;
  }

  n->nblayer = nblayer;
  n->layers = layers;
  n->threshold = bias;
  n->out = output;
  n->delta = d;
  n->weight = w;
  return n;
}

/*#################################################*/

/**
 * \brief free all components of a network
 *
 * \param n the neural network
 */
void freeNetwork(network *n)
{
  for (unsigned i = 0; i < n->nblayer - 1; i++)
    free(n->threshold[i]);
  free(n->threshold);
  for (unsigned i = 0; i < n->nblayer; i++)
    free(n->out[i]);
  free(n->out);
  for (unsigned i = 0; i < n->nblayer - 1; i++)
    free(n->delta[i]);
  free(n->delta);
  for (unsigned i = 0; i < n->nblayer - 1; i++)
  {
    for (unsigned j = 0; j < n->layers[i]; j++)
      free(n->weight[i][j]);
    free(n->weight[i]);
  }
  free(n->weight);
  free(n->layers);
  free(n);
}


/*#################################################*/

void generateNetwork()
{
  unsigned *layers = malloc(sizeof(unsigned) * 3);
  layers[0] = 256;
  layers[1] = 80;
  layers[2] = 93;
  network *n = newNetwork(3, layers);

  printf("Generating the network :\n");
  printf("  - Layer size : %d | %d | %d\n", layers[0], layers[1], layers[2]);
  printf("  - Creation of network.save\n");
  saveNetwork("network.save", n);
  printf("DONE\n");

  freeNetwork(n);
  
  network *nn = loadNetwork("network.save");
  printf("%d \n", nn->layers[0]);
	printf("%d \n", nn->layers[1]);
	printf("%d \n", nn->layers[2]);
  
}

/*#################################################*/



network *loadNetwork(char *path)
{

  FILE *file = fopen(path, "r");
	
	int r;
  //nblayer
  unsigned nblayer;
  r = fread(&nblayer, sizeof(unsigned), 1, file);
	if (r == 0)
		return NULL;
  //*layers
  unsigned *layers = malloc(nblayer * sizeof(unsigned));
  r = fread(layers, sizeof(unsigned), nblayer, file);
	if(r == 0)
		return NULL;
	

  network *n = newNetwork(nblayer, layers);

  //**threshold
  for(unsigned k = 0; k < n->nblayer - 1; k++){
    r = fread(n->threshold[k], sizeof(float), n->layers[k + 1], file);
		if (r == 0)
			return NULL;
	}

  //***weight
  for(unsigned k = 0; k < n->nblayer - 1; k++)
    for(unsigned l = 0; l < n->layers[k]; l++){
      r = fread(n->weight[k][l], sizeof(float), n->layers[k + 1], file);
			if (r == 0)
				return NULL;
		}
  fclose(file);

  return n;
}


void saveNetwork(char *path, network *n)
{
  FILE *file = fopen(path, "w");
  if (file == NULL)
    errx(1, "error during fopen");

  //nblayer
  fwrite(&n->nblayer, sizeof(unsigned), 1, file);
  //fputc('\n', file);

  //*layers
  fwrite(n->layers, sizeof(unsigned), n->nblayer, file);

  //**threshold
  for(unsigned k = 1; k < n->nblayer; k++)
    fwrite(n->threshold[k - 1], sizeof(float), n->layers[k], file);

  //***weight
  for(unsigned k = 0; k < n->nblayer - 1; k++)
    for(unsigned l = 0; l < n->layers[k]; l++)
      fwrite(n->weight[k][l], sizeof(float), n->layers[k + 1], file);

  fclose(file);
}
/*#################################################*/


/**
 * \brief the activation function of a neural network
 *
 * \param n the neural network
 * \param inputs values for the input layer
 */
void feedForward(network *n, float *inputs)
{
  for (unsigned i = 0; i < n->layers[0]; i++)
    n->out[0][i] = inputs[i];

  for (unsigned i = 1; i < n->nblayer - 1; i++)
    for (unsigned j = 0; j < n->layers[i]; j++)
    {
      n->out[i][j] = n->threshold[i - 1][j];
      for (unsigned k = 0; k < n->layers[i - 1]; k++)
        n->out[i][j] += n->weight[i - 1][k][j] * n->out[i - 1][k];
      n->out[i][j] = sigmoid(n->out[i][j]);
    }
  unsigned last = n->nblayer - 1;
  for (unsigned j = 0; j < n->layers[last]; j++)
  {
    n->out[last][j] = n->threshold[last - 1][j];
    for (unsigned k = 0; k < n->layers[last - 1]; k++)
      n->out[last][j] += n->weight[last - 1][k][j] * n->out[last - 1][k];
  }
  softmax(n->layers[last], n->out[last]);
}

void backPropagation(network *n, float *outputs)
{
  unsigned last = n->nblayer - 1;
  for (unsigned i = 0; i < n->layers[last]; i++)
  {
    float out = n->out[last][i];
    n->delta[last - 1][i] = out * (1 - out) * (out - outputs[i]);
  }

  for (int i = last - 1; i > 0; i--)
    for (unsigned j = 0; j < n->layers[i]; j++)
    {
      n->delta[i - 1][j] = 0;
      for (unsigned k = 0; k < n->layers[i + 1]; k++)
        n->delta[i - 1][j] += n->weight[i][j][k] * n->delta[i][k];
      n->delta[i - 1][j] *= n->out[i][j] * (1 - n->out[i][j]);
    }
}


void update(network *n, float speed)
{
  for (unsigned i = 0; i < n->nblayer - 1; i++)
  {
    for (unsigned j = 0; j < n->layers[i]; j++)
      for (unsigned k = 0; k < n->layers[i + 1]; k++)
        n->weight[i][j][k] -= speed * n->out[i][j] * n->delta[i][k];

    for (unsigned j = 0; j < n->layers[i + 1]; j++)
      n->threshold[i][j] -= speed * n->delta[i][j];
  }
}

float evaluate(network *n, float **samples, float **results, size_t nbSample)
{
	//printf("evaluating ... \n");
  float error = 0;
  unsigned last = n->nblayer - 1;
  //printf("%d ... \n", (int)n->nblayer);
  for (size_t i = 0; i < nbSample; i++)
  {
	  //printf("%d -- ... \n", (int)i);
    float dist = 0;
    feedForward(n, samples[i]);
	//printf("%d -- ... \n", (int)i);
    for (unsigned j = 0; j < n->layers[last]; j++)
      dist += pow(n->out[last][j] - results[i][j], 2);
    error += sqrt(dist);
  }
  return error / (nbSample * 2);
}


/**
 * \brief optical character recognition
 *
 * \param img a picture of a character (16x16)
 * \param n the neural network
 */
char ocr(bitmap *img, network *n)
{
  float *input = malloc(sizeof(float) * img->width * img->height);
  //draw(img);
  for (unsigned i = 0; i < img->width * img->height; i++) 
	  feedForward(n, input);

  int best = 0;
  for (unsigned i = 1; i < n->layers[n->nblayer - 1]; i++)
    if (n->out[n->nblayer - 1][best] < n->out[n->nblayer - 1][i])
      best = i;
  

  free(input);
  return getCharFromIndex(best);
}

/**
 * \brief give the index corresponding with the character c
 *
 * \param c the character
 */
int getCharIndex(char c)
{
  for (size_t i = 0; i < sizeof(characters); i++)
    if (characters[i] == c)
      return i;
  errx(1, "The character is not valid !");
}

/**
 * \brief give the character corresponding with the index i
 *
 * \param i the index
 */
char getCharFromIndex(int i)
{
  return characters[i];
}


