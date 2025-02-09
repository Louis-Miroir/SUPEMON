#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int main() {
    int choice;

    printf("1 - New Game\n");
    printf("2 - Load Game\n");
    printf("3 - Quit\n");
    printf("Choose an option: ");
    scanf("%d", &choice);

    if (choice == 1) {
        startNewGame();
    } else if (choice == 2) {
        loadGame();
    } else if (choice == 3) {
        printf("Exiting the game...\n");
        exit(0); 
    } else {
        printf("Invalid choice. Exiting...\n");
        exit(1);
    }

    return 0;
}