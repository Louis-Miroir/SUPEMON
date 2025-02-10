#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "player.h"

int main() {
    int choice;
    Player player;

    printf("1 - New Game\n");
    printf("2 - Load Game\n");
    printf("3 - Quit\n");
    printf("Choose an option: ");
    scanf("%d", &choice);

    if (choice == 1) {
        startNewGame();
    } else if (choice == 2) {
        if (loadGame(&player)) {
            // Continue the game with the loaded player
            printf("Game loaded successfully. Welcome back, %s!\n", player.name);
        } else {
            printf("Failed to load game.\n");
        }
    } else if (choice == 3) {
        saveGame(&player);
        printf("Exiting the game...\n");
        exit(0); 
    } else {
        printf("Invalid choice. Exiting...\n");
        exit(1);
    }

    return 0;
}