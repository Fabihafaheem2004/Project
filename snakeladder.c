#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rollDice() {
    return rand() % 6 + 1;
}

int movePlayer(int currentPlayer, int dice) {
    int newPosition = currentPlayer + dice;

    int snakes[] = {99, 65, 25};
    int ladders[] = {13, 60, 70};
    int newPositions[] = {1, 40, 9, 42, 83, 93};

    for (int i = 0; i < 3; i++) {
        if (newPosition == snakes[i]) {
            printf("Oops! You landed on a snake! Go down to position %d\n", newPositions[i]);
            return newPositions[i];
        } else if (newPosition == ladders[i]) {
            printf("Hooray! You climbed a ladder! Go up to position %d\n", newPositions[i + 3]);
            return newPositions[i + 3];
        }
    }

    return newPosition;
}

void displayBoard(int player1, int player2) {
    printf("--------------------------------------------------\n");
    for (int row = 10; row >= 1; row--) {
        for (int col = 1; col <= 10; col++) {
            int position = row * 10 - (row % 2 == 0 ? col : 10 - col + 1);
            if (position == player1)
                printf("P1\t");
            else if (position == player2)
                printf("P2\t");
            else
                printf("%d\t", position);
        }
        printf("\n");
    }
    printf("--------------------------------------------------\n");
}

int main() {
    srand(time(NULL));

    int player1 = 0, player2 = 0;

    while (1) {
        displayBoard(player1, player2);

        printf("Player 1's turn. Press Enter to roll the dice.\n");
        getchar();
        int diceRoll = rollDice();
        printf("Player 1 rolled: %d\n", diceRoll);
        player1 = movePlayer(player1, diceRoll);
        printf("Player 1 is now at position %d\n", player1);

        if (player1 >= 100) {
            printf("Player 1 wins!\n");
            break;
        }

        displayBoard(player1, player2);

        printf("Player 2's turn. Press Enter to roll the dice.\n");
        getchar();
        diceRoll = rollDice();
        printf("Player 2 rolled: %d\n", diceRoll);
        player2 = movePlayer(player2, diceRoll);
        printf("Player 2 is now at position %d\n", player2);

        if (player2 >= 100) {
            printf("Player 2 wins!\n");
            break;
        }
    }

    return 0;
}
