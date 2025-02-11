#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "item.h"
#include "battle.h"
#include "supemon.h" 


void saveGame(Player *player);
int loadGame(Player *player);

void startNewGame(Player *player);
void gameLoop(Player *player);
void chooseStarter(Player *player);

#endif