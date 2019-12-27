#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int playGame(int rowLength, int userBet);

int main() {
    int userChoice;
    int userBet = 0;
    int rowLength = 0;
    int userBill;
    bool isPlaying = true;
    time_t t;

    srand((unsigned) time(&t)); /* Intializes random number generator */

    printf("Welcome \n  Enter digit to choose menu \n   1) Rools \n   2) Make bet \n   3) Choose row length \n   4) Play \n   5) Exit \n");

    while (isPlaying) {
        printf("\n Make your choice ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
                printf(" all the numbers are 7 - the bet x3 \n all the numbers are the same - the bet x2 \n at least one 7 - the bet is kept\n");
                break;
            case 2:
                printf("Enter your bet ");
                scanf("%d", &userBet);
                break;
            case 3:
                printf("Enter row length ");
                scanf("%d", &rowLength);
                break;
            case 4:
                if (userBet == 0) printf("\n Your bet is 0. Make the bet.");
                else if (rowLength <= 3) {
                    userBet = playGame(5, userBet);
                    printf("\n Your bet is %d", (int) userBet);
                } else {
                    userBet = playGame(rowLength, userBet);
                    printf("\n Your bet is %d", (int) userBet);
                }
                break;
            case 5:
                isPlaying = false;
                break;
            default  :
                printf("No option selected \n");
        }
    }
    return EXIT_SUCCESS;
}


int playGame(int rowLength, int userBet) {

    int gamingBoard[rowLength];
    int k = 0;
    int l = 0;
    int r = 0;

    for (int i = 0; i < rowLength; i++) {
        gamingBoard[i] = 1 + rand() % 8;
    }

    for (int i = 0; i < rowLength; i++) {
        printf(" %d ", gamingBoard[i]);
    }

    for (int i = 0; i < rowLength; i++) {
        if (gamingBoard[0] == gamingBoard[i] && gamingBoard[0] != 7) l++;
        if (gamingBoard[i] == 7) k++;
    }

    if (l == rowLength) userBet *= 2;
    if (k == rowLength) userBet *= 3;
    if (k == 0) userBet = 0;

    return userBet;
}