#pragma once

#include "data.h"

#define HAND_SIZE 8
#define DECK_SIZE 40
#define DUNGEON_SIZE 12

struct boss {
	char hp, dp, val, suit;
};

extern struct boss dungeon[DUNGEON_SIZE];

struct card {
	char val, suit;
};

extern list_t *deck;
extern list_t *pile;
extern list_t *hand;

void fill_dungeon();
void fill_deck();
void draw(int n);
void fill(int n);
void use(int id);

void display_info();
