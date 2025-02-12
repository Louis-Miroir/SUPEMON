#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "battle.h"
#include "item.h"

void startWildBattle(Player *player) {
    if (player->teamSize == 0) {
        printf("You have no Supémon to fight!\n");
        return;
    }

    Supemon supemonSauvage = getRandomPokemon(player->team[0].level);
    printf("\nA wild %s appears!\n", supemonSauvage.name);

    if (player->team[0].hp > 0) {
        lancerCombat(&player->team[0], &supemonSauvage, player);
    } else {
        printf("Your Supémon is K.O.!\n");
    }
}

void attaquerSupemon(Supemon *attaquant, Supemon *defenseur, Player *joueur, int isWild, int attackIndex) {
    Attack attack = attaquant->attacks[attackIndex];
    if (attack.damage > 0) {
        int degats = attack.damage + attaquant->attack - defenseur->defense;
        if (degats < 0) degats = 0;
        defenseur->hp -= degats;
        if (defenseur->hp < 0) defenseur->hp = 0;
        printf("%s (Level %d, HP %d/%d) uses %s and deals %d damage to %s (Level %d, HP %d/%d)!\n",
               attaquant->name, attaquant->level, attaquant->hp, attaquant->maxHp,
               attack.name, degats,
               defenseur->name, defenseur->level, defenseur->hp, defenseur->maxHp);
    }
    if (attack.effect == 1) {
        attaquant->attack++;
        printf("%s (Level %d, HP %d/%d) uses %s and increases its attack!\n",
               attaquant->name, attaquant->level, attaquant->hp, attaquant->maxHp, attack.name);
    } else if (attack.effect == 2) {
        attaquant->evasion++;
        printf("%s (Level %d, HP %d/%d) uses %s and increases its evasion!\n",
               attaquant->name, attaquant->level, attaquant->hp, attaquant->maxHp, attack.name);
    } else if (attack.effect == 3) {
        attaquant->defense++;
        printf("%s (Level %d, HP %d/%d) uses %s and increases its defense!\n",
               attaquant->name, attaquant->level, attaquant->hp, attaquant->maxHp, attack.name);
    }
}

Supemon* changerSupemon(Player *joueur) {
    int choix;
    printf("\nChoose a Supémon to fight:\n");
    for (int i = 0; i < joueur->teamSize; i++) {
        printf("%d - %s (Level %d, HP %d/%d)\n", i + 1, joueur->team[i].name, joueur->team[i].level, joueur->team[i].hp, joueur->team[i].maxHp);
    }
    printf("Enter the number of the Supémon: ");
    scanf("%d", &choix);

    if (choix < 1 || choix > joueur->teamSize || joueur->team[choix - 1].hp <= 0) {
        printf("Invalid choice or Supémon is K.O.!\n");
        return NULL;
    }

    return &joueur->team[choix - 1];
}

void utiliserObjet(Player *joueur, Supemon *supemon) {
    int choix;
    printf("\nChoose an item to use:\n");
    for (int i = 0; i < joueur->item_count; i++) {
        printf("%d - %s (Quantity: %d, Effect: %d)\n", i + 1, joueur->items[i].name, joueur->items[i].quantity, joueur->items[i].effect);
    }
    printf("Enter the number of the item: ");
    scanf("%d", &choix);

    if (choix < 1 || choix > joueur->item_count || joueur->items[choix - 1].quantity <= 0) {
        printf("Invalid choice or item not available!\n");
        return;
    }

    if (strcmp(joueur->items[choix - 1].name, "Rare Candy") == 0) {
        useRareCandy(supemon);
        printf("%s used %s and gained a level!\n", supemon->name, joueur->items[choix - 1].name);
    } else {
        supemon->hp += joueur->items[choix - 1].effect;
        if (supemon->hp > supemon->maxHp) supemon->hp = supemon->maxHp;
        printf("%s used %s and recovered %d HP!\n", supemon->name, joueur->items[choix - 1].name, joueur->items[choix - 1].effect);
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
    printf("\nA battle begins between your %s (Level %d, HP %d/%d) and the wild %s (Level %d, HP %d/%d)!\n",
           supemonJoueur->name, supemonJoueur->level, supemonJoueur->hp, supemonJoueur->maxHp,
           supemonSauvage->name, supemonSauvage->level, supemonSauvage->hp, supemonSauvage->maxHp);

    while (supemonJoueur->hp > 0 && supemonSauvage->hp > 0) {
        printf("\n--- Your turn ---\n");
        printf("1 - Attack with %s\n", supemonJoueur->attacks[0].name);
        printf("2 - Attack with %s\n", supemonJoueur->attacks[1].name);
        printf("3 - Switch Supémon\n");
        printf("4 - Use an item\n");
        printf("5 - Run away\n");
        printf("6 - Attempt to capture\n");
        printf("Choose an action:\n");
        printf("______________________________\n");
        
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
                    printf("You switched to %s (Level %d, HP %d/%d)!\n",
                           supemonJoueur->name, supemonJoueur->level, supemonJoueur->hp, supemonJoueur->maxHp);
                }
                break;
            }
            case 4:
                utiliserObjet(joueur, supemonJoueur);
                break;
            case 5:
                printf("You attempt to run away...\n");
                if ((rand() % 100) / 100.0 < (float)supemonJoueur->speed / (supemonJoueur->speed + supemonSauvage->speed)) {
                    printf("You successfully ran away!\n");
                    return;
                } else {
                    printf("Failed to run away!\n");
                }
                break;
            case 6:
                printf("You are trying to capture the wild Supémon...\n");
                float chanceCapture = ((float)(supemonSauvage->maxHp - supemonSauvage->hp) / supemonSauvage->maxHp) + 0.3;
                if ((rand() % 100) / 100.0 < chanceCapture) {
                    printf("You have captured the wild %s (Level %d, HP %d/%d)!\n",
                           supemonSauvage->name, supemonSauvage->level, supemonSauvage->hp, supemonSauvage->maxHp);
                    joueur->team[joueur->teamSize++] = *supemonSauvage;
                    return;
                } else {
                    printf("The capture failed!\n");
                }
                break;
            default:
                printf("Invalid choice!\n");
        }

        if (supemonSauvage->hp > 0) {
            printf("\n--- Wild Supémon's Turn ---\n");
            attaquerSupemon(supemonSauvage, supemonJoueur, joueur, 0, rand() % 2);
        }
    }

    if (supemonJoueur->hp <= 0) {
        printf("\nYour %s (Level %d, HP %d/%d) is K.O.! You lost the fight.\n",
               supemonJoueur->name, supemonJoueur->level, supemonJoueur->hp, supemonJoueur->maxHp);
    } else {
        printf("\nThe wild %s (Level %d, HP %d/%d) is K.O.! You won the fight.\n",
               supemonSauvage->name, supemonSauvage->level, supemonSauvage->hp, supemonSauvage->maxHp);
        int experienceGagnee = (100 + rand() % 401) * supemonSauvage->level; 
        gainExperience(supemonJoueur, experienceGagnee);
        int supcoinsGagnes = 100 + rand() % 401; 
        joueur->supcoins += supcoinsGagnes;
        printf("You earned %d Supcoins and %d XP!\n", supcoinsGagnes, experienceGagnee);
    }
}