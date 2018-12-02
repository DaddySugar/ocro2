#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "treatment.h"
#include "detection.h"
# include "queue.h"
#include "network/NeuralNetwork.h"
//#include "network/learning.h"
# include "bitmap.h"
# include "tools.h"
#include <stdlib.h>

/*
int kkkkk(char image[]) {
    SDL_Event event;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    SDL_Window *window = NULL;

    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(
        COMMON_WINDOW_WIDTH, COMMON_WINDOW_WIDTH,
        0, &window, &renderer
    );
    IMG_Init(IMG_INIT_PNG);
    texture = IMG_LoadTexture(renderer, image);
    common_fps_init();
    while (1) {
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        common_fps_update_and_print();
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
    SDL_DestroyTexture(texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
*/


int main(int argc, char * argv[])
{
	//unsigned long param = strtoul(argv[1], NULL, 10);
	SDL_Surface * img;
	
	printf("Start Training process!\n");
	
	if(argv[1][0] == '0') {
		img = load_image(argv[2]);
		//greyscale(img);
		display_image(img);
		//kkkkk(argv[2]);
		}
		
	else if(argv[1][0] == '1'){
		img = load_image(argv[2]);
		printf("Image OTSU + Dynamique expansion :");
		expansiondynamique(img);
		wholefunction(img);
		display_image(img);
	}
	else if(argv[1][0] == '3')
		{
			img = load_image(argv[2]);
			int len = 0; 	
			queue *q = newQueue();
			char segtext[1000+1];
			segmentation(img, q,&len, segtext);
			//printf("The text is: %s", segtext);
		}
			
	else{
	
		img = load_image("res/learn1.bmp");

		if(argv[1][0] == '2') //generateNetwork();
			return 1;
			
		
		else if(argv[1][0] == '6')
		{
			printf("Start Training process!");
			//learningChar();
			main_Train(argc,argv);
		}
		
		else if(argv[1][0] == '7')
		{
			/*queue* qqq = newQueue();
			getFilesFromDir(qqq);*/
			return 1;
		}
		else {
			printf("\tThis option does not exist\n");
			return 1; 
		}
}
	
	if(argv[1][0] != '4' && argv[1][0] != '0' && argv[1][0] != '1' )
		display_image(img);
	

	if(argc != 0) return 1; 
	return 0;
}

