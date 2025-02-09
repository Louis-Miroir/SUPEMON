#include <stdio.h>
#include <string.h>

#define max 50

int main() {
    char playername[max];
    int x;
    
    printf("1. Nouvelle Partie\n2. Charger une Partie\nChoisissez une option : ");
    scanf("%d", &x);
    getchar(); //enleve les probleme de buffer
    
    if (x == 1) { // Correction ici
        printf("Entrez votre nom : "); 
        fgets(playername, max, stdin); //stock le nom au max 
        playername[strcspn(playername, "\n")] = 0; //ca retrourne le premier index qui correspond a n 
        
        printf("\nHello %s!\nWelcome in Supémon World!\n", playername);
        printf("+-------------------------------+\n");
        printf("| Choose your starter Supémon: |\n");
        printf("| 1 - Supmander                |\n");
        printf("| 2 - Supasaur                 |\n");
        printf("| 3 - Supirtle                 |\n");
        printf("+-------------------------------+\n");
        printf("1, 2 or 3: ");
        int starterchoice;
        scanf("%d", &starterchoice);
        
        switch (starterchoice) {
            case 1:
                printf("You chose Supmander!\n");
                break;
            case 2:
                printf("You chose Supasaur!\n");
                break;
            case 3:
                printf("You chose Supirtle!\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } else if (x == 2) {
        printf("Chargement de la partie...\n");
    } else {
        printf("Option invalide!\n");
    }
    
    return 0;
}