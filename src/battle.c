#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "battle.h"
#include "supemon.h"

extern Player player; // On utilise le joueur global défini ailleurs

void startWildBattle() {
    if (player.team_size == 0) {
        printf("Vous n'avez aucun Supémon pour combattre !\n");
        return;
    }

    supemon supemonSauvage = getRandomPokemon();
    
    // Ajuster le niveau du Supémon sauvage pour correspondre à celui du joueur
    supemonSauvage.level = player.team[0].level;

    printf("\nUn %s sauvage apparaît ! (Niveau %d)\n", supemonSauvage.name, supemonSauvage.level);

    if (player.team[0].hp > 0) { // Vérifie si le premier Supémon est en état de combattre
        lancerCombat(&player.team[0], &supemonSauvage, &player);
    } else {
        printf("Votre Supémon est K.O. !\n");
    }
}

// Fonction d'attaque d'un Supémon contre un autre
void attaquerSupemon(supemon *attaquant, supemon *defenseur) {
    float tauxReussite = (float)attaquant->accuracy / (attaquant->accuracy + defenseur->evasion) + 0.1;
    if ((rand() % 100) / 100.0 < tauxReussite) {
        int degats = (attaquant->attack * 3) / defenseur->defense;
        degats = (rand() % 2 == 0) ? degats : degats + 1; // Variation aléatoire des dégâts
        defenseur->hp -= degats;
        if (defenseur->hp < 0) defenseur->hp = 0;
        printf("%s inflige %d points de dégâts à %s ! %s a maintenant %d PV.\n", 
                attaquant->name, degats, defenseur->name, defenseur->name, defenseur->hp);
    } else {
        printf("%s a raté son attaque !\n", attaquant->name);
    }
}

// Fonction principale pour gérer le combat entre un Supémon du joueur et un Supémon sauvage
void lancerCombat(supemon *supemonJoueur, supemon *supemonSauvage, Player *joueur) {
    printf("\nUn combat commence entre votre %s et le %s sauvage !\n", supemonJoueur->name, supemonSauvage->name);

    while (supemonJoueur->hp > 0 && supemonSauvage->hp > 0) {
        printf("\n--- Votre tour ---\n");
        printf("1 - Attaquer\n");
        printf("2 - Changer de Supémon (Pas encore implémenté)\n");
        printf("3 - Utiliser un objet (Pas encore implémenté)\n");
        printf("4 - Fuir\n");
        printf("5 - Tenter de capturer\n");
        printf("Choisissez une action : ");
        
        int choix;
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                attaquerSupemon(supemonJoueur, supemonSauvage);
                break;
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
                float chanceCapture = ((float)(supemonSauvage->max_hp - supemonSauvage->hp) / supemonSauvage->max_hp) + 0.3;
                if ((rand() % 100) / 100.0 < chanceCapture) {
                    printf("Vous avez capturé le %s sauvage !\n", supemonSauvage->name);
                    // Ajouter le Supémon capturé à l'équipe du joueur (à implémenter)
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
            attaquerSupemon(supemonSauvage, supemonJoueur);
        }
    }

    if (supemonSauvage->hp == 0) {
        printf("\nLe %s sauvage est K.O. ! Vous avez gagné le combat.\n", supemonSauvage->name);
        
        // Calcul de l'expérience gagnée
        int expGagnee = (supemonSauvage->level + 1) * 500;  
        printf("%s gagne %d points d'expérience !\n", supemonJoueur->name, expGagnee);
        
        // Ajouter l'expérience et vérifier si un niveau est gagné
        ajouterExperience(supemonJoueur, expGagnee);
    }
}
