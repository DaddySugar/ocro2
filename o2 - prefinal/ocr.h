#ifndef OCR_H
#define OCR_H

void saveText(char* path, char* text); 
char ocrGetChar(bitmap* letter);
char *spellCheck(char *word);

#endif
