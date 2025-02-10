#ifndef GAME_H
#define GAME_H

#include "player.h"  // Inclure player.h pour accéder à la définition de Player


// Déclaration des fonctions
void saveGame(Player *player);
void loadGame(Player *player);

void startNewGame();
void startWildBattle();
void gameLoop();
void chooseStarter();

#endif