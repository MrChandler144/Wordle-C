// this one makes wordle.
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int checkGreen(char word[], char guess[], int spot)
{
	if (word[spot]==guess[spot])
	{
		return 2;
	}

	return 0;
}

int checkYellow(char word[], char guess[], int spot)
{
	int i;
	for (i=0; i<5; i++)
	{
		if(guess[spot] == word[i])
		{
			return 1;
		}
	}
	
	return 0;
}

// this one gets a word at a time
void getWord(char word[])
{
	int i=0;
	FILE *fp;
	fp=fopen("setlist.txt", "r");
	// If it fails, fp==NULL is true.
	if (fp==NULL)
	{
		printf("something went wrong here fp didn't open");
	}
	
	fgets(word, 100, fp);//, "%s", word); // prints out the first word
	
	// fgure out how many to take
	int num;
	num=rand() % 2300;
	num=num+3;

	while ((i<num) && (fgets(word, 100, fp) != NULL))
	{
		i++;
	}
	
	// so now we have the loop
	// find the length
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
	//printf("the word is %s\n", word);
}

int isItValid(char guess[])
{
	// this one just checks if a guess is valid
	
	// initalise the text file with all the words on it
	char word[1998];
	FILE *fp;
	fp=fopen("setlistcomplete.txt", "r");
	// If it fails, fpr==NULL is true.
	if (fp==NULL)
	{
		printf("something went wrong here fp didn't open");
	}
	
	int matchq=0;
	// check if out guess matches a word
	while (fgets(word, 100, fp) != NULL)
	{
		if ((guess[0]==word[0]) && (guess[1]==word[1]) && (guess[2]==word[2]) && (guess[3]==word[3]) && (guess[4]==word[4]))
		{
			matchq = 1;
			//printf("a match\n");
		}
	}
	// if you get here we didn't return a value, so return nothing
	return matchq;
}


int main(void)
{
	int didTheyWin = 0;
	srand(time(NULL));
	
	// initialise the word they gotta guess
	char word[1998];
	getWord(word);
	
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
	
	// so we run this charade six times
	int count=0;
	int charadesRun=0;
	int index = 0;
	
	
	// run the program
	int i, j, validq;
	while (charadesRun <6)
	{
		// display results
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
		
		
		
		// ask for a word
		validq=0;
		printf("Guess %d:\n", charadesRun+1);
		while (validq==0)
		{
			scanf("%s", &guess);
			validq=isItValid(guess);
		}
		
		// process our guess
		for (i=0; i<5; i++)
		{
			// make it lower case
			if ('A' <= guess[i] && guess[i] <='Z')
			{
				guess[i]=guess[i]+'a'-'A';
			}
			
			// put it into our display array
			guesses[charadesRun][i]=guess[i];
		}
		
		// then compare the word
		// first check for greens, then yellows.
		// 0 is grey, 1 is yellow, 2 is green
		
		for (i=0; i<5; i++)
		{
			// set the character in the results array
			spots[charadesRun][i]=checkGreen(word, guess, i);
			
			if (spots[charadesRun][i] != 2)
			{
				// wasn't green, check if yellow
				spots[charadesRun][i]=checkYellow(word, guess, i);
				
				// if it was yellow, make the keyboard caps, and make the display caps
				if (spots[charadesRun][i] == 1)
				{
					guesses[charadesRun][i]=guesses[charadesRun][i]+'A'-'a';
					index=0;
					while (keyboard[index]!='\0')
					{
						if(keyboard[index] == guess[i])
						{
							keyboard[index]=keyboard[index]+'A'-'a';
						}
						index++;
					}
				}
				
			} else {
				// was green, add to the count
				count=count+1;
				
				//make it caps for display
				guesses[charadesRun][i]=guesses[charadesRun][i]+'A'-'a';
				
				// make the keyboard caps
				index=0;
				while (keyboard[index]!='\0')
				{
					if(keyboard[index] == guess[i])
					{
						keyboard[index]=keyboard[index]+'A'-'a';
					}
					index++;
				}
			}
		}
		// if we got five greens, we won and also count=5
		if (count==5)
		{
			// exit while loop
			charadesRun=charadesRun+7;
			didTheyWin=1;
		} else {
			// reset
			count=0;
		}
		
		charadesRun++;
		
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
	}

	// display results one last time
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
	
	if (didTheyWin==1)
	{
		if (charadesRun-7 == 1)
		{
			printf("\nYou Win! Good work!\nYou won in %d round\n", charadesRun-7);
		} else {
			printf("\nYou Win! Good work!\nYou won in %d rounds\n", charadesRun-7);
		}
	} else {
		printf("ha u suck!\nThe word was %s, noob\n", word);
	}
}