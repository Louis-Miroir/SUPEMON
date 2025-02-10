#include <stdio.h>
#include <string.h>
#include "player.h"

Player player; // Déclaration du joueur global

void createPlayer() {
    printf("Entrez votre nom : ");
    scanf("%s", player.name);

    player.supcoins = 500; // Exemple de monnaie initiale
    player.team_size = 0;  // L'équipe commence vide

    printf("Bienvenue, %s!\n", player.name);
}
