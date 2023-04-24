//SE 185: Final Project Template//
/////////////////////////
/* 
Team member 1 "Josh Dwight" | "Percentage of Contribution to The Project"
Team member 2 "Name" | "Percentage of Contribution to The Project"
Team member 3 "Name" | "Percentage of Contribution to The Project"
Team member 4 "Name" | "Percentage of Contribution to The Project"
*/

////////////////////
#include<stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define MAX_WORDS 2000
#define MAX_WORD_LENGTH 15

//add more here////

//////////////////////
//Struct Definition//
////////////////////


/////////////////////////////////////
//User Defined Functions Prototype//
//List prototypes here and define//
//tehm below the main function////
/////////////////////////////////
int read_words(char *word_list[MAX_WORDS], char *file_name);

int main(){
	char *word_list[MAX_WORDS];
	int word_count = read_words(word_list, "wordList.txt");
	srand(time(NULL));
	printf("Hello, this is a typing game. You will need to type the words as they appear\n");
	printf("Would you like to play or add a word?\n You currently have %d words that can be used.\n(p/a)");	

	
	
	
	
	return 0;
}

///////////////////////////////////////
//User Defined Functions' Definition//
/////////////////////////////////////

int read_words(char *word_list[MAX_WORDS], char *file_name)
{
    int number_of_words_read = 0;
    char line[MAX_WORD_LENGTH];
    char *pointer;
    FILE *file = fopen(file_name, "r");

    while (!feof(file))
    {
        pointer = fgets(line, MAX_WORD_LENGTH, file);
        if (pointer != NULL)
        {
            trim_whitespace(line);
            word_list[number_of_words_read] = (char *) malloc(strlen(line) + 1);
            strcpy(word_list[number_of_words_read], line);
            number_of_words_read++;
        }
    }

    fclose(file);
    return number_of_words_read;
}
