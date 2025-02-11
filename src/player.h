#ifndef PLAYER_H
#define PLAYER_H

#include "supemon.h"

typedef struct {
    char name[50];
    int supcoins;
    Supemon team[6];  
    int teamSize; 
} Player;

void createPlayer();
int loadGame(Player *player);
void saveGame(Player *player);
#endif