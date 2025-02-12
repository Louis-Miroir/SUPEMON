#ifndef PLAYER_H
#define PLAYER_H
#define MAX_ITEMS 10

#include "supemon.h"

typedef struct {
    char name[20];
    int price;
    int effect;
    int quantity;
} Item;

typedef struct {
    char name[50];
    int supcoins;
    Supemon team[6];
    int teamSize;
    Item items[MAX_ITEMS];  
    int item_count;
} Player;

void createPlayer();
int loadGame(Player *player);
void saveGame(Player *player);

#endif