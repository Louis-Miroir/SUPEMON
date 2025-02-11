#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "battle.h"

void startWildBattle(Player *player) {
    if (player->teamSize == 0) {
        printf("Vous n'avez aucun Supémon pour combattre !\n");
        return;
    }

    Supemon supemonSauvage = getRandomPokemon();
    printf("\nUn %s sauvage apparaît !\n", supemonSauvage.name);

    if (player->team[0].hp > 0) { // Supposons que le premier Supémon est actif
        lancerCombat(&player->team[0], &supemonSauvage, player);
    } else {
        printf("Votre Supémon est K.O. !\n");
    }
}

// Fonction d'attaque d'un Supémon contre un autre
void attaquerSupemon(Supemon *attaquant, Supemon *defenseur, Player *joueur, int isWild) {
    float tauxReussite = (float)attaquant->accuracy / (attaquant->accuracy + defenseur->evasion) + 0.1;
    if ((rand() % 100) / 100.0 < tauxReussite) {
        int degats = (attaquant->attack * 3) / defenseur->defense;
        degats = (rand() % 2 == 0) ? degats : degats + 1; // Variation aléatoire des dégâts
        defenseur->hp -= degats;
        if (defenseur->hp < 0) defenseur->hp = 0;
        if (isWild) {
            printf("%s de %s (Niveau: %d, HP: %d/%d) inflige %d points de dégâts à %s sauvage (Niveau: %d, HP: %d/%d) !\n", 
                attaquant->name, joueur->name, attaquant->level, attaquant->hp, attaquant->maxHp, 
                degats, defenseur->name, defenseur->level, defenseur->hp, defenseur->maxHp);
        } else {
            printf("%s sauvage (Niveau: %d, HP: %d/%d) inflige %d points de dégâts à %s de %s (Niveau: %d, HP: %d/%d) !\n", 
                attaquant->name, attaquant->level, attaquant->hp, attaquant->maxHp, 
                degats, defenseur->name, joueur->name, defenseur->level, defenseur->hp, defenseur->maxHp);
        }
    } else {
        if (isWild) {
            printf("%s de %s (Niveau: %d, HP: %d/%d) a raté son attaque !\n", 
                attaquant->name, joueur->name, attaquant->level, attaquant->hp, attaquant->maxHp);
        } else {
            printf("%s sauvage (Niveau: %d, HP: %d/%d) a raté son attaque !\n", 
                attaquant->name, attaquant->level, attaquant->hp, attaquant->maxHp);
        }
    }
}

// Fonction pour changer de Supémon
Supemon* changerSupemon(Player *joueur) {
    int choix;
    printf("\nChoisissez un Supémon pour combattre :\n");
    for (int i = 0; i < joueur->teamSize; i++) {
        printf("%d - %s (HP: %d/%d)\n", i + 1, joueur->team[i].name, joueur->team[i].hp, joueur->team[i].maxHp);
    }
    printf("Entrez le numéro du Supémon : ");
    scanf("%d", &choix);

    if (choix < 1 || choix > joueur->teamSize || joueur->team[choix - 1].hp <= 0) {
        printf("Choix invalide ou Supémon K.O. !\n");
        return NULL;
    }

    return &joueur->team[choix - 1];
}

// Fonction principale pour gérer le combat entre un Supémon du joueur et un Supémon sauvage
void lancerCombat(Supemon *supemonJoueur, Supemon *supemonSauvage, Player *joueur) {
    printf("\nUn combat commence entre votre %s et le %s sauvage !\n", supemonJoueur->name, supemonSauvage->name);

    while (supemonJoueur->hp > 0 && supemonSauvage->hp > 0) {
        printf("\n--- Votre tour ---\n");
        printf("1 - Attaquer\n");
        printf("2 - Changer de Supémon\n");
        printf("3 - Utiliser un objet (Pas encore implémenté)\n");
        printf("4 - Fuir\n");
        printf("5 - Tenter de capturer\n");
        printf("Choisissez une action : ");
        
        int choix;
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                attaquerSupemon(supemonJoueur, supemonSauvage, joueur, 1);
                break;
            case 2: {
                Supemon *nouveauSupemon = changerSupemon(joueur);
                if (nouveauSupemon != NULL) {
                    supemonJoueur = nouveauSupemon;
                    printf("Vous avez changé pour %s !\n", supemonJoueur->name);
                }
                break;
            }
            case 4:
                printf("Vous tentez de fuir...\n");
                if ((rand() % 100) / 100.0 < (float)supemonJoueur->speed / (supemonJoueur->speed + supemonSauvage->speed)) {
                    printf("Vous avez réussi à fuir !\n");
                    return;
                } else {
                    printf("Échec de la fuite !\n");
                }
                break;
            case 5:
                printf("Vous tentez de capturer le Supémon sauvage...\n");
                float chanceCapture = ((float)(supemonSauvage->maxHp - supemonSauvage->hp) / supemonSauvage->maxHp) + 0.3;
                if ((rand() % 100) / 100.0 < chanceCapture) {
                    printf("Vous avez capturé le %s sauvage !\n", supemonSauvage->name);
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
            attaquerSupemon(supemonSauvage, supemonJoueur, joueur, 0);
        }
    }

    if (supemonJoueur->hp <= 0) {
        printf("\nVotre %s est K.O. ! Vous avez perdu le combat.\n", supemonJoueur->name);
    } else {
        printf("\nLe %s sauvage est K.O. ! Vous avez gagné le combat.\n", supemonSauvage->name);
        int experienceGagnee = (100 + rand() % 401) * supemonSauvage->level; 
        gainExperience(supemonJoueur, experienceGagnee);
        int supcoinsGagnes = 100 + rand() % 401; 
        joueur->supcoins += supcoinsGagnes;
        printf("Vous avez gagné %d Supcoins et %d points d'expérience !\n", supcoinsGagnes, experienceGagnee);
    }
}