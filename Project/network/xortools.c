#include "xor.h"

// Normal sigmoid function
double sigmoid(double z)
{
	return (double)(1.0 / (1.0 + exp(-z)));
}

// Desactivation function: derivative of sigmoid. 
double sigmoid_prime(double z)
{
	//return sig(y) x (1-sig(y))
	return z * (1 - z);
	
}

// Get random value between -1 and 1
double getRandom()
{
	srand(time(NULL));
    double r =  (double)rand() / RAND_MAX - 1;
	printf("%d", r);
	return r;
}

