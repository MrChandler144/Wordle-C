 _ _ _           _ _     
| | | |___ ___ _| | |___ 
| | | | . |  _| . | | -_|
|_____|___|_| |___|_|___|

This is a collection of programs that catalogues my progress in developing the game of wordle.
It contains eight successive versions of the main game, the wordlist as I downloaded it from the internet, the wordlist I used, and the C script I used to turn the downloaded word list into the used list.
The final version is wordle8.

A word is selected from the external word list, and each guess is checked against it. Valid guesses activate the machinery of the program.
Grey tiles are represented by a 0, yellow tiles are represented by a 1, and green tiles are represented by a 2.
The word you guessed is displayed alongside the letters, with individual letters capitalised if they are found in the word.
Finally, a keyboard is placed just under the display grid, representing letters guessed, unguessed and placed.
This project was a lot of fun to develop and play with my friends, and required a lot of thought around handling edge cases.

Developed from November 2 to November 30 2022, revisited and polished on June 6 2023
