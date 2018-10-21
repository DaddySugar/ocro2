# include "xortools.h"



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
    //	printf("%d", r);
    return r;
}

//the activation function of a neural network
void feedForward() {
    //First
    // Hidden node values: H1 = Input1 x wight1 + Input2 x wight3 + Bias1 x wight 5; 
    //                     h2 =  //    x  //  2 +   //   x   // 4 +  //   x   //  6;

    // Calculate hidden note activation values : HA1 = 1/1+e^-H1   and  HA2 =  1/1+e^-H2
    //    //     output node values:    O1 = HA1 W7 + HA2 W9  + B2 W11
                                  //    o2 =  // W8 + //  W10 + // W12
        // OA = O
        //              2
        // error = 1/n SUM(yi - OAi   ) ^2 
        //             i-1
        
        
        //int counter = 0; 
        

        for (int i = 0; i < nblayer; i++) {
            for (int j = 0; j < hiddenLayer; j++) {
		    double tmp = input_weights[i][j] * input_layer[i];
                    hidden_layer[j] += tmp;
            
			/*Second :X  Need to go throw all the elements first. 
			if(counter % nblayer == 0)
		hidden_layer[j] = sigmoid(hidden_layer[j] + input_bias[j]);*/
        }
    }
	
	//Moved to here.
        //int k = 0; 
        for (int x = 0; x < hiddenLayer; x++) { 
            //k %= nblayer;
            hidden_layer[x] = sigmoid((-1) *  hidden_layer[x] + input_bias[x%2] );
            getOutput += hidden_weights[x] * hidden_layer[x];
            //k++;
    }
    getOutput = sigmoid(getOutput + hidden_bias);
}

void backPropagation()
 { 
     double error = getOutput - result;
     // NVM WRONG   double error = result - getOutput;  
     //  //  // error *=error;
     // 1 XOR  0 is wrong TOFIX  

	// Calculate the new values of input weights
        for (int i = 0; i < hiddenLayer; i++) {
            for (int j = 0; j < nblayer; j++) {
                double first = error * hidden_weights[i] * input_layer[j] * 
				    sigmoid_prime(hidden_layer[i])*
					sigmoid_prime(getOutput);
            
			
                input_weights[i][j]-= (first * learn);
       }

            double second = error * hidden_layer[i] *
                        sigmoid_prime(getOutput);
						

            hidden_weights[i] -= second * learn;

            double deltab1 = error * sigmoid_prime(getOutput) *
                        hidden_weights[i] *
                        sigmoid_prime(hidden_layer[i]);

        //for(int x = 0; x < nblayer; x++) 
           input_bias[i] -= deltab1 * learn;

        double hbiasupdate = sigmoid_prime(getOutput) * error;
        hidden_bias -= hbiasupdate * learn;
    }
}

void getRandWeight() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < hiddenLayer; j++)
        {
            input_weights[i][j] = getRandom();
        }
    }
}

void getRandHide() {
    for (int i = 0; i < hiddenLayer; i++)
    {
        hidden_weights[i] = getRandom();
    }
}

