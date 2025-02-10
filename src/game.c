#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "game.h"
#include "battle.h"
#include "player.h"
#include "item.h"

void startNewGame(Player *player) {
    printf("Enter your name: ");
    scanf("%s", player->name);
    printf("Welcome, %s! Your adventure begins now...\n", player->name);
    chooseStarter();
    gameLoop(player);  // Passer le pointeur vers player
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

        } else if (choice == 2) {
            printf("Opening shop...\n");
            openShop(player);  // Utiliser le pointeur vers player

        } else if (choice == 3) {
            printf("Opening Supémon Center...\n");
            // openSupemonCenter(player);  // Utiliser le pointeur vers player    

        } else if (choice == 4) {
            saveGame(player);  // Utiliser le pointeur vers player
            printf("Exiting game...\n");
            exit(0);
        } else {
            printf("Feature not implemented yet. Try again!\n");
        }
    }
}

void chooseStarter(Player *player) {
    int choice;

    printf("\nChoose your starter Supémon:\n");
    printf("1 - Supmander (Fire type)\n");
    printf("2 - Supasaur (Grass type)\n");
    printf("3 - Supirtle (Water type)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (player->team_size < MAX_SUPEMON) {
        switch (choice) {
            case 1:
                player->team[0] = createSupmander();
                break;
            case 2:
                player->team[0] = createSupasaur();
                break;
            case 3:
                player->team[0] = createSupirtle();
                break;
            default:
                printf("Invalid choice, you get Supmander by default.\n");
                player->team[0] = createSupmander();
                break;
        }
        player->team_size = 1; // Mise à jour de la taille de l'équipe
    }

    printf("\nCongratulations! You chose %s as your starter!\n", player->team[0].name);
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