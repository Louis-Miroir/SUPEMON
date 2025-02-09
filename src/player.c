#include <stdio.h>
#include <string.h>
#include "player.h"
#include "supemon.h"

Player player;

void createPlayer() {
    int choice;
    printf("Entrez votre nom : ");
    scanf("%s", player.name);
    player.supcoins = 500;

    printf("\nChoisissez votre Supémon :\n");
    printf("1 - Supmander\n");
    printf("2 - Supasaur\n");
    printf("3 - Supirtle\n");
    printf("Votre choix : ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            player.team[0] = createSupmander();
            break;
        case 2:
            player.team[0] = createSupasaur();
            break;
        case 3:
            player.team[0] = createSupirtle();
            break;
        default:
            printf("Choix invalide, Supmander sélectionné par défaut.\n");
            player.team[0] = createSupmander();
    }

    printf("\nBienvenue, %s ! Vous avez choisi %s.\n", player.name, player.team[0].name);
}