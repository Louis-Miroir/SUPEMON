#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "battle.h"
#include "item.h"

void startWildBattle(Player *player) {
    if (player->teamSize == 0) {
        printf("Vous n'avez aucun Supémon pour combattre !\n");
        return;
    }

    Supemon supemonSauvage = getRandomPokemon(player->team[0].level);
    printf("\nUn %s sauvage apparaît !\n", supemonSauvage.name);

    if (player->team[0].hp > 0) {
        lancerCombat(&player->team[0], &supemonSauvage, player);
    } else {
        printf("Votre Supémon est K.O. !\n");
    }
}


void attaquerSupemon(Supemon *attaquant, Supemon *defenseur, Player *joueur, int isWild, int attackIndex) {
    Attack attack = attaquant->attacks[attackIndex];
    if (attack.damage > 0) {
        int degats = attack.damage + attaquant->attack - defenseur->defense;
        if (degats < 0) degats = 0;
        defenseur->hp -= degats;
        if (defenseur->hp < 0) defenseur->hp = 0;
        printf("%s (Niveau %d, HP %d/%d) utilise %s et inflige %d points de dégâts à %s (Niveau %d, HP %d/%d) !\n",
               attaquant->name, attaquant->level, attaquant->hp, attaquant->maxHp,
               attack.name, degats,
               defenseur->name, defenseur->level, defenseur->hp, defenseur->maxHp);
    }
    if (attack.effect == 1) {
        attaquant->attack++;
        printf("%s (Niveau %d, HP %d/%d) utilise %s et augmente son attaque !\n",
               attaquant->name, attaquant->level, attaquant->hp, attaquant->maxHp, attack.name);
    } else if (attack.effect == 2) {
        attaquant->evasion++;
        printf("%s (Niveau %d, HP %d/%d) utilise %s et augmente son évasion !\n",
               attaquant->name, attaquant->level, attaquant->hp, attaquant->maxHp, attack.name);
    } else if (attack.effect == 3) {
        attaquant->defense++;
        printf("%s (Niveau %d, HP %d/%d) utilise %s et augmente sa défense !\n",
               attaquant->name, attaquant->level, attaquant->hp, attaquant->maxHp, attack.name);
    }
}


Supemon* changerSupemon(Player *joueur) {
    int choix;
    printf("\nChoisissez un Supémon pour combattre :\n");
    for (int i = 0; i < joueur->teamSize; i++) {
        printf("%d - %s (Niveau %d, HP %d/%d)\n", i + 1, joueur->team[i].name, joueur->team[i].level, joueur->team[i].hp, joueur->team[i].maxHp);
    }
    printf("Entrez le numéro du Supémon : ");
    scanf("%d", &choix);

    if (choix < 1 || choix > joueur->teamSize || joueur->team[choix - 1].hp <= 0) {
        printf("Choix invalide ou Supémon K.O. !\n");
        return NULL;
    }

    return &joueur->team[choix - 1];
}

void utiliserObjet(Player *joueur, Supemon *supemon) {
    int choix;
    printf("\nChoisissez un objet à utiliser :\n");
    for (int i = 0; i < joueur->item_count; i++) {
        printf("%d - %s (Quantité: %d, Effet: %d)\n", i + 1, joueur->items[i].name, joueur->items[i].quantity, joueur->items[i].effect);
    }
    printf("Entrez le numéro de l'objet : ");
    scanf("%d", &choix);

    if (choix < 1 || choix > joueur->item_count || joueur->items[choix - 1].quantity <= 0) {
        printf("Choix invalide ou objet indisponible !\n");
        return;
    }

    if (strcmp(joueur->items[choix - 1].name, "Rare Candy") == 0) {
        useRareCandy(supemon);
        printf("%s a utilisé %s et a gagné un niveau !\n", supemon->name, joueur->items[choix - 1].name);
    } else {
        supemon->hp += joueur->items[choix - 1].effect;
        if (supemon->hp > supemon->maxHp) supemon->hp = supemon->maxHp;
        printf("%s a utilisé %s et a récupéré %d HP !\n", supemon->name, joueur->items[choix - 1].name, joueur->items[choix - 1].effect);
    }

    joueur->items[choix - 1].quantity--;

   
    if (joueur->items[choix - 1].quantity == 0) {
        for (int i = choix - 1; i < joueur->item_count - 1; i++) {
            joueur->items[i] = joueur->items[i + 1];
        }
        joueur->item_count--;
    }
}

void lancerCombat(Supemon *supemonJoueur, Supemon *supemonSauvage, Player *joueur) {
    printf("\nUn combat commence entre votre %s (Niveau %d, HP %d/%d) et le %s sauvage (Niveau %d, HP %d/%d) !\n",
           supemonJoueur->name, supemonJoueur->level, supemonJoueur->hp, supemonJoueur->maxHp,
           supemonSauvage->name, supemonSauvage->level, supemonSauvage->hp, supemonSauvage->maxHp);

    while (supemonJoueur->hp > 0 && supemonSauvage->hp > 0) {
        printf("\n--- Votre tour ---\n");
        printf("1 - Attaquer avec %s\n", supemonJoueur->attacks[0].name);
        printf("2 - Attaquer avec %s\n", supemonJoueur->attacks[1].name);
        printf("3 - Changer de Supémon\n");
        printf("4 - Utiliser un objet\n");
        printf("5 - Fuir\n");
        printf("6 - Tenter de capturer\n");
        printf("Choisissez une action : ");
        
        int choix;
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                attaquerSupemon(supemonJoueur, supemonSauvage, joueur, 1, 0);
                break;
            case 2:
                attaquerSupemon(supemonJoueur, supemonSauvage, joueur, 1, 1);
                break;
            case 3: {
                Supemon *nouveauSupemon = changerSupemon(joueur);
                if (nouveauSupemon != NULL) {
                    supemonJoueur = nouveauSupemon;
                    printf("Vous avez changé pour %s (Niveau %d, HP %d/%d) !\n",
                           supemonJoueur->name, supemonJoueur->level, supemonJoueur->hp, supemonJoueur->maxHp);
                }
                break;
            }
            case 4:
                utiliserObjet(joueur, supemonJoueur);
                break;
            case 5:
                printf("Vous tentez de fuir...\n");
                if ((rand() % 100) / 100.0 < (float)supemonJoueur->speed / (supemonJoueur->speed + supemonSauvage->speed)) {
                    printf("Vous avez réussi à fuir !\n");
                    return;
                } else {
                    printf("Échec de la fuite !\n");
                }
                break;
            case 6:
                printf("Vous tentez de capturer le Supémon sauvage...\n");
                float chanceCapture = ((float)(supemonSauvage->maxHp - supemonSauvage->hp) / supemonSauvage->maxHp) + 0.3;
                if ((rand() % 100) / 100.0 < chanceCapture) {
                    printf("Vous avez capturé le %s sauvage (Niveau %d, HP %d/%d) !\n",
                           supemonSauvage->name, supemonSauvage->level, supemonSauvage->hp, supemonSauvage->maxHp);
                    joueur->team[joueur->teamSize++] = *supemonSauvage;
                    return;
                } else {
                    printf("La capture a échoué !\n");
                }
                break;
            default:
                printf("Choix invalide !\n");
        }

        if (supemonSauvage->hp > 0) {
            printf("\n--- Tour du Supémon sauvage ---\n");
            attaquerSupemon(supemonSauvage, supemonJoueur, joueur, 0, rand() % 2);
        }
    }

    if (supemonJoueur->hp <= 0) {
        printf("\nVotre %s (Niveau %d, HP %d/%d) est K.O. ! Vous avez perdu le combat.\n",
               supemonJoueur->name, supemonJoueur->level, supemonJoueur->hp, supemonJoueur->maxHp);
    } else {
        printf("\nLe %s sauvage (Niveau %d, HP %d/%d) est K.O. ! Vous avez gagné le combat.\n",
               supemonSauvage->name, supemonSauvage->level, supemonSauvage->hp, supemonSauvage->maxHp);
        int experienceGagnee = (100 + rand() % 401) * supemonSauvage->level; 
        gainExperience(supemonJoueur, experienceGagnee);
        int supcoinsGagnes = 100 + rand() % 401; 
        joueur->supcoins += supcoinsGagnes;
        printf("Vous avez gagné %d Supcoins et %d points d'expérience !\n", supcoinsGagnes, experienceGagnee);
    }
}