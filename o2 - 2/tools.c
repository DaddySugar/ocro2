#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include "treatment.h"
#include "detection.h"
# include "queue.h"
#include "network/NeuralNetwork.h"
# include "bitmap.h"
# include "matrix.h"


/*#############################################################*/

int file_exist (char *filename)
{
  struct stat   buffer;   
  return (stat (filename, &buffer) == 0);
}

/*
void getFileRes(char file[],char res[]){
	size_t i = 0; 
	while( i < strlen(file) && 
		(file[i] != '.' || file[i] != 'b')){
		res[i] = file[i]; 
		i++;
		}
	printf("--  %s\n",res);
}

queue* getFilesFromDir(queue* res) {
	DIR *d;
	queue* samples = newQueue(); 
	struct dirent *dir;
	d = opendir("./res/Alphabet");
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			enQueue(samples,dir->d_name);
			char ttt[strlen(dir->d_name)];
			getFileRes(dir->d_name, ttt);
			enQueue(res,ttt);
			printf("%s\n", dir->d_name);
		}
		closedir(d);
	}
	
	while(samples->length > 0){
		char *s = deQueue(samples);
		printf("%s\n",s);
	}
	
	return samples;
}*/

/*#############################################################*/
void GenerateTargetNN(double target[], int chosen)
{
    for (int i = 0; i < chosen; i++)
        target[i] = 0;
    target[chosen] = 1;
    for (int i = chosen + 1; i < 86; i++)
        target[i] = 0;
}

void QuickGray(SDL_Surface* imageSurface, unsigned char ** matrix)
{
	// Fill matrix with grayscale's values of image
	for (int y = 0; y < imageSurface->h; y++)
	{
		for (int x = 0; x < imageSurface->w; x++)
		{
			Uint8 r, g, b;
			//GetRGBSDLPixel
			SDL_GetRGB(getpixel(imageSurface,x,y),imageSurface->format,&r,&g,&b);
			matrix[y][x] = (0.3 * r) + (0.59 * g) + (0.11 * b);
		}
	}

	IMG_Quit();
}

/*#############################################################*/

void QuickBan(unsigned char **grayscale, int height,
			int width, unsigned char **matrix)
{
	
	float histogram[256] = {0.0F};
	int threshold = 0;
	
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int value = grayscale[y][x];
			histogram[value]++;
		}
	}

	for(int i = 0; i < 256; i++)
	{
		histogram[i] /= (width * height);
	}
	
	float ut = 0;
	for (int i = 0; i < 256; i++)
	{
		ut += i * histogram[i];
	}

	int max_k = 0;
	float max_sigma_k = 0;
	for(int k = 0; k < 256; k++)
	{
		float wk = 0;
		for(int i = 0; i <= k; i++)
		{
			wk += histogram[i];
		}
		float uk = 0;
		for(int i = 0; i <= k; i++)
		{
			uk += i * histogram[i];
		}

		float sigma_k = 0;
		if(wk != 0 && wk != 1)
		{
			sigma_k = ((ut * wk - uk) * (ut * wk - uk)) / (wk * (1 - wk));
		}
		if(sigma_k > max_sigma_k)
		{
			max_k = k;
			max_sigma_k = sigma_k;
		}
	}
	threshold = max_k;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if(grayscale[y][x] > threshold)
			{
				matrix[y][x] = 0;
			}
			else
			{
				matrix[y][x] = 1;
			}
		}
	}
}

/*#############################################################*/


void GenerateInputNN(long character, long id, double input[])
{
    SDL_Surface * image;
    char path[100] = "";
	
    snprintf(path, sizeof(path),
				"resources/nn-training/Alphabet/%lu/%lu.bmp",
							character,id);
							
	//printf("Test file : %lu with ID = %lu\n",character, id);
	
	
	if (!file_exist (path)){
		printf("file doesn't exist");
		return;
	}
	

	image = load_image(path);
	queue *q = newQueue();
	int length =0;
	//display_image(image);
	Line_Detection(image,q, &length);
	wholefunction(image);
	
	/*unsigned char ** gray = CreateCharMatrix(
		image->w,
		image->h
	);
	QuickGray(image,gray);
	unsigned char ** bini = CreateCharMatrix(image->w,image->h);
	QuickBan(gray, image->h, image->w, bini);*/
	
	while (q->length > 0)
	{
		queue *line = deQueue(q);
		while (line->length > 0)
		{
			SDL_Surface* iii = deQueue(line);
			bitmap* letter = loadBmp(iii);
			resize(letter);
			autoContrast(letter);
			binarize(letter);
			//draw(letter);
			//sleep(1);*/
			for (int i = 0; i < 16; i++)
			{
				for (int j = 0; j < 16; j++)
					//input[i * 16 + j] = (double) bini[i][j];
					input[i * 16 + j] = (double) 
						letter->content[i * 16 + j].r == 255 ? 1 : 0;
			}
			
			freeBitmap(letter);
		}
	}	
	free(q);
	
}

/*#############################################################*/

void TrainNeuralNetwork(size_t inputN, size_t hiddenN, size_t outputN, int tours, int mode)
{
    // create the NN
    Start(inputN, hiddenN, outputN);

    // load the nn.data maybe make a mode as before???
    if (mode)
        Load("resources/nn.data");
    
    // print Predict with the values before training?
    
    // sand the rand
    srand(time(NULL));

    // character : the number represented the char chosen randomly
    // id : the id of the image in the chosen char folder
    long int character, id;
     int count = 0;
    for (int i = 0; i < tours; i++)
    {
        if (i % 10000 == 0)
        {
            printf("%d\n", count );
            count += 1;
        }
    
        //print ("%d \n", i );

        character = rand() % 86; // change here
		//character = 0;
        //id = rand() % 1016;
		id = 0;

        // retrieve the good image --> an array 16*16 with doubles inside
        double input[256];
        GenerateInputNN(character, id, input);

        // now generate the right output of this number according to character
        double target[86];
        GenerateTargetNN(target, character);

        //printf("character : %ld,    id : %ld\n", character, id);


        /*
        for (int i = 0; i < 86; i++)
        {
            if (i % 10 == 0)
                printf("\n");
            printf("%f   ", target[i]);
        }
        printf("\n\n");*/




        // train with the input and the output.
        Train(input, target);
    }
    // save in nn.data
	printf("(nn.data updated!)");
    Save("resources/nn.data");
}

/*#############################################################*/

char PredictionInterpretationNN(double output[])
{
    char res[86] = {'0','1','2','3','4','5','6',
		'7','8','9','A','B','C','D','E','F','G','H','I','J',
		'K','L','M','N','O','P','Q','R','S','T','U','V','W',
		'X','Y','Z','a','b','c','d','e','f','g','h','i','j','k',
		'l','m','n','o','p','q','r','s','t','u','v','w','x','y',
		'z', '"','(',')','=','+','-','_',47,'#','&','*', '/',
		134, '[',']','{','}',',','.', ':','?','!',';','@'};

    int max = 0;
    for (int i = 0; i < 86; i++)
    {
        if (output[max] < output[i])
            max = i;
    }
    return res[max];
}

/*#############################################################*/

void PrintPredictNN(size_t inputN, size_t hiddenN, size_t outputN,
							int character, int id, int mode)
{
    if (mode)
    {
        Start(inputN, hiddenN, outputN);
        Load("resources/nn.data");
    }
    double input[256];
    GenerateInputNN(character, id, input);
    double *output = Predict(input);
    double target[86];
    GenerateTargetNN(target, character);
    printf("Expected result : %c\n", PredictionInterpretationNN(target));
    printf("result : %c\n\n\n", PredictionInterpretationNN(output));
}



int main2(int argc, char** argv)
{

    // ******* TRAINING *******

    // if you train for the first time
    if (argc != 3)
        TrainNeuralNetwork(256, 86*5, 86, 1000000,0);
    // else
	else
    {
        unsigned long param = strtoul(argv[2], NULL,10);
        if (param == 1)
            //TrainNeuralNetwork(256, 86*5, 86, 1000000,1);
			TrainNeuralNetwork(256, 86*5, 86, 10000,1);
        else
            TrainNeuralNetwork(256, 86*5, 86, 1000000,0);
    }

unsigned long param = strtoul(argv[1], NULL,10);
(void) param;


    // ******* PREDICT/TESTS *******

    srand(time(NULL));
    long int character, id;

    printf("******* Before training *******");

    Start(256, 86*5, 86);

    for (int i = 0; i < 5; i++)
    {
        character = rand() % 86; // change here
       // id = rand() % 1016;
	   id = 0;
        
        //printf("character : %ld,    id : %ld\n\n\n", character, id);

        PrintPredictNN(256, 86*5, 86, character, id, 0);
    }

    printf("\n\n\n******* After Training *******");

    character = rand() % 86; // change here
    //id = rand() % 1016;
    id = 0;
    //printf("character : %ld,    id : %ld\n\n", character, id);

    PrintPredictNN(256, 86*5, 86, character, id, 1);

    


    for (int i = 0; i < 100; i++)
    {
        character = rand() % 86; // change here
        //id = rand() % 1016;
		id = 0;
        
        printf("character : %ld,    id : %ld\n\n", character, id);

        PrintPredictNN(256, 86*5, 86, character, id, 0);
    }


	return argc > 0;

}
