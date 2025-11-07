
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_TRIES 6
#define WORD_COUNT 30

// Function declarations
void displayHangman(int wrong);
void displayWord(char word[], int guessed[]);
int checkWin(char word[], int guessed[]);
void playGame();
void clearScreen();

// Word bank
char* wordBank[WORD_COUNT] = {
    "COMPUTER", "KEYBOARD", "MONITOR", "PROGRAM", "SOFTWARE",
    "HARDWARE", "INTERNET", "WEBSITE", "DATABASE", "NETWORK",
    "PYTHON", "LANGUAGE", "COLLEGE", "STUDENT", "LIBRARY",
    "SCIENCE", "MATHEMATICS", "FOOTBALL", "CRICKET", "MOUNTAIN",
    "RIVER", "OCEAN", "FOREST", "DESERT", "ANIMAL",
    "TIGER", "ELEPHANT", "GIRAFFE", "DOLPHIN", "PENGUIN"
};

int main() {
    char choice;
    
    srand(time(NULL));  // Initialize random seed
    
    printf("\n");
    printf("****************************************\n");
    printf("*                                      *\n");
    printf("*      WELCOME TO HANGMAN GAME!        *\n");
    printf("*                                      *\n");
    printf("****************************************\n");
    printf("\n");
    
    do {
        playGame();
        
        printf("\n\nDo you want to play again? (y/n): ");
        scanf(" %c", &choice);
        choice = tolower(choice);
        
    } while(choice == 'y');
    
    printf("\n");
    printf("****************************************\n");
    printf("*   Thanks for playing! Goodbye!       *\n");
    printf("****************************************\n");
    printf("\n");
    
    return 0;
}

void playGame() {
    // Select random word
    char* secretWord = wordBank[rand() % WORD_COUNT];
    int wordLength = strlen(secretWord);
    
    // Array to track which letters have been guessed (26 letters)
    int guessed[26] = {0};
    
    int wrongGuesses = 0;
    int gameOver = 0;
    char guess;
    
    clearScreen();
    
    printf("\n=== NEW GAME ===\n");
    printf("Guess the word! You have %d chances.\n\n", MAX_TRIES);
    
    // Main game loop
    while(!gameOver) {
        // Display hangman
        displayHangman(wrongGuesses);
        
        // Display word with blanks
        printf("\nWord: ");
        displayWord(secretWord, guessed);
        
        printf("\n\nAttempts remaining: %d\n", MAX_TRIES - wrongGuesses);
        
        // Display guessed letters
        printf("Guessed letters: ");
        for(int i = 0; i < 26; i++) {
            if(guessed[i]) {
                printf("%c ", 'A' + i);
            }
        }
        printf("\n");
        
        // Get user input
        printf("\nEnter a letter: ");
        scanf(" %c", &guess);
        guess = toupper(guess);
        
        // Validate input
        if(!isalpha(guess)) {
            printf("\nPlease enter a valid letter!\n");
            printf("Press Enter to continue...");
            getchar();
            getchar();
            clearScreen();
            continue;
        }
        
        int letterIndex = guess - 'A';
        
        // Check if already guessed
        if(guessed[letterIndex]) {
            printf("\nYou already guessed that letter!\n");
            printf("Press Enter to continue...");
            getchar();
            getchar();
            clearScreen();
            continue;
        }
        
        // Mark as guessed
        guessed[letterIndex] = 1;
        
        // Check if letter is in word
        int found = 0;
        for(int i = 0; i < wordLength; i++) {
            if(secretWord[i] == guess) {
                found = 1;
                break;
            }
        }
        
        if(found) {
            printf("\n✓ Good guess!\n");
        } else {
            wrongGuesses++;
            printf("\n✗ Wrong guess!\n");
        }
        
        printf("Press Enter to continue...");
        getchar();
        getchar();
        clearScreen();
        
        // Check win condition
        if(checkWin(secretWord, guessed)) {
            clearScreen();
            displayHangman(wrongGuesses);
            printf("\n");
            printf("****************************************\n");
            printf("*                                      *\n");
            printf("*         CONGRATULATIONS!             *\n");
            printf("*            YOU WON! 🎉               *\n");
            printf("*                                      *\n");
            printf("****************************************\n");
            printf("\nThe word was: %s\n", secretWord);
            printf("Wrong guesses: %d/%d\n", wrongGuesses, MAX_TRIES);
            gameOver = 1;
        }
        
        // Check lose condition
        if(wrongGuesses >= MAX_TRIES) {
            clearScreen();
            displayHangman(wrongGuesses);
            printf("\n");
            printf("****************************************\n");
            printf("*                                      *\n");
            printf("*            GAME OVER!                *\n");
            printf("*            YOU LOST! 😢              *\n");
            printf("*                                      *\n");
            printf("****************************************\n");
            printf("\nThe word was: %s\n", secretWord);
            gameOver = 1;
        }
    }
}

void displayHangman(int wrong) {
    printf("\n");
    printf("  +---+\n");
    printf("  |   |\n");
    
    // Head
    if(wrong >= 1)
        printf("  |   O\n");
    else
        printf("  |    \n");
    
    // Body and arms
    if(wrong >= 4)
        printf("  |  /|\\\n");
    else if(wrong >= 3)
        printf("  |  /|\n");
    else if(wrong >= 2)
        printf("  |   |\n");
    else
        printf("  |    \n");
    
    // Legs
    if(wrong >= 6)
        printf("  |  / \\\n");
    else if(wrong >= 5)
        printf("  |  /  \n");
    else
        printf("  |     \n");
    
    printf("  |     \n");
    printf("==========\n");
}

void displayWord(char word[], int guessed[]) {
    for(int i = 0; i < strlen(word); i++) {
        char letter = word[i];
        int letterIndex = letter - 'A';
        
        if(guessed[letterIndex]) {
            printf("%c ", letter);
        } else {
            printf("_ ");
        }
    }
}

int checkWin(char word[], int guessed[]) {
    for(int i = 0; i < strlen(word); i++) {
        int letterIndex = word[i] - 'A';
        if(!guessed[letterIndex]) {
            return 0;  // Not all letters guessed yet
        }
    }
    return 1;  // All letters guessed - WIN!
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}