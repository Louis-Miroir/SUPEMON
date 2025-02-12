#include <stdio.h>
#include <string.h>
#include "player.h"
#include "item.h"

void useRareCandy(Supemon *supemon) {
    int experienceToNextLevel = 500 + (supemon->level - 1) * 1000;
    supemon->experience += experienceToNextLevel;
    gainExperience(supemon, 0); 
}

void openShop(Player* player) {
    int choice;
    printf("\nWelcome to the Shop!\n");
    printf("You have %d Supcoins.\n", player->supcoins);
    printf("Items available for purchase:\n");
    printf("1. Potion (+5 HP) - 100 Supcoins\n");
    printf("2. Super Potion (+10 HP) - 300 Supcoins\n");
    printf("3. Rare Candy (Level up) - 700 Supcoins\n");
    printf("4. Exit Shop\n");

    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (player->supcoins >= 100) {
                    player->supcoins -= 100;
                    printf("Potion purchased!\n");
                    // Ajouter l'objet à l'inventaire
                    int found = 0;
                    for (int i = 0; i < player->item_count; i++) {
                        if (strcmp(player->items[i].name, "Potion") == 0) {
                            player->items[i].quantity++;
                            found = 1;
                            break;
                        }
                    }
                    if (!found && player->item_count < MAX_ITEMS) {
                        strcpy(player->items[player->item_count].name, "Potion");
                        player->items[player->item_count].price = 100;
                        player->items[player->item_count].effect = 5;
                        player->items[player->item_count].quantity = 1;
                        player->item_count++;
                    }
                } else {
                    printf("Not enough Supcoins!\n");
                }
                break;
            case 2:
                if (player->supcoins >= 300) {
                    player->supcoins -= 300;
                    printf("Super Potion purchased!\n");
                    // Ajouter l'objet à l'inventaire
                    int found = 0;
                    for (int i = 0; i < player->item_count; i++) {
                        if (strcmp(player->items[i].name, "Super Potion") == 0) {
                            player->items[i].quantity++;
                            found = 1;
                            break;
                        }
                    }
                    if (!found && player->item_count < MAX_ITEMS) {
                        strcpy(player->items[player->item_count].name, "Super Potion");
                        player->items[player->item_count].price = 300;
                        player->items[player->item_count].effect = 10;
                        player->items[player->item_count].quantity = 1;
                        player->item_count++;
                    }
                } else {
                    printf("Not enough Supcoins!\n");
                }
                break;
            case 3:
                if (player->supcoins >= 700) {
                    player->supcoins -= 700;
                    printf("Rare Candy purchased!\n");
                    // Ajouter l'objet à l'inventaire
                    int found = 0;
                    for (int i = 0; i < player->item_count; i++) {
                        if (strcmp(player->items[i].name, "Rare Candy") == 0) {
                            player->items[i].quantity++;
                            found = 1;
                            break;
                        }
                    }
                    if (!found && player->item_count < MAX_ITEMS) {
                        strcpy(player->items[player->item_count].name, "Rare Candy");
                        player->items[player->item_count].price = 700;
                        player->items[player->item_count].effect = 1;
                        player->items[player->item_count].quantity = 1;
                        player->item_count++;
                    }
                } else {
                    printf("Not enough Supcoins!\n");
                }
                break;
            case 4:
                printf("Exiting shop...\n");
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

void openSupemonCenter(Player* player) {
    printf("\nWelcome to the Supémon Center!\n");
    for (int i = 0; i < player->teamSize; i++) {
        if (player->team[i].hp < player->team[i].maxHp) {
            player->team[i].hp = player->team[i].maxHp;
            printf("%s has been healed to full HP!\n", player->team[i].name);
        } else {
            printf("%s is already at full HP!\n", player->team[i].name);
        }
    }
    printf("\nAll your Supémons have been healed!\n");
}