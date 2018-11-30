#ifndef matrix_h
#define matrix_h



typedef struct Matrix
{
	int x;
	int y;
	int* mat;// = malloc(x*y * sizeof(int);
}Matrix;

void printMatrix(Matrix mat);
Matrix ConstructMatrix(int x, int y);
void initMatrix(Matrix a);
Matrix sumMatrix(Matrix a, Matrix b);
Matrix subtractionMatrix(Matrix a, Matrix b);
Matrix multMatrix(Matrix a, Matrix b);
Matrix multMatrixLambda(Matrix a, int lambda);
Matrix sumMatrixLambda(Matrix a, int lambda);
Matrix subtractionMatrixLambda(Matrix a, int lambda);
Matrix giveMatrixDiag(int x, int y);
Matrix transposeMatrix(Matrix a);
Matrix andBinary(Matrix a, Matrix b);

#endif
