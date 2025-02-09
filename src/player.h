#ifndef PLAYER_H
#define PLAYER_H

#include "pokemon.h"

typedef struct {
    char name[20];
    int supcoins;
    Pokemon team[1]; // Pour l'instant, on gère 1 Supémon
} Player;

void createPlayer();

#endif