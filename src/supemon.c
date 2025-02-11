#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "supemon.h"

Supemon createSupmander() {
    Supemon p;
    strcpy(p.name, "Supmander");
    p.level = 1;
    p.experience = 0;
    p.hp = p.maxHp = 10;
    p.attack = p.baseAttack = 1;
    p.defense = p.baseDefense = 1;
    p.evasion = p.baseEvasion = 1;
    p.accuracy = p.baseAccuracy = 2;
    p.speed = 1;
    return p;
}

Supemon createSupasaur() {
    Supemon p;
    strcpy(p.name, "Supasaur");
    p.level = 1;
    p.experience = 0;
    p.hp = p.maxHp = 9;
    p.attack = p.baseAttack = 1;
    p.defense = p.baseDefense = 1;
    p.evasion = p.baseEvasion = 3;
    p.accuracy = p.baseAccuracy = 2;
    p.speed = 2;
    return p;
}

Supemon createSupirtle() {
    Supemon p;
    strcpy(p.name, "Supirtle");
    p.level = 1;
    p.experience = 0;
    p.hp = p.maxHp = 11;
    p.attack = p.baseAttack = 1;
    p.defense = p.baseDefense = 2;
    p.evasion = p.baseEvasion = 2;
    p.accuracy = p.baseAccuracy = 1;
    p.speed = 2;
    return p;
}


Supemon getRandomPokemon() {
    int r = rand() % 3;
    if (r == 0) return createSupmander();
    if (r == 1) return createSupasaur();
    return createSupirtle();
}


void gainExperience(Supemon *supemon, int experience) {
    supemon->experience += experience;
    int experienceToNextLevel = 500 + (supemon->level - 1) * 1000;

    while (supemon->experience >= experienceToNextLevel) {
        supemon->experience -= experienceToNextLevel;
        supemon->level++;
        experienceToNextLevel = 500 + (supemon->level - 1) * 1000;

        
        supemon->maxHp = (int)(supemon->maxHp * 1.3 + 0.5);
        supemon->attack = (int)(supemon->attack * 1.3 + 0.5);
        supemon->defense = (int)(supemon->defense * 1.3 + 0.5);
        supemon->evasion = (int)(supemon->evasion * 1.3 + 0.5);
        supemon->accuracy = (int)(supemon->accuracy * 1.3 + 0.5);
        supemon->speed = (int)(supemon->speed * 1.3 + 0.5);

       
        supemon->hp = supemon->maxHp;

        printf("%s a atteint le niveau %d !\n", supemon->name, supemon->level);
    }
}