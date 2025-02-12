#ifndef SUPEMON_H
#define SUPEMON_H

typedef struct {
    char name[20];
    int damage;
    int effect; 
} Attack;

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
    Attack attacks[2]; 
} Supemon;

Supemon createSupmander();
Supemon createSupaper();
Supemon createSupnoa();
Supemon createSupenzo();
Supemon createSupasaur();
Supemon createSupirtle();
Supemon createSuparthur();
Supemon createSupkachu();
Supemon getRandomPokemon(int level); 
void gainExperience(Supemon *supemon, int experience);

#endif