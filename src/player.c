#include <stdio.h>
#include <string.h>
#include "player.h"

Player player;

void createPlayer() {
    printf("Entrez votre nom : ");
    scanf("%s", player.name);
}

// Supprimez la définition de loadGame ici