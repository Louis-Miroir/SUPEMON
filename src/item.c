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
    printf("______________________________\n");
    printf("\nWelcome to the Shop!\n");
    printf("You have %d Supcoins.\n", player->supcoins);
    printf("Items available for purchase:\n");
    printf("1. Potion (+5 HP) - 100 Supcoins\n");
    printf("2. Super Potion (+10 HP) - 300 Supcoins\n");
    printf("3. Rare Candy (Level up) - 700 Supcoins\n");
    printf("4. Sell Items\n");
    printf("5. Exit Shop\n");
    printf("______________________________\n");

    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (player->supcoins >= 100) {
                    player->supcoins -= 100;
                    printf("Potion purchased!\n");
                   
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
                sellItem(player);
                break;
            case 5:
                printf("Exiting shop...\n");
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

void sellItem(Player* player) {
    int choice;
    printf("\nChoose an item to sell:\n");
    for (int i = 0; i < player->item_count; i++) {
        printf("%d - %s (Quantity: %d, Sell Price: %d Supcoins)\n", i + 1, player->items[i].name, player->items[i].quantity, player->items[i].price / 2);
    }
    printf("Enter the item number to sell: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > player->item_count || player->items[choice - 1].quantity <= 0) {
        printf("Invalid choice or item not available!\n");
        return;
    }

    player->supcoins += player->items[choice - 1].price / 2;
    player->items[choice - 1].quantity--;

    
    if (player->items[choice - 1].quantity == 0) {
        for (int i = choice - 1; i < player->item_count - 1; i++) {
            player->items[i] = player->items[i + 1];
        }
        player->item_count--;
    }

    printf("Item sold!\n");
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