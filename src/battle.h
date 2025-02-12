#ifndef BATTLE_H
#define BATTLE_H

#include "player.h"
#include "supemon.h"

void startWildBattle(Player *player);
void attaquerSupemon(Supemon *attaquant, Supemon *defenseur, Player *joueur, int isWild, int attackIndex); 
void lancerCombat(Supemon *supemonJoueur, Supemon *supemonSauvage, Player *joueur);
Supemon* changerSupemon(Player *joueur);

#endif