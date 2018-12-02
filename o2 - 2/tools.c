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

/*#############################################################*/

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

void createResults(double result[], int chosen)
{
    for (int i = 0; i < chosen; i++)
        result[i] = 0;
    result[chosen] = 1;
    for (int i = chosen + 1; i < 86; i++)
        result[i] = 0;
}

/*#############################################################*/

void QuickGray(SDL_Surface* imageSurface, unsigned char ** matrix)
{
	for (int y = 0; y < imageSurface->h; y++)
	{
		for (int x = 0; x < imageSurface->w; x++)
		{
			Uint8 r, g, b;
			SDL_GetRGB(getpixel(imageSurface,x,y),imageSurface->format,
															&r,&g,&b);
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


void createSamples(long character, double input[])
{
    SDL_Surface * image;
    char path[100] = "";
	
    snprintf(path, sizeof(path),
				"res/Alphabet/%lu/%d.bmp",
							character,0);
							

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
			//sleep(1);
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

void start_TrainNN(int mode)
{
	
    newNetwork(256, 430, 86);
    if (mode)
        loadNetwork("output/network.save");
	
    srand(time(NULL));

    long int character;
    int count = 0;
    for (int i = 0; i < 10000; i++)
    {
        if (i % 10000 == 0)
        {
            printf("%d\n", count );
            count += 1;
        }

        character = rand() % 86; 

        double input[256];
        createSamples(character, input);
        double target[86];
        createResults(target, character);
        updateNN(input, target);
    }
	
	printf("(Updated NN save file!)");
    saveNetwork("output/network.save");
}

/*#############################################################*/

char testResults(double output[])
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

void printResults(int character, int mode)
{
    if (mode)
    {
        newNetwork(256, 430, 86);
        loadNetwork("output/network.save");
    }
    double input[256];
    createSamples(character, input);
    double *output = forwardBack(input);
    double target[86];
    createResults(target, character);
    printf("Expected result : %c\n", testResults(target));
    printf("result : %c\n\n\n", testResults(output));
}

/*#############################################################*/


void testNetwork()
{	
	srand(time(NULL));
    long int character;

    printf("\n\n");
    character = rand() % 86;

    for (int i = 0; i < 100; i++)
    {
        character = rand() % 86; // change here
        printf("character : %ld \n", character);
        printResults(character, 0);
    }
}

/*#############################################################*/

void main_Train(int argc, char** argv)
{
	clock_t chrono = clock();
	
    if (argc != 3)
        start_TrainNN(0);
	else
		start_TrainNN(1);
	(void) argv;
	testNetwork();
	printf("  - Time : %.6f (seconds)\n", (clock() - chrono) / 1000000.0F);
}
