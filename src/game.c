#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "game.h"

void startNewGame(Player *player) {
    printf("Enter your name: ");
    scanf("%s", player->name);
    printf("Welcome, %s! Your adventure begins now...\n", player->name);
    chooseStarter(player);
    gameLoop(player);
}

void gameLoop(Player *player) {
    int choice;

    while (1) {
        printf("\n--- What do you want to do? ---\n");
        printf("1 - Into the Wild (Battle a random Supémon)\n");
        printf("2 - Shop\n");
        printf("3 - Supémon Center\n");
        printf("4 - Save & Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 1) {
            startWildBattle(player);
        } else if (choice == 2) {
            printf("Opening shop...\n");
            openShop(player);
        } else if (choice == 3) {
            printf("Opening Supémon Center...\n");
            openSupemonCenter(player);
        } else if (choice == 4) {
            saveGame(player);
            printf("Exiting game...\n");
            exit(0);
        } else {
            printf("Invalid choice. Try again!\n");
        }
    }
}

void chooseStarter(Player *player) {
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
            player->team[0] = createSupmander();
            break;
        case 2:
            strcpy(starter, "Supasaur");
            player->team[0] = createSupasaur();
            break;
        case 3:
            strcpy(starter, "Supirtle");
            player->team[0] = createSupirtle();
            break;
        default:
            printf("Invalid choice, you get Supmander by default.\n");
            strcpy(starter, "Supmander");
            player->team[0] = createSupmander();
            break;
    }

    printf("\nCongratulations! You chose %s as your starter!\n", starter);
    player->teamSize = 1;
}

void saveGame(Player *player) {
    FILE *file = fopen("savegame.dat", "wb"); 
    if (!file) {
        printf("Failed to open save file.\n");
        return;
    }
    fwrite(player, sizeof(Player), 1, file);
    fclose(file);
    printf("Game saved successfully.\n");
}

int loadGame(Player *player) {
    FILE *file = fopen("savegame.dat", "rb"); 
    if (!file) {
        printf("Failed to open save file.\n");
        return 0;
    }
    fread(player, sizeof(Player), 1, file);
    fclose(file);
    printf("Game loaded successfully.\n");
    return 1;
}