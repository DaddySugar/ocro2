#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
# include <stdlib.h>
# include "treatment.h"
# include "detection.h"
# include "queue.h"
# include "network/NeuralNetwork.h"
# include "bitmap.h"
# include "ocr.h"
//# include <hunspell/hunspell.h>


char res[86] = {'0', '1', '2', '3', '4', '5', '6', '7', '8',
	'9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
	'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
	'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
	'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u',
	'v', 'w', 'x', 'y', 'z', '"', '(', ')', '=', '+', '-', '_',
	47, '#', '&', '*', '/', 134, '[', ']', '{', '}', ',', '.', 
	':', '?', '!', ';', '@'};
	
	
void saveText(char* path, char* text)
{
	FILE *f = fopen(path, "w");
	fputs(text, f);
	fclose(f);
}

char ocrGetChar(bitmap* letter)
{
	
	newNetwork(256, 430, 86);
	loadNetwork("output/network.save");
	
	
	double input[256];
	for (int i = 0; i < 256; i++)
	{
		input[i] = (double) letter->content[i].r == 255 ? 1 : 0;
	}


	double *output = forwardBack(input);


	char res[86] = {'0', '1', '2', '3', '4', '5', '6', '7', '8',
	'9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
	'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
	'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
	'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u',
	'v', 'w', 'x', 'y', 'z', '"', '(', ')', '=', '+', '-', '_',
	47, '#', '&', '*', '/', 134, '[', ']', '{', '}', ',', '.', 
	':', '?', '!', ';', '@'};
	
	
	int best = 0;
	
	for (int i = 0; i < 86; i++)
	{
		if (output[best] < output[i])
			best = i;
	}
	
	//printf("Best choice : %c\n", res[best]);
	return res[best];
}


//https://stackoverflow.com

char* spellCheck(char *letter)
{
	/*Hunhandle *handle = Hunspell_create("/usr/share/hunspell/en_US.aff", "/usr/share/hunspell/en_US.dic");

	int isCorrect = Hunspell_spell(handle, letter);
	if(!isCorrect)
	{
		char ***s = malloc(sizeof(char));
		Hunspell_suggest(handle, s, letter);
		Hunspell_destroy(handle);
		if (*s != NULL)
		{
			return s[0][0];
		}
	}
	
	saveText("output/OUTPUT_Spellcheck.txt", letter);*/
	(void) letter;
	return letter;
}
