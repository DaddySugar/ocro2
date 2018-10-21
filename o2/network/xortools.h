#ifndef XOR_TOOLS_H
#define XOR_TOOLS_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <err.h>
# include <math.h>
# include <time.h>

#define generation 30000
#define learn 0.85
#define hiddenLayer  10
#define nblayer 2


double result;               // 1/0
double getOutput;            

double input_weights[nblayer][hiddenLayer]; //Input[Neurone0/1][index_of_wight_of_neurone_0/1] 
double input_bias[nblayer] = {0,0};  // [0,0] 
double input_layer[nblayer];  // 0|1

//Hidden Layers
double hidden_weights[hiddenLayer];
double hidden_bias = 0;
double hidden_layer[hiddenLayer];


double sigmoid(double z);
double sigmoid_prime(double z);
double getRandom(); 
void feedForward();
void backPropagation();
void getRandWeight();
void getRandHide();


#endif
