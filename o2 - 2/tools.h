#ifndef TOOLS_H
#define TOOLS_H

void GenerateTargetNN(double target[], int chosen);
void GenerateInputNN(long character, long id, double input[]);
void TrainNeuralNetwork(size_t inputN, size_t hiddenN, size_t outputN, int tours, int mode);
char PredictionInterpretationNN(double output[]);
void PrintPredictNN(size_t inputN, size_t hiddenN, size_t outputN, int character, int id, int mode);
int file_exist (char *filename);
int main2(int argc, char** argv);

#endif