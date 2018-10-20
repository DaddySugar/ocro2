# include <err.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <math.h>
//# include "xortools" 
/*Errors i can't solve : multiple definition 
		Possible causes : - #ifndef ...#endif V
						  - # include <*.c>
*/




#define generation 30000
#define learn 0.85
#define hiddenLayer  10
#define nblayer 2

double sigmoid(double z);
double sigmoid_prime(double z);
double getRandom(); 
void feedForward();
void backPropagation();
void getRandWeight();
void getRandHide();
void display_result(int i);



/* Structure of Network: 
**			
**			result : the value we are hoping to get 
**        (either 0 if both x and y have the same value otherwise 1).
** 			getOutput : the  result we will be getting. 
**			unsigned nblayer; 
**  		unsigned *layers; 
**		    float **bias;
**			float **input; 
**			float **delta_neurone; 
** 			float ***weight_neurone;
*/


//Let's assume there is 10 hidden layers : 
// const : Variably modified array at file scope
//const double hiddenLayer = 10; 
//const int nblayer = 2; 
//PROBLEM #define doesnt work. 




double result;               // 1/0
double getOutput;            

double input_weights[nblayer][hiddenLayer]; //Input[Neurone0/1][index_of_wight_of_neurone_0/1] 
double input_bias[nblayer];  // [0,0] 
double input_layer[nblayer];  // 0|1

//Hidden Layers
double h_weights[hiddenLayer];
double h_bias = 0;
double h_layer[hiddenLayer];



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
                    h_layer[j] += tmp;
            
			/*Second :X  Need to go throw all the elements first. 
			if(counter % nblayer == 0)
		h_layer[j] = sigmoid(h_layer[j] + input_bias[j]);*/
        }
    }
	
	//Moved to here.
        //int k = 0; 
        for (int i = 0; x < hiddenLayer; i++) { 
            //k %= nblayer;
            h_layer[i] = sigmoid((-1) *  h_layer[i] + input_bias[i%2] );
            getOutput += h_weights[i] * h_layer[i];
            //k++;
    }
    getOutput = sigmoid(getOutput + h_bias);
}


//Get back the gradient of the loss
void backPropagation()
 { 
     double error = getOutput - result;
     // NVM WRONG   double error = result - getOutput;  
     //  //  // error *=error;
     // 1 XOR  0 is wrong TOFIX  

	// Calculate The new values of input weights
        for (int i = 0; i < hiddenLayer; i++) {
            for (int j = 0; j < nblayer; j++) {
                double first = error * h_weights[i] * input_layer[j] * 
				    sigmoid_prime(h_layer[i])*
					sigmoid_prime(getOutput);
            
			
                input_weights[i][j]-= (first * learn);
       }

	   
	// Calculate The new value of hidden weights
            double second = error * h_layer[i] *
                        sigmoid_prime(getOutput);
			h_weights[i] -= second * learn;

            
	// Calculate The new value of Bias input
			double inputbiasupdate = error * sigmoid_prime(getOutput) *
                        h_weights[i] *
                        sigmoid_prime(h_layer[i]);

        //for(int x = 0; x < nblayer; x++) 
           input_bias[i%nblayer] -= inputbiasupdate * learn;

        double hbiasupdate = sigmoid_prime(getOutput) * error;
        h_bias -= hbiasupdate * learn;
    }
}

// Get random value between 0 and 1
double getRandom()
{
	srand(time(NULL));
    double r =  (double)rand() / RAND_MAX - 1;
	//printf("%d", r);
	return r;
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
        h_weights[i] = getRandom();
    }
}

void display_result(int i) {
   // if(i%1000 == 0 && x == 4) printf("Generation : %d\n",i);
    //rintf("Generation : %d\n",i);
    
	if(i > generation-10)
            printf(
	        "||%0.f | %0.f || => %f || %f\n",
	        input_layer[0],
	        input_layer[1],
		getOutput,
	        result
	        
    );
}

int main(int argc, char *argv[])
	{
	printf("\n\n");
	printf("	                          .,:;;;:.                                             \n ");       
	printf("                           ,##################:                                               \n");
	printf("                        +#########################`                                           \n");
	printf("                     ,##############################'                                         \n");
	printf("                   ;##################################+                                       \n");
	printf("                 ,######################################'                                     \n");
	printf("                ##########################################                                    \n");
	printf("              ,############################################'                                  \n");
	printf("             +###############################################                                 \n");
	printf("            ##################################################                                \n");
	printf("           ####################################################                               \n");
	printf("          #######################;.    `:#######################                              \n");
	printf("         #####################              '####################                             \n");
	printf("        '##################'                  ,###################                            \n");
	printf("       `##################                      +#################'                           \n");
	printf("       #################;                        `#################                           \n");
	printf("      #################.                           #################                          \n");
	printf("     `################`                             ################;                         \n");
	printf("     ################.                               ################                         \n");
	printf("    ,###############'                                .###############+                        \n");
	printf("    ################                                  +###############                        \n");
	printf("   `###############                                    ###############;                       \n");
	printf("   ###############'                                    .###############                       \n");
	printf("   ###############                                      ###############`                      \n");
	printf("  :##############;                                      `###############                      \n");
	printf("  ###############                                        ###############                      \n");
	printf("  ###############                                        :##############                      \n");
	printf(" `##############                                          ##############'                     \n");
	printf(" +##############                                          ###############                     \n");
	printf(" ###############                                          ;##############                     \n");
	printf(" ##############,                                           ##############                     \n");
	printf(" ##############                                            ##############`                    \n");
	printf(" ##############                                            ##############:                    \n");
	printf(".##############                                            ##############'                    \n");
	printf(":##############                                            '##############                    \n");
	printf("'##############                                            :##############                    \n");
	printf("+#############'                                            .##############                    \n");
	printf("##############;                                            `##############                    \n");
	printf("##############;                                            `##############                    \n");
	printf("+#############'                                            .##############                    \n");
	printf("'#############+                                            .##############                    \n");
	printf(";##############                                            ;##############                    \n");
	printf(".##############                                            +#############+                    \n");
	printf(" ##############                                            ##############:                    \n");
	printf(" ##############                                            ##############`                    \n");
	printf(" ##############                                            ##############                     \n");
	printf(" ##############;                                           ##############                     \n");
	printf(" +##############                                          '##############                     \n");
	printf(" `##############                                          ##############;                     \n");
	printf("  ##############`                                         ##############                      \n");
	printf("  ###############                                        '##############                      \n");
	printf("  ,##############                                        ##############+                      \n");
	printf("   ##############'                                      .##############                       \n");
	printf("   ###############                                      ###############                       \n");
	printf("    ##############+                                    ,##############,                       \n");
	printf("    ###############                                    ###############                        \n");
	printf("    `###############                                  ###############:                        \n");
	printf("     ###############+                                ,###############                         \n");
	printf("      ###############;                              `###############.                         \n");
	printf("      +###############:                             ################                          \n");
	printf("       ################;                          .################         `##########,      \n");
	printf("        #################                        '################,       ###############`    \n");
	printf("        :#################,                    `#################+       #################.   \n");
	printf("         +##################,                `###################        ##################   \n");
	printf("          #####################,          `+####################         ###################  \n");
	printf("           ####################################################          '###.      ########  \n");
	printf("            ##################################################           :#          #######` \n");
	printf("              ,############################################+                          ######+ \n");
	printf("                ##########################################.                           ######+ \n");
	printf("                 '#######################################                             ######; \n");
	printf("                   ####################################                              `######  \n");
	printf("                     ################################`                               #######  \n");
	printf("                       '##########################+                                 `#######  \n");
	printf("                          '####################+`                                   #######   \n");
	printf("                              :+###########;`                                      +#######   \n");
	printf("                                                                                  ,#######    \n");
	printf("                                                                                  #######,    \n");
	printf("                                                                                 ########     \n");
	printf("                                                                                ########      \n");
	printf("                                                                               ########       \n");
	printf("                                                                              ########        \n");
	printf("                                                                             ########`        \n");
	printf("                                                                            ########`         \n");
	printf("                                                                           ########`          \n");
	printf("                                                                          ########`           \n");
	printf("                                                                        `########`            \n");
	printf("                                                                        ######################\n");
	printf("                                                                        ######################\n");
	printf("                                                                        ######################\n");
	printf("                                                                        ######################\n");
	printf("                                                                        ######################\n");
	printf("\n\n\n\n\n");




	if(if (argc < 2)  
    { 
        // no arguments in ./main 
 
    
		printf("XOR Function test: \n\n");
		printf("|| x | y || => Result   || Normally\n");
		
		getRandWeight();
		getRandHide();
		
		input_bias = {0.0, 0.0};
		
		
		const double InputsXY[4][2] = {
			{ 0, 0 },
			{ 1, 0 },
			{ 0, 1 },
			{ 1, 1 }};
		const int AnswerOut[4] = { 0, 1, 1, 0 };

		for (int i = 0; i < generation; i++) {
			for (int inputs = 0; inputs < 4; inputs++) {
				input_layer[0] = InputsXY[inputs][0];
				input_layer[1] = InputsXY[inputs][1];
				result = AnswerOut[inputs];
			
					//xor
				feedForward();
				backPropagation();
				if(i > generation-10) display_result(i);
				
				}

			if(i > generation-10)  printf("############################# \n");        
		}
	}
	else{
		printf("make sure you remove the extra argument %c ", argv[1] ); 
	}

}