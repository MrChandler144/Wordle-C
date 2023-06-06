// this one reads in setlistfull.txt, takes the five-letter word from each line, and puts it into setlistcomplete.txt.
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

/* Reads all of the words from the dictionary file, and stores those of the appropriate length into memory */

// this one gets a word at a time
void getWord(char word[])
{
	// initialise a few things
	int i=0;
	FILE *fpr;
	FILE *fpw;
	
	// initialise the file we read from
	fpr=fopen("setlistfull.txt", "r");
	// If it fails, fpr==NULL is true.
	if (fpr==NULL)
	{
		printf("something went wrong here fpr didn't open");
	}
	
	// initialise the file we write to`
	fpw=fopen("setlistcomplete.txt", "w");
	// If it fails, fpw==NULL is true.
	if (fpw==NULL)
	{
		printf("something went wrong here fpw didn't open");
	}
	
	// skip over the first line (column headers)
	fgets(word, 100, fpr);
	
	// go through the rest of the words
	while (fgets(word, 100, fpr) != NULL)
	{
		//we have our line
		// extract the word
		i=0;
		while (word[i+1]!= '\0')
		{
			i++;
		}
		// assign our number
		word[0]=word[i-5];
		word[1]=word[i-4];
		word[2]=word[i-3];
		word[3]=word[i-2];
		word[4]=word[i-1];
		word[5]='\0';
		
		// go write it to the file
		fprintf(fpw,"%s\n", word);
	}
} 


int main(void)
{
	// it works
	char word[1998];
	getWord(word);
}