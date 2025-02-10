#ifndef supemon_H
#define supemon_H

typedef struct {
    char name[20];
    int level;
    int experience;
    int hp, max_hp;
    int attack, base_attack;
    int defense, base_defense;
    int evasion, base_evasion;
    int accuracy, base_accuracy;
    int speed;
} supemon;

supemon createSupmander();
supemon createSupasaur();
supemon createSupirtle();
supemon getRandomPokemon(); // Pour générer un adversaire

void ajouterExperience(supemon *p, int exp);
int arrondiAleatoire(float valeur);


#endif
