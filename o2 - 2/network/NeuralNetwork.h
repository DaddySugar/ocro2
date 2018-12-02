#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H


int getCharIndex(char , char*);
char getCharFromIndex(int, char*);

double* makeList(size_t);

void newNetwork(size_t, size_t, size_t);
void saveNetwork(char*);
void loadNetwork(char*);

double* forwardBack(double[]);
void updateNN(double[], double[]);



#endif