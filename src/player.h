#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    char name[50];
    int supcoins;
    struct Supemon {
        char name[20];
        int level;
        int experience;
        int hp, maxHp;
        int attack, baseAttack;
        int defense, baseDefense;
        int evasion, baseEvasion;
        int accuracy, baseAccuracy;
        int speed;
    } team[6];  // Ajoutez un tableau de Supemon pour représenter l'équipe du joueur
    int teamSize;  // Ajoutez un champ pour la taille de l'équipe
} Player;

void createPlayer();
int loadGame(Player *player);  // Changer la déclaration en int

#endif