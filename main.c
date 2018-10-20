
# include <err.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <math.h>
//# include "xortools" 



#define generation 30000
#define learn 0.85
#define hiddenLayer  10
#define nblayer 2

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


/*
 Input Layer    ||           || Hiden Layer                         || 

    Input : 0  --- weight  ---> hidden node - Hidden node activated                              
            
            1  --- weight  --->    //               // 

                               /
                   wight >    /
                             /
                    Bias Node 

*/





double result;               // 1/0
double getOutput;            

double input_weights[nblayer][hiddenLayer]; //Input[Neurone0/1][index_of_wight_of_neurone_0/1] 
double input_bias[nblayer] = {0.0, 0.0};
double input_layer[nblayer];  // 0|1

//Hidden Layers
double hidden_weights[hiddenLayer];
double hidden_bias = 0;
double hidden_layer[hiddenLayer];


double sigmoid(double z)
{return (double)(1.0 / (1.0 + exp(-z)));}

// Desactivation function: derivative of sigmoid. 
double sigmoid_prime(double z)
{return z * (1 - z);}

// Get random value between -1 and 1
double getRandom()
{
	srand(time(NULL));
    double r =  (double)rand() / RAND_MAX - 1;
	//printf("%f\n", r);
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
            hidden_layer[x] = sigmoid((-1) *  hidden_layer[x] + input_bias[i%2] );
            getOutput += hidden_weights[x] * hidden_layer[x];
            //k++;
    }
    getOutput = sigmoid(getOutput + hidden_bias);
}

//Get back the gradient of the loss

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
//}

void display_result(int i) {
   // if(i%1000 == 0 && x == 4) printf("Generation : %d\n",i);
    //rintf("Generation : %d\n",i);
    
	if(i > generation-10)
            printf(
	        "%0.f | %0.f => %f || %f\n",
	        input_layer[0],
	        input_layer[1],
		getOutput,
	        result
	        
    );
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

int main()
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
printf("x | y => Result   || Normally\n");
    getRandWeight();
    getRandHide();
	
	const double possible_Inputs[4][2] = {
		{ 0, 0 },
		{ 1, 0 },
		{ 0, 1 },
		{ 1, 1 }};
	const double possible_Answers[4] = { 0, 1, 1, 0 };

    // train the network
   // int display = 0;
    for (int i = 0; i < generation; i++) {
        //display = 0;
        for (int inputs = 0; inputs < 4; inputs++) {
            input_layer[0] = possible_Inputs[inputs][0];
            input_layer[1] = possible_Inputs[inputs][1];
            //display +=1;
            result = possible_Answers[inputs];

            feedForward();
            backPropagation();
            if(i > generation-10) display_result(i);
            }

        if(i > generation-10)  printf("############################# \n");        
    }

}