#ifndef PLAYER_H
#define PLAYER_H

#define MAX_SUPEMON 6  // Limite de l'équipe
#include "supemon.h"

typedef struct {
    char name[50];
    int supcoins;
    supemon team[MAX_SUPEMON]; 
    int team_size;
} Player;  

void createPlayer();
int loadGame(Player *player);  // Changer la déclaration en int

#endif

