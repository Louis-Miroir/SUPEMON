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
    strcpy(p.attacks[0].name, "Scratch");
    p.attacks[0].damage = 3;
    p.attacks[0].effect = 0;
    strcpy(p.attacks[1].name, "Growl");
    p.attacks[1].damage = 0;
    p.attacks[1].effect = 1; 
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
    strcpy(p.attacks[0].name, "Pound");
    p.attacks[0].damage = 2;
    p.attacks[0].effect = 0;
    strcpy(p.attacks[1].name, "Foliage");
    p.attacks[1].damage = 0;
    p.attacks[1].effect = 2;
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
    strcpy(p.attacks[0].name, "Pound");
    p.attacks[0].damage = 2;
    p.attacks[0].effect = 0;
    strcpy(p.attacks[1].name, "Shell");
    p.attacks[1].damage = 0;
    p.attacks[1].effect = 3; 
    return p;
}

Supemon createSupkachu() {
    Supemon p;
    strcpy(p.name, "Supkachu");
    p.level = 1;
    p.experience = 0;
    p.hp = p.maxHp = 12;
    p.attack = p.baseAttack = 1;
    p.defense = p.baseDefense = 2;
    p.evasion = p.baseEvasion = 2;
    p.accuracy = p.baseAccuracy = 1;
    p.speed = 1;
    strcpy(p.attacks[0].name, "flash");
    p.attacks[0].damage = 4;
    p.attacks[0].effect = 0;
    return p;
}

Supemon createSupaper() {
    Supemon p;
    strcpy(p.name, "Supaper");
    p.level = 1;
    p.experience = 0;
    p.hp = p.maxHp = 8;
    p.attack = p.baseAttack = 1;
    p.defense = p.baseDefense = 1;
    p.evasion = p.baseEvasion = 3;
    p.accuracy = p.baseAccuracy = 1;
    p.speed = 4;
    strcpy(p.attacks[0].name, "cut");
    p.attacks[0].damage = 3;
    p.attacks[0].effect = 0;
    return p;
}

Supemon createSuparthur() {
    Supemon p;
    strcpy(p.name, "Suparthur");
    p.level = 1;
    p.experience = 0;
    p.hp = p.maxHp = 10;
    p.attack = p.baseAttack = 1;
    p.defense = p.baseDefense = 1;
    p.evasion = p.baseEvasion = 2;
    p.accuracy = p.baseAccuracy = 1;
    p.speed = 2;
    strcpy(p.attacks[0].name, "punch");
    p.attacks[0].damage = 3;
    p.attacks[0].effect = 0;
    return p;
}

Supemon createSupnoa() {
    Supemon p;
    strcpy(p.name, "Supnoa");
    p.level = 1;
    p.experience = 0;
    p.hp = p.maxHp = 14;
    p.attack = p.baseAttack = 1;
    p.defense = p.baseDefense = 1;
    p.evasion = p.baseEvasion = 1;
    p.accuracy = p.baseAccuracy = 1;
    p.speed = 1;
    strcpy(p.attacks[0].name, "bulletseed");
    p.attacks[0].damage = 3;
    p.attacks[0].effect = 0;
    return p;
}

Supemon createSupenzo() {
    Supemon p;
    strcpy(p.name, "Supenzo");
    p.level = 1;
    p.experience = 0;
    p.hp = p.maxHp = 9;
    p.attack = p.baseAttack = 1;
    p.defense = p.baseDefense = 4;
    p.evasion = p.baseEvasion = 2;
    p.accuracy = p.baseAccuracy = 1;
    p.speed = 1;
    strcpy(p.attacks[0].name, "bite");
    p.attacks[0].damage = 4;
    p.attacks[0].effect = 0;
    return p;
}

Supemon getRandomPokemon(int level) {
    Supemon p;
    int r = rand() % 7;  
    if (r == 1) p = createSupasaur();
    else if (r == 2) p = createSupirtle();
    else if (r == 3) p = createSupkachu();
    else if (r == 4) p = createSupnoa();
    else if (r == 5) p = createSupenzo();
    else if (r == 6) p = createSupmander();
    else p = createSuparthur();

   
    for (int i = 1; i < level; i++) {
        gainExperience(&p, 500 + (i - 1) * 1000);
    }

    return p;
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