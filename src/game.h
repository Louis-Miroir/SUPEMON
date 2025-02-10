#ifndef GAME_H
#define GAME_H

#include "player.h"  // Inclure player.h pour accéder à la définition de Player

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
int loadGame(Player *player);  // Changer la déclaration en int

void startNewGame();
void startWildBattle();
void gameLoop(Player *player);  // Modifier pour accepter un pointeur vers Player
void chooseStarter();

#endif