#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <err.h>
# include "xortools.h"
#include "../matrix.h"


/*#############################################################*/
/*##############--       Network        --#####################*/
/*#############################################################*/

size_t inputIN;
size_t hiddenNL;
size_t outputIN;

double *biasHidden;
double *biasOutput;
double **weightIN;
double **weightHIDE;


/*#############################################################*/
 
 
double* makeList(size_t size)
{
	double *list = (double *)malloc(sizeof(double) * size);
	if (list == NULL){
		errx(1,"Could not initialize a list\n");
		exit(EXIT_FAILURE);
		}
	return list;
}

/*#############################################################*/
/*##############--    Create New Network        --#############*/
/*#############################################################*/


void newNetwork(size_t inputNodes, size_t hiddenNodes, size_t outputNodes)
{
	srand(time(NULL)); 

	inputIN = inputNodes;
	hiddenNL = hiddenNodes;
	outputIN = outputNodes;

	// INIT biasHidden
	biasHidden = makeList(hiddenNodes);
	for (size_t i = 0; i < hiddenNodes; i++)
		biasHidden[i] = getRandom();
	

	// INIT biasOutput
	biasOutput = makeList(outputNodes);
	for (size_t i = 0; i < outputNodes; i++)
		biasOutput[i] = getRandom();
	

	// INIT weightIN 
	weightIN = CreateDoubleMatrix(inputNodes, hiddenNodes);
	for (size_t j = 0; j < inputNodes; j++)
	{
		for (size_t k = 0; k < hiddenNodes; k++)
			weightIN[j][k] = getRandom();
	}

	// INIT weightHIDE,
	weightHIDE = CreateDoubleMatrix(hiddenNodes, outputNodes);
	for (size_t j = 0; j < hiddenNodes; j++)
	{
		for (size_t k = 0; k < outputNodes; k++)

			weightHIDE[j][k] = (rand() / (double)RAND_MAX) * 2 - 1;
	}
}

/*#############################################################*/
/*##############--   Save and Load Network      --#############*/
/*#############################################################*/


void saveNetwork(char path[])
{
	FILE *f = fopen(path, "w");
	fprintf(f, "# NEURAL NETWORK\n\n");
	fprintf(f, "# Structure\n%zu\n%zu\n%zu\n\n",inputIN,
										hiddenNL,outputIN);

	fprintf(f, "# biasHidden\n");
	for (size_t i = 0; i < hiddenNL; i++)
		fprintf(f, "%f\n", biasHidden[i]);

	fprintf(f, "\n# biasOutput\n");
	for (size_t j = 0; j < outputIN; j++)
		fprintf(f, "%f\n", biasOutput[j]);
	

	fprintf(f, "\n# weightIN\n");
	for (size_t i = 0; i < inputIN; i++)
	{
		for (size_t j = 0; j < hiddenNL; j++)
			fprintf(f, "%f\n", weightIN[i][j]);
		
	}

	fprintf(f, "\n# weightHIDE\n");
	for (size_t i = 0; i < hiddenNL; i++)
	{
		for (size_t j = 0; j < outputIN; j++)
			fprintf(f, "%f\n", weightHIDE[i][j]);
		
	}

	fclose(f);
}



void loadNetwork(char *path)
{
	FILE *f = fopen(path, "r");

	int count = 0;
	char str[10000];
	while (fgets(str, 1000, f) != NULL){count++;}
	double lines[count];
	size_t line = 0;
	rewind(f);
	while (fgets(str, 1000, f) != NULL)
	{
		if (str[0] != '#' && str[0] != '\n' && str[0] != ' ' 
										&& str[0] != '\0')
		{
			double a;
			sscanf(str, "%le", &a);
			lines[line] = a;
			line++;
		}
	}


	inputIN = lines[0];
	hiddenNL = lines[1];
	outputIN = lines[2];
	line = 3;
	
	for (size_t i = 0; i < hiddenNL; i++)
	{
		biasHidden[i] = lines[line];
		line++;
	}
	
	for (size_t i = 0; i < outputIN; i++)
	{
		biasOutput[i] = lines[line];
		line++;
	}
	
	for (size_t i = 0; i < inputIN; i++)
	{
		for (size_t j = 0; j < hiddenNL; j++)
		{
			weightIN[i][j] = lines[line];
			line++;
		}
	}

	for (size_t i = 0; i < hiddenNL; i++)
	{
		for (size_t j = 0; j < outputIN; j++)
		{
			weightHIDE[i][j] = lines[line];
			line++;
		}
	}

	fclose(f);
}

/*#############################################################*/

/*
void construct(double *resHidden, double inputs[], size_t nb1, size_t nb2){
	
	for (size_t i = 0; i < nb1; i++)
		resHidden[i] = 0;
	for (size_t j = 0; j < nb1; j++)
	{
		for (size_t i = 0; i < nb2; i++)
		{
			resHidden[j] += inputs[i] * weightIN[i][j];
		}
		resHidden[j] += biasHidden[j];
	}

	for (size_t i = 0; i < nb1; i++)
		resHidden[i] = sigmoid(resHidden[i]); 
}

*/

/*#############################################################*/

double* forwardBack(double inputs[])
{
	//resHidden part :
	double *resHidden = makeList(hiddenNL);
	for (size_t i = 0; i < hiddenNL; i++)
		resHidden[i] = 0;
	
	for (size_t j = 0; j < hiddenNL; j++)
	{
		for (size_t i = 0; i < inputIN; i++)
		{
			resHidden[j] += inputs[i] * weightIN[i][j];
		}
		resHidden[j] += biasHidden[j];
	}

	for (size_t i = 0; i < hiddenNL; i++)
		resHidden[i] = sigmoid(resHidden[i]); 


	//output part: 
	double *outputs = makeList(outputIN);

	for (size_t i = 0; i < outputIN; i++)
		outputs[i] = 0;
	
	for (size_t j = 0; j < outputIN; j++)
	{
		for (size_t i = 0; i < hiddenNL; i++)
		{
			outputs[j] += resHidden[i] * weightHIDE[i][j];
		}
		outputs[j] += biasOutput[j];
	}

	for (size_t i = 0; i < outputIN; i++)
		outputs[i] = sigmoid(outputs[i]); 


	free(resHidden);

	return outputs; 
}

/*#############################################################*/


void updateError(double* errorOUT, double targets[], double *outputs, double rate){
	
	for (size_t i = 0; i < outputIN; i++)
		errorOUT[i] = targets[i] - outputs[i];
	
	for (size_t i = 0; i < outputIN; i++)
	{
		outputs[i] =
			(outputs[i] * (1 - outputs[i])) * errorOUT[i] * rate;
	}
	
}

void backwardHI(double *errorHIDE, double *errorOUT, double *resHidden, double rate){
	
	for (size_t i = 0; i < hiddenNL; i++)
		errorHIDE[i] = 0;

	for (size_t i = 0; i < hiddenNL; i++)
	{
		for (size_t j = 0; j < outputIN; j++)
			errorHIDE[i] += errorOUT[j] * weightHIDE[i][j];
	}

	for (size_t i = 0; i < hiddenNL; i++)
	{
		resHidden[i] = (resHidden[i] * (1 - resHidden[i])) *
			errorHIDE[i] * rate;
	}

}

/*#############################################################*/

/*
double evaluate(network *n, float **samples, float **o, size_t nbInput)
{
	//printf("evaluating ... \n");
  float error = 0;
  unsigned last = n->nblayer - 1;
  //printf("%d ... \n", (int)n->nblayer);
  for (size_t i = 0; i < nbinput; i++)
  {
	  //printf("%d -- ... \n", (int)i);
    float dist = 0;
    feedForward(n, samples[i]);
	//printf("%d -- ... \n", (int)i);
    for (unsigned j = 0; j < n->layers[last]; j++)
      dist += pow(n->out[last][j]);
    error += sqrt(dist);
  }
  return error / (nbSample * 2);
}

*/

/*#############################################################*/

void updateNN(double inputs[], double targets[])
{
	double learningRate = 0.5;
	
	//Same as XOR: 
	
	double *resHidden = makeList(hiddenNL);
	for (size_t i = 0; i < hiddenNL; i++)
		resHidden[i] = 0;
	
	for (size_t j = 0; j < hiddenNL; j++)
	{
		for (size_t i = 0; i < inputIN; i++)
		{
			resHidden[j] += inputs[i] * weightIN[i][j];
		}
		resHidden[j] += biasHidden[j];
	}

	for (size_t i = 0; i < hiddenNL; i++)
		resHidden[i] = sigmoid(resHidden[i]);


	// OUTPUT 
	double *outputs = makeList(outputIN);
	for (size_t i = 0; i < outputIN; i++)
		outputs[i] = 0;
	
	for (size_t j = 0; j < outputIN; j++)
	{
		for (size_t i = 0; i < hiddenNL; i++)
		{
			outputs[j] += resHidden[i] * weightHIDE[i][j];
		}
		outputs[j] += biasOutput[j];
	}
	
	for (size_t i = 0; i < outputIN; i++)
		outputs[i] = sigmoid(outputs[i]);;


	
	// BACKWORDS :   | I |   | H | <- | O |
	

	double *errorOUT = makeList(outputIN);
	updateError(errorOUT, targets, outputs, learningRate);
	
	double **dWeightHN = CreateDoubleMatrix(hiddenNL, outputIN);

	for (size_t i = 0; i < hiddenNL; i++)
	{
		for (size_t j = 0; j < outputIN; j++)
			dWeightHN[i][j] = resHidden[i] * outputs[j];
	}

	
	for (size_t i = 0; i < hiddenNL; i++)
	{
		for (size_t j = 0; j < outputIN; j++)
			weightHIDE[i][j] += dWeightHN[i][j];
	}
	
	for (size_t i = 0; i < outputIN; i++)
		biasOutput[i] += outputs[i];

	
	//        | I |  <-  | H |   | O |
	
	double *errorHIDE = makeList(hiddenNL);
	backwardHI(errorHIDE, errorOUT, resHidden,learningRate);
	
	
	double **dWeightIN = CreateDoubleMatrix(inputIN, hiddenNL);

	for (size_t i = 0; i < inputIN; i++)
	{
		for (size_t j = 0; j < hiddenNL; j++)
			dWeightIN[i][j] = inputs[i] * resHidden[j];
	}

	
	for (size_t i = 0; i < inputIN; i++)
	{
		for (size_t j = 0; j < hiddenNL; j++)
			weightIN[i][j] += dWeightIN[i][j];
	}
	for (size_t i = 0; i < hiddenNL; i++)
		biasHidden[i] += resHidden[i];
	
	
	
	//FREE EVERYTHING : ADD IF I FORGOT ONE 
	FreeMatrix(dWeightHN, hiddenNL);
	FreeMatrix(dWeightIN, inputIN);
	free(resHidden);
	free(outputs);
	free(errorOUT);
	free(errorHIDE);
}


/*#############################################################*/

int getCharIndex(char c, char *characters)
{
  for (size_t i = 0; i < sizeof(characters); i++)
    if (characters[i] == c)
      return i;
  errx(1, "The character is not valid !");
}

char getCharFromIndex(int i, char *characters)
{
  return characters[i];
}


/*#############################################################*/
