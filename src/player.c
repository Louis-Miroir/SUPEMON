#include <stdio.h>
#include <string.h>
#include "player.h"

void createPlayer(Player *player) {
    printf("Enter your name: ");
    scanf("%s", player->name);
    player->supcoins = 1000;  
    player->teamSize = 0;
    player->item_count = 0;
    
    for (int i = 0; i < 6; i++) {
        player->team[i].hp = 0;
    }
    for (int i = 0; i < MAX_ITEMS; i++) {
        strcpy(player->items[i].name, "");
        player->items[i].price = 0;
        player->items[i].effect = 0;
    }
}