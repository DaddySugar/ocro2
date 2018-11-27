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
		img = load_image("lena.bmp");
		greyscale(img);
		makeitblackandwhite(img,img->w,img->h);
		display_image(img);
	}
	else if(argv[1][0] == '3')
		{
			img = load_image("res/learn1.bmp");
			//learning("res/learn1", img, 1);
			network *n = loadNetwork("network.save");
			int i = 0;
			char txt[1000 + 1];
			txt[1000] = 0;
			
			int len = 0; 
			queue *q = newQueue();
		//	img = load_image("index.bmp");
			greyscale(img);
			makeitblackandwhite(img,img->w,img->h);
			Line_Detection(img,q, &len);
			
			
			while (q->length > 0)
			{
				queue *line = deQueue(q);
				while (line->length > 0)
				{
					bitmap* letter = loadBmp(deQueue(line));
					
					
					//bitmap *letter = loadBmp(letter); 	
					
					resize(letter);
					autoContrast(letter);
					binarize(letter);
					draw(letter);
					printf("\n %d -- \n", q->length);
					txt[i] = ocr(letter, n);
					printf("\n %d -- \n", line->length);
					printf("%c\n", txt[i]);
						i++;
					
					freeBitmap(letter);
					
					
				}

                            txt[i] = '\n'; 
                            i++; 
			}	
			free(q);
			printf("\n done\n");
			printf("%s\n", txt);
			printf("There  is %d \n", len);
			return 0;
		}
			
	else{
	
		img = load_image("res/learn1.bmp");

		if(argv[1][0] == '2') generateNetwork();
			
		
		
		
		else if(argv[1][0] == '4') {
			
			printf("Start Training process 2! %s %d \n", argv[2], argc-2);
			//char* kkk = aaa;
			learning();
			return 1;
		}
		
		else if(argv[1][0] == '6')
		{
			printf("Start Training process!");
			//learning("res/learn1", img, 1);
		}
		
		else if(argv[1][0] == '7')
		{
			img = load_image("pdf_test.bmp");
			greyscale(img);
			makeitblackandwhite(img,img->w,img->h);
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
