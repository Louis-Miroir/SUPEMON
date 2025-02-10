#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    char name[50];
    // Ajoutez d'autres champs si nécessaire
} Player;

void createPlayer();
int loadGame(Player *player);  // Changer la déclaration en int

#endif