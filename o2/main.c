#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "treatment.h"
#include "detection.h"
# include "queue.h"
#include "network/network.h"
#include "network/learning.h"
# include "bitmap.h"



int main(int argc, char * argv[])
{
	//unsigned long param = strtoul(argv[1], NULL, 10);
	SDL_Surface * img;
	
	printf("Start Training process!\n");
	
	if(argv[1][0] == '0') {
		img = load_image("lena.bmp");
		greyscale(img);
		display_image(img);
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
			printf("The text is: %s", segtext);
		}
			
	else{
	
		img = load_image("res/learn1.bmp");

		if(argv[1][0] == '2') generateNetwork();
			
		
		
		
		else if(argv[1][0] == '4') {
			
			printf("Start Training process 2! %s %d \n", argv[2], argc-2);
			//char* kkk = aaa;
			learning(argv + 2, argc-2);
			return 1;
		}
		
		else if(argv[1][0] == '6')
		{
			printf("Start Training process!");
			learningChar();
		}
		
		else if(argv[1][0] == '7')
		{
			img = load_image("pdf_test.bmp");
			greyscale(img);
			//makeitblackandwhite(img,img->w,img->h);
			//Line_Detection(img);
			//Height_Detection(img);
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
