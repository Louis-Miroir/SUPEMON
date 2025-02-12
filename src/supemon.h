#ifndef SUPEMON_H
#define SUPEMON_H

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

Supemon createSupmander();
Supemon createSupaper();
Supemon createSupnoa();
Supemon createSupenzo();
Supemon createSupasaur();
Supemon createSupirtle();
Supemon createSuparthur();
Supemon createSupkachu();
Supemon getRandomPokemon(); 
void gainExperience(Supemon *supemon, int experience); 

#endif