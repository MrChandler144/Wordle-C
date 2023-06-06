// this one makes wordle.
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

// v8 (final) brings a radical rethink to the way yellows and greens work by creating dummy variables for both word and guess and vandalising those
// developed from 2022-11-02 to 2022-11-30, then revisted and polished on 2023-06-06

void checkGreen(char altWord[], char altGuess[], int spots[25][25], int *count, char guesses[25][25], int charadesRun, char keyboard[])
{
	// we need to go through each letter
	// if it matches then write to the necessary arrays
	// and remove the letters from the altGuess and altWord
	
	int i;
	for (i=0; i<5; i++)
	{
		if (altWord[i] == altGuess[i])
		{
			// we found a match
			// write to the output display (numbers)
			spots[charadesRun][i] = 2;
			
			// add to the count
			*count=*count+1;
			
			// update the letters display array with capitals
			guesses[charadesRun][i]=guesses[charadesRun][i]+'A'-'a';
			
			// make the keyboard capitals
			int index=0;
			while (keyboard[index]!='\0')
			{
				if (keyboard[index] == altGuess[i])
				{
					keyboard[index]=keyboard[index]+'A'-'a';
				}
				index++;
			}
			
			// and finally we need to remove these letters from our alts
			altGuess[i]=' ';
			altWord[i]='.';		// different characters to avoid potential bugs
		}
	}
}

void checkYellow(char altGuess[], char altWord[], int spots[25][25], int charadesRun, char guesses[25][25], char keyboard[])
{
	// go through the altGuess a letter at a time
	// and for each letter go thorugh the altWord a letter at a time
	// if there's a match manage that and move onto the next letter in altGuess (using a break)
	
	// go through altGuess a letter at a time
	int i, j;
	for (i=0; i<5; i++)
	{
		// and go through altWord a letter at a time
		for (j=0; j<5; j++)
		{
			// if they are the same then make the spots array 1 and remove both letters and stop looking through the word
			if (altGuess[i] == altWord[j])
			{
				// update the spots number array
				spots[charadesRun][i]=1;
				
				// update the letters display array with capitals
				guesses[charadesRun][i]=guesses[charadesRun][i]+'A'-'a';
				
				// and make the keyboard capitals
				int index=0;
				while (keyboard[index]!='\0')
				{
					if (keyboard[index] == altGuess[i])
					{
						keyboard[index]=keyboard[index]+'A'-'a';
					}
					index++;
				}
				
				// remove the letters from altWord and altGuess
				altGuess[i]=' ';
				altWord[j]='.';
			
				// then stop looking through altWord
				break;
			}
		}	
	}	
}

void getWord(char word[])
{
	// this one gets the word you have to guess
	FILE *fp;
	fp=fopen("setlistcomplete.txt", "r");		// setlistcomplete is the list of words
	// If it fails, fp==NULL is true.
	if (fp==NULL)
	{
		printf("something went wrong here fp didn't open");
	}
	
	fgets(word, 100, fp);
	
	// figure out how many to take
	int num;
	int i = 0;
	num=rand() % 2300;
	num=num+3;

	while ((i<num) && (fgets(word, 100, fp) != NULL))
	{
		i++;
	}
	// and now we have our word
	
	/*
	word[0]='f';
	word[1]='l';
	word[2]='u';
	word[3]='f';
	word[4]='f';
	*/
	
	// this is useful for testing v
	//printf("the word is %s\n", word);
}

int isItValid(char guess[])
{
	// this one just checks if a guess is valid
	char word[1998];
	
	// initalise the text file with all the words on it
	FILE *fp;
	fp=fopen("setlistcomplete.txt", "r");
	// If it fails, fp==NULL is true.
	if (fp==NULL)
	{
		printf("something went wrong here fp didn't open");
	}
	
	// check if out guess matches a word
	while (fgets(word, 100, fp) != NULL)
	{
		if ((guess[0]==word[0]) && (guess[1]==word[1]) && (guess[2]==word[2]) && (guess[3]==word[3]) && (guess[4]==word[4]))
		{
			// strcmp doesn't work (not sure why) but that ^ does so it's ok
			// anyway this is a match return a 1
			return 1;
		}
	}
	// if you get here there were no matches, return a 0
	return 0;
}

void displayResults(int spots[25][25], char guesses[25][25], char keyboard[])
{
	// displays the results to the user, the closest thing this program has to a UI :)
	int i,j;
	for (i=0; i<6; i++)
	{
		for (j=0; j<5; j++)
		{
			printf("%d", spots[i][j]);
		}
		printf("\t");
		for (j=0; j<5; j++)
		{
			printf("%c", guesses[i][j]);
		}
		printf("\n");
	}
	printf("%s", keyboard);
}

int main(void)
{
	// initialise the word they gotta guess
	srand((int)time(NULL));
	char word[1998];
	getWord(word);
	word[5]='\0';	// would otherwise be a newline
	
	// intialise results arrays
	int spots[25][25]={0};
	char guesses[25][25]={' '};
	
	// intialise our player's guess
	char guess[1998]="     ";
	
	// intialise the keyboard
	char keyboard[1998]=
	"q w e r t y u i o p\n"	
	" a s d f g h j k l\n"
	"  z x c v b n m\n\n";
	
	// intialise some other variables
	int i, validq;
	int charadesRun=0;
	int count=0;
	int index = 0;
	int didTheyWin = 0;
	
	
	// run the program
	while (charadesRun <6)
	{
		displayResults(spots, guesses, keyboard);
		
		// ask for a word
		validq=0;
		printf("Guess %d:\n", charadesRun+1);
		while (validq==0)
		{
			scanf("%s", &guess);
			// process our guess for validation
			for (i=0; i<5; i++)
			{
				// make it lower case
				if ('A' <= guess[i] && guess[i] <='Z')
				{
					guess[i]=guess[i]+'a'-'A';
				}
				
				// put it into our display array as well this is the most convenient spot
				guesses[charadesRun][i]=guess[i];
			}
			
			// and check if it's a good guess
			validq=isItValid(guess);
		}
		
		// then compare the word
		// we will do this by making a dummy word and dummy guess and running some functions on them
		char altWord[8];
		char altGuess[8];
		
		// make them duplicates of their words (I prefer this over strcpy)
		for (i=0; i<6; i++)
		{
			altWord[i]=word[i];
			altGuess[i]=guess[i];
		}
		
		// Now check for greens
		checkGreen(altWord, altGuess, spots, &count, guesses, charadesRun, keyboard);
		
		// and yellows
		checkYellow(altGuess, altWord, spots, charadesRun, guesses, keyboard);
		
		// weed out the letters we guessed from the keyboard
		for (i=0; i<6; i++)
		{
			index = 0;
			while (keyboard[index]!='\0')
			{
				if(keyboard[index] == guess[i])
				{
					keyboard[index]=' ';
				}
				index++;
			}
		}
		
		charadesRun++;
		
		// check for win conditions (five greens means count is 5)
		if (count==5)
		{
			// complete this while loop but don't do another one
			didTheyWin=1;
			break;
		} else {
			// reset count
			count=0;
		}
	}

	// display results one last time
	displayResults(spots, guesses, keyboard);
	
	// and check the win condition
	if (didTheyWin==1)
	{
		if (charadesRun == 1)
		{
			printf("\nYou Win! Good work!\nYou won in %d round\n", charadesRun);
		} else {
			printf("\nYou Win! Good work!\nYou won in %d rounds\n", charadesRun);
		}
	} else {
		printf("Better luck next time!\nThe word was %s\n", word);
	}
}