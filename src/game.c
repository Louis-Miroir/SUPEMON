#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "game.h"

void startNewGame(Player *player) {
    printf("Enter your name: ");
    scanf("%s", player->name);
    printf("Welcome, %s! Your adventure begins now...\n", player->name);
    chooseStarter();
    gameLoop(player);  // Passer le pointeur vers player
}

void startWildBattle() {
    printf("\nA wild Supémon appears!\n");

    char *supemons[] = {"Supmander", "Supasaur", "Supirtle"};
    srand(time(NULL));
    int randomIndex = rand() % 3;

    printf("It's a wild %s!\n", supemons[randomIndex]);
    printf("The battle begins...\n");

    // Ici, tu devras implémenter la logique du combat (attaques, tours, capture, etc.)
}

void gameLoop(Player *player) {
    int choice;

    while (1) {
        printf("\n--- What do you want to do? ---\n");
        printf("1 - Into the Wild (Battle a random Supémon)\n");
        printf("2 - Shop (Not implemented yet)\n");
        printf("3 - Supémon Center (Not implemented yet)\n");
        printf("4 - Save & Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 1) {
            startWildBattle(); 
        } else if (choice == 4) {
            saveGame(player);  // Utiliser le pointeur vers player
            printf("Exiting game...\n");
            exit(0);
        } else {
            printf("Feature not implemented yet. Try again!\n");
        }
    }
}

void chooseStarter() {
    int choice;
    char starter[20];

    printf("\nChoose your starter Supémon:\n");
    printf("1 - Supmander (Fire type)\n");
    printf("2 - Supasaur (Grass type)\n");
    printf("3 - Supirtle (Water type)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            strcpy(starter, "Supmander");
            break;
        case 2:
            strcpy(starter, "Supasaur");
            break;
        case 3:
            strcpy(starter, "Supirtle");
            break;
        default:
            printf("Invalid choice, you get Supmander by default.\n");
            strcpy(starter, "Supmander");
            break;
    }

    printf("\nCongratulations! You chose %s as your starter!\n", starter);
}

void saveGame(Player *player) {
    FILE *file = fopen("savegame.dat", "wb"); // Mode binaire "wb" = write binary
    if (!file) {
        printf("Failed to open save file.\n");
        return;
    }
    fwrite(player, sizeof(Player), 1, file);
    fclose(file);
    printf("Game saved successfully.\n");
}

int loadGame(Player *player) {
    FILE *file = fopen("savegame.dat", "rb"); // Mode binaire "rb" = read binary
    if (!file) {
        printf("Failed to open save file.\n");
        return 0;
    }
    fread(player, sizeof(Player), 1, file);
    fclose(file);
    printf("Game loaded successfully.\n");
    return 1;
}