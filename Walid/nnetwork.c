#include <stdio.h>
#include <math.h>

//Let's Make the structure of NeuralNetwork: 
//We need: 
//	- Layers + nblayer + layerlen 
//	- weigh
//	- bias 
struct NeuralNetwork {
       
	double[][] layers;
    	double[][] weights;
	double[][] bias;
	int nbLayer;
	int[] layerLen[];
}

double[][] multiplyMatrix(double[][] m1, double[][] m2, int rowLen, int columnlen)
{
       	int i, j k = 0;
	int sum = 0;
	double m[rowLen][columlen];

	for (i = 0; i < rowLen; i++) {
	  for (j = 0; j < columnlen; j++) {
		for (k = 0; k < Rowlen; k++) {
			
			sum = sum + first[i][k]*second[k][j];
		}

		m[i][j] = sum;
		sum = 0;
	  }
	}

  return m;
}

// Initiate the NETWORK: 

struct NeuralNetwork InitNetwork(int layerNumber, int[] layerLength)
{
	int maxLength = 0;
	
	for(int n = 0; n < layerNumber; n++)
	{
		if(maxLength < layerLength[n])
		{
			maxLength = layerLength[n];
		}
	}

   	 double layers[nbLayer][maxLength];
   	 double weightss[layerNumber-1][maxLength];
   	 double bias[layerNumber-1][maxLength];
 	 int w, h;
 	 for(h = 0; h < layerNumber; h++)
 	 {
	 	 for(w = 0; w < layerNumber; w++)
	 	 {
 			 weights[h][w] = 0;
 			 bias[h][w] = 0;
		 
		 }
	
	 	 NeuralNetwork NN = { layers, weights, bias, layerNumber, layerLength}
		 return NN;
	 }
}











