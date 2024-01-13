#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAXGUESSES 6     //guesses 5
#define WORDSIZE 25



int win =1;
void HangmanRules(void);
void UpperCaseword(char word[WORDSIZE]);
void CreateStarword(char starword[], int length);
void PlayOneGame(char solution[]);
char GetTheLetterGuess(char lettersGuessed[WORDSIZE], int *numPtr);
int ReplaceStars(char solution[WORDSIZE], char secretword[WORDSIZE], char letter);
void PlayAgain(char *againPtr);
int DidYouWin(char solution[WORDSIZE]);

void printBody(int mistakes)
{
    printf("\n");
    if(mistakes==2){
        printf("\n _________");
        printf("\n|         |");
        printf("\n|            ");
	    printf("\n|            ");
	    printf("\n|            ");
        printf("\n|            ");
        printf("\n|            ");
    }
    else if(mistakes==3){
        printf("\n _________");
        printf("\n|         |");
        printf("\n|        ( )");
	    printf("\n|            ");
	    printf("\n|            ");
        printf("\n|            ");
        printf("\n|            ");
    }
    else if(mistakes==4){
        printf("\n _________");
        printf("\n|         |");
        printf("\n|        ( )");
	    printf("\n|        /|\\");
	    printf("\n|            ");
        printf("\n|            ");
        printf("\n|            ");
    }
    else if(mistakes==5){
        printf("\n _________");
        printf("\n|         |");
        printf("\n|        ( )");
	    printf("\n|        /|\\ ");
	    printf("\n|        | |  ");
        printf("\n|             ");
        printf("\n|             ");
    }
}

int main()
{
    char solution[WORDSIZE];
    char again = 1;
    printf("                                    *** Welcome to Hangman Game ***\n");
    HangmanRules();
    FILE *WordGame;
    WordGame = fopen("inputWords.txt", "r");

    if(WordGame != NULL)
    {
        do
        {
            for(int t=1; t<=3; t++)
            {
                printf("\n\n                                           --- STAGE %d ---",t);
                fscanf(WordGame,"%s", solution);
                UpperCaseWord(solution);
                PlayOneGame(solution);
                break;
            }
            if(win==3)
            {
                PlayAgain(&again);
            }
        }
        while (tolower(again) == 'y');
        fclose(WordGame);
    }
    else
    {
        printf("Unable to open file inputWords.txt");
    }
    return 0;
}

void HangmanRules(void)
{
    printf("\nPlease read the following playing instructions.\n");
    printf("- You will be presented with a word to be guessed\n");
    printf("- Guess letters one at a time and there is three stages.\n");
    printf("- You can have up to five incorrect letter guesses\n");
    printf("- You can only guess the word when you have made a correct letter guess\n");
    printf("- The game will be OVER when you have guessed the word correctly in all of three stage\n");
    printf("  Or when you have guessed letters incorrectly Five times.\n\n");
}

void UpperCaseWord(char word[WORDSIZE])
{
    int i, length_A;
    length_A = strlen(word);
    for (i = 0; i < length_A; i++)
    {
        word[i] = toupper(word[i]);
    }
}

void CreateStarword(char starword[], int length)
{
    int j;

    for (j = 0; j<length; j++)
    {
        starword[j] = '*';
    }
    starword[j] = '\0';
}
void PlayOneGame(char solution[])
{
    char secretword[WORDSIZE];
    CreateStarword(secretword, strlen(solution));
    char lettersGuessed[26];
    char letter;
    int count=0, i, result = 0, found, num_guess=0;
    printf("\nHere are the letters guessed so far:");
    for(i=0; i<num_guess; i++)
        printf("%c",lettersGuessed[i]);
    printf("\n");
    for(i=0; i<strlen(secretword); i++)
        printf("%c",secretword[i]);
    printf("\n");

    while(count < MAXGUESSES && result == 0)
    {
        letter = GetTheLetterGuess(lettersGuessed, &num_guess);
        found = ReplaceStars(solution, secretword, letter);
        if(found == 1)
        {
            printf("\nThe letter was in the word, you can now guess the word:");

            printf("\nSecret Word: ");
            for(i=0; i<strlen(secretword); i++)
                printf("%c",secretword[i]);
            printf("\n");
            result = DidYouWin(solution);
            if(result == 1)
            {
                printf("You won that stage, congratulations!");
                win ++;
                break;
            }
            else
            {
                printf("\nThat is not the correct word");
            }
        }
        else
        {
            count++;
            printf("\nThe letter was not in the word, the value of wrongGuesses is now %d",count);
            printBody(count);
        }
        printf("\n Here are the letters guessed so far:");
        for(i=0; i<num_guess; i++)
            printf("%c",lettersGuessed[i]);
        printf("\n\n");
        for(i=0; i<strlen(secretword); i++)
        {
            printf("%c",secretword[i]);
        }
        printf("\n");
    }
    if(result == 0 )
    {
        printf("You did not win this stage, the solution was\n%s",solution);
    }
}
char GetTheLetterGuess(char lettersGuessed[WORDSIZE], int *numPtr)
{
    char letter;
    int i;
    printf("\nGuess a letter: ");
    fflush(stdout);
    scanf("%c",&letter);
    letter = toupper(letter);
    printf("\n\n");
    for(i=0; i<*numPtr; i++)
    {
        if(lettersGuessed[i] == letter)
            return letter;
    }
    lettersGuessed[*numPtr] = letter;
    *numPtr = *numPtr + 1;
    return letter;
}

int ReplaceStars(char solution[WORDSIZE], char secretword[WORDSIZE], char letter)
{
    int i;
    int found = 0;
    for(i=0; i<strlen(solution); i++)
    {
        if(solution[i] == letter)
        {
            secretword[i] = letter;
            found = 1;
        }
    }
    return found;
}

int DidYouWin(char solution[WORDSIZE])
{
    char word[WORDSIZE];

    printf("\nGuess the word: ");
    fflush(stdout);
    scanf("%s",word);
    UpperCaseWord(word);

    if(strcmp(solution,word) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void PlayAgain(char *againPtr)
{
    printf("\nDo you want to play again?\ny -> Yes\nq-> Quit\n");
    fflush(stdout);
    scanf("%c",againPtr);
}
