#ifndef XOR_TOOLS_H
#define XOR_TOOLS_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <err.h>
# include <math.h>
# include <time.h>


double sigmoid(double z);
double sigmoid_prime(double z);
double getRandom(); 
void softmax(unsigned k, float *z);


#endif
