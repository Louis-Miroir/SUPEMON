#include <stdio.h>
#include <string.h>
#include "player.h"

Player player;

void createPlayer() {
    printf("Entrez votre nom : ");
    scanf("%s", player.name);
}

void loadGame(Player *player) {
    // Implémentez la logique de chargement du jeu ici
}