#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "supemon.h"


supemon createSupmander() {
    supemon p;
    strcpy(p.name, "Supmander");
    p.level = 1;
    p.experience = 0;
    p.hp = p.max_hp = 10;
    p.attack = p.base_attack = 1;
    p.defense = p.base_defense = 1;
    p.evasion = p.base_evasion = 1;
    p.accuracy = p.base_accuracy = 2;
    p.speed = 1;
    return p;
}

supemon createSupasaur() {
    supemon p;
    strcpy(p.name, "Supasaur");
    p.level = 1;
    p.experience = 0;
    p.hp = p.max_hp = 9;
    p.attack = p.base_attack = 1;
    p.defense = p.base_defense = 1;
    p.evasion = p.base_evasion = 3;
    p.accuracy = p.base_accuracy = 2;
    p.speed = 2;
    return p;
}

supemon createSupirtle() {
    supemon p;
    strcpy(p.name, "Supirtle");
    p.level = 1;
    p.experience = 0;
    p.hp = p.max_hp = 11;
    p.attack = p.base_attack = 1;
    p.defense = p.base_defense = 2;
    p.evasion = p.base_evasion = 2;
    p.accuracy = p.base_accuracy = 1;
    p.speed = 2;
    return p;
}

// Générer un Supémon aléatoire
supemon getRandomPokemon() {
    int r = rand() % 3;
    if (r == 0) return createSupmander();
    if (r == 1) return createSupasaur();
    return createSupirtle();
}

void ajouterExperience(supemon *p, int exp) {
    p->experience += exp;
    int expRequis = 500 + (p->level - 1) * 1000;

    while (p->experience >= expRequis) {
        p->experience -= expRequis;
        p->level++;
        printf("%s monte au niveau %d !\n", p->name, p->level);

        // Augmentation des stats de 30% avec arrondi aléatoire
        p->max_hp = arrondiAleatoire(p->max_hp * 1.3);
        p->attack = arrondiAleatoire(p->attack * 1.3);
        p->defense = arrondiAleatoire(p->defense * 1.3);
        p->evasion = arrondiAleatoire(p->evasion * 1.3);
        p->accuracy = arrondiAleatoire(p->accuracy * 1.3);
        p->speed = arrondiAleatoire(p->speed * 1.3);

        // Mise à jour des HP actuels
        p->hp = p->max_hp;

        expRequis = 500 + (p->level - 1) * 1000;
    }
}

// Fonction pour arrondir aléatoirement un nombre
int arrondiAleatoire(float valeur) {
    return (rand() % 2 == 0) ? (int)valeur : (int)valeur + 1;
}