#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "item.h"  // Inclure item.h pour accéder aux déclarations de openShop et openSupemonCenter

#define MAX_NAME_LENGTH 50
#define MAX_SUPEMONS 6
#define MAX_ITEMS 10

typedef struct {
    char name[20];
    int level;
    int experience;
    int hp, maxHp;
    int attack, baseAttack;
    int defense, baseDefense;
    int evasion, baseEvasion;
    int accuracy, baseAccuracy;
    int speed;
} Supemon;

// Déclaration des fonctions
void saveGame(Player *player);
int loadGame(Player *player);

void startNewGame(Player *player);
void startWildBattle();
void gameLoop(Player *player);
void chooseStarter();

#endif