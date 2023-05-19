/*
Team member 1 "Josh Dwight" | "33%"
Team member 2 "Adeife Fadahunsi" | "33%"
Team member 3 "Rayane Kadri" | "33%"
*/


////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define boardLength 60
#define boardHeight 20
#define MAX_WORD_LENGTH 20

// prototypes
int fileLength();
void printBoard(char list[boardHeight][MAX_WORD_LENGTH], int spaceBeforeWord[boardHeight]);
void addWordToFile(int wordsAdded);
void getWordFromFile(int n, char word[MAX_WORD_LENGTH]);
void addWordToBoard(char list[boardHeight][MAX_WORD_LENGTH], int spaceBeforeWord[boardHeight]);


int main(){
	srand((int)time(0));
	int gameStartTime;
	int gameEndTime;
	int roundStartTime; 
	int roundEndTime;
	int wordsOnBoard = 0;
	int gameTotalTime; 
	int roundTotalTime;
	char scannedWord[20];
	int endgame = 0;
	int wordsAdded;
	char textFile[20] = "wordList.txt";

	//begin menu
	printf("This is a typing game. Words will appear on the board that you need to type. The amount of words that appears depends on how long you take to type the word.\n");
	printf("There are currently %d words in the file\n", fileLength(0));
	printf("Would you like to play or add a word? (p/a): ");
	scanf("%s", scannedWord);
	
	//if user key is a, add a word to the file
	int loops = 0;
	while (strcmp(scannedWord, "a") == 0) {
		addWordToFile(loops);
		printf("There are now %d words. Would you like to play or add another word? (p/a): ", fileLength(0));
		scanf("%s", scannedWord);
	}

    //initializing the board
	int spaceBeforeWord[boardHeight + 1];
	char words[boardHeight + 1][MAX_WORD_LENGTH];
	
	//spaceBeforeWords are initialized as zero, and there are no words yet, so every row in words is initialized as a blank space
	for (int i = 0; i < boardHeight; i++) {
		spaceBeforeWord[i] = 0;
		strcpy(words[i], "");
	}
	
    //start time for the game
	gameStartTime = time(0);

    //put word on the board after board was initialized
	addWordToBoard(words, spaceBeforeWord);

    //while the player hasn't lost, execute this loop
	while(endgame == 0) {
		//wordsOnBoard stores the amount of words that are currently on the board as well as words that were previously on the board. It's basically a total word count
		
		//if the word count is below 15, one word is added for every three seconds that the user took to type the current word
		if (wordsOnBoard < 15) {
			for (int i = 0; i < roundTotalTime; i = i + 3) {
				if (strcmp(words[boardHeight - 1], "") != 0) { //if the bottom of the board has a word in it, then the user failed
					endgame = 1;
				}
				
				//if they didn't fail, add a word to the board and increment wordsOnBoard
				addWordToBoard(words, spaceBeforeWord); 
				++wordsOnBoard;
				}
		} 	
		
		//if the word count is below 30 but above 15, one word is added for every two seconds that the user took to type the current word
		else if (wordsOnBoard < 30) {
			for (int i = 0; i < roundTotalTime; i = i + 2) {
				if (strcmp(words[boardHeight - 1], "") != 0) {
					endgame = 1; 
				}
				
				addWordToBoard(words, spaceBeforeWord);
				++wordsOnBoard;
				}
		} 
		
		//if the word count is above 30, one word is added for every second that the user took to type the current word	
		else {
			for (int i = 0; i < roundTotalTime; ++i) {
				if (strcmp(words[boardHeight - 1], "") != 0) { 
					endgame = 1;
				}
				
				addWordToBoard(words, spaceBeforeWord);
				++wordsOnBoard;
			}
		}

		if (endgame == 1) {
			break;
		}
		
		printBoard(words, spaceBeforeWord);
		
		roundStartTime = time(0); //time right before user enters word
		scanf("%s", scannedWord);
		roundEndTime = time(0); //time right after user enters word
		roundTotalTime = roundEndTime - roundStartTime;

		//for each row in the board (starting from the bottom), if the scannedWord matches the word in the row (if there is any), the word is removed from the row
		//This removal is done by setting the row equal to ""
		for (int i = boardHeight - 1; i >= 0; i--) {
			if (strcmp(scannedWord, words[i]) == 0) {
				strcpy(words[i], "");
				break; //only deletes the bottom-most word
			}
		}
	}

  //ends timer for whole game
	gameEndTime = time(0);
	gameTotalTime = gameEndTime - gameStartTime;
	
	//displays how long the game took
	printf("This game took you %d minutes and %d seconds", (gameTotalTime / 60), (gameTotalTime % 60));
	
	return 0;
}

/*///////////
//functions//
///////////*/

//used to add a word to the board
void addWordToBoard(char list[boardHeight][MAX_WORD_LENGTH], int spaceBeforeWord[boardHeight]) {
	//starting at the bottom, move all words down one spot to free up the top for a word
	for (int i = boardHeight - 1; i > 0; i--) {
		strcpy(list[i], list[i - 1]);
		spaceBeforeWord[i] = spaceBeforeWord[i - 1];
	}

	//gets a word from the file
	char wordToAdd[MAX_WORD_LENGTH];
	getWordFromFile((rand() % fileLength(0)), wordToAdd);
	
	//adds the obtained word to the top of the word array
	strcpy(list[0], wordToAdd);
	
	//randomizes the space before the word
	spaceBeforeWord[0] = rand() % (boardLength - strlen(list[0]) + 1);
}

//used to print the board
void printBoard(char list[boardHeight][MAX_WORD_LENGTH], int spaceBeforeWord[boardHeight]) {
  system("clear");
	for (int i = 0; i < boardLength + 1; i++) {
		printf("_");
	}
	printf("\n");
	
	for (int i = 0; i < boardHeight; i++) {
		// Creates a temporary string for an entire line of the board
		char line[boardLength + 2] = "|";
		int length = strlen(list[i]);
		
		// Adds spaces up until the words "x" position
		for (int j = 0; j < spaceBeforeWord[i]; j++) {
			strcat(line, " ");
		}
    // Adds the word
		strcat(line, list[i]);
		// Fills in spaces after until boardLength is reached
		for (int j = spaceBeforeWord[i] + length; j < boardLength; j++) {
			strcat(line, " ");
		}
		// Closes off the line, then prints
		strcat(line, "|");

		printf("%s\n", line);
	}
	
	for (int i = 0; i < boardLength + 1; i++) {
		printf("_");
	}
	
	printf("\n");
}

//used to get a word from the file
void getWordFromFile(int n, char word[MAX_WORD_LENGTH]) {
	FILE* wordList = NULL;
	
	//open wordlist.txt in read mode
	wordList = fopen("wordList.txt", "r");
	
	for (int i = 0; i <= n; ++i) {
		fscanf(wordList, "%s", word);
	}
	fclose(wordList);
}

int fileLength() {
	FILE* wordList = NULL;
	char word[MAX_WORD_LENGTH];
	int fileLength = 0;
	
	//opening wordlist.txt in read mode
	wordList = fopen("wordList.txt", "r");
	
	//while not at end of file, increment fileLength by 1 if there's a word in that index
	while (!feof(wordList)) {
		fscanf(wordList, "%s", word);
		++fileLength;
    }
	
	//don't need file anymore, so close
	fclose(wordList);
	
	return fileLength;
}

void addWordToFile(int wordsAdded) 
{
    char userInput[100];
	
    FILE *wordFile;
    //opening wordlist.txt in append mode
    wordFile = fopen("wordList.txt", "a");
    
    //scanning user's desired word that is then printed onto the file
    printf("\nType in your desired word: ");
    scanf("%s", userInput);
	fprintf(wordFile, "\n%s", userInput);
   
	//don't need file anymore, so close
    fclose(wordFile);
}