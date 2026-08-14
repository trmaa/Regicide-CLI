#pragma once

#define HAND_SIZE 8
#define DECK_SIZE 40
#define DUNGEON_SIZE 12

struct boss {
	char hp, dp, suit;
};

extern struct boss dungeon[DUNGEON_SIZE];

struct card {
	char val, suit;
};

extern struct card deck[DECK_SIZE];
extern struct card hand[HAND_SIZE];

void fill_deck();
void draw(int n); // recursive
void use(int id);
