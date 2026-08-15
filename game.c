#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include "ui.h"
#include "game.h"
#include "gfx.h"

int boss_id = 0;
struct boss dungeon[DUNGEON_SIZE];

deck_t *deck;
deck_t *hand;
deck_t *pile;

static char suits[] = { 'S', 'D', 'C', 'H' };
static char faces[] = { 'J', 'Q', 'K' };

void fill_dungeon()
{
	for (int l = 0; l < 3; l++)
		for (int s = 0; s < 4; s++) {
			int id = s + l * 4;
			dungeon[id].hp = 10 + 10*l;
			dungeon[id].dp = 5 + 5*l;
			dungeon[id].val = faces[l];
			dungeon[id].suit = suits[s];
		}

	srand(time(NULL));
	for (int k = 0; k < 3; k++)
		for (int i = 3; i > 0; i--) {
			int j = rand() % (i + 1) + 4*k;
			struct boss tmp = dungeon[i+4*k];
			dungeon[i+4*k] = dungeon[j];
			dungeon[j] = tmp;
		}
}

void fill_deck()
{
	struct card aux[DECK_SIZE];

	srand(time(NULL));

	for (int s = 0; s < 4; s++)
		for (int n = 0; n < 10; n++) {
			int id = n + s * 10;
			aux[id].val = n+1;
			aux[id].suit = suits[s];
		}

	for (int i = DECK_SIZE - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		struct card tmp = aux[i];
		aux[i] = aux[j];
		aux[j] = tmp;
	}

	deck = deck_init();

	for (int i = 0; i < DECK_SIZE; i++)
		deck = d_push(deck, aux[i]);

	hand = deck_init();
	pile = deck_init();
}

void draw(int n)
{
	if (n > 0 && d_size(hand) < HAND_SIZE && d_size(deck) > 0) {
		hand = d_push(hand, deck->top);
		d_pop(deck);

		draw(--n);
	}
}

void fill(int n)
{
	if (n > 0) {
		int size = d_size(pile);
		if (size < n)
			n = size;
		if (n == 0)
			return;

		deck = d_push(deck, pile->top);
		d_pop(pile); // stack, not queue... TODO

		fill(--n);
	}
}

void discard(int id)
{
	if (id < 0 || id >= d_size(hand))
		return;

	struct node *n = d_at(hand, id);
	pile = d_push(pile, n->top);
	if (n == hand)
		hand = n->prev;
	if (n->prev != NULL)
		n->prev->next = n->next;
	if (n->next != NULL)
		n->next->prev = n->prev;
	free(n);
}

void use(int id)
{
	struct boss *boss = &dungeon[boss_id];
	struct card card;

	if (id < 0 || id >= d_size(hand))
		return;

	struct node *n = d_at(hand, id);
	card = n->top;
	pile = d_push(pile, n->top);

	if (n == hand)
		hand = n->prev;
	if (n->prev != NULL)
		n->prev->next = n->next;
	if (n->next != NULL)
		n->next->prev = n->prev;
	free(n);

	if (card.suit != boss->suit) {
		switch (card.suit) {
		case 'S':
			boss->dp -= card.val;
			break;
		case 'D':
			fill(card.val);
			break;
		case 'C':
			card.val *= 2;
			break;
		case 'H':
			draw(card.val);
			break;
		}
	}

	boss->hp -= card.val;

	if (boss->dp < 0)
		boss->dp = 0;
}

static struct col
suit_col(char suit)
{
	struct col col;
	switch (suit) {
	case 'S':
		col = COL(0x77AAFF);
		break;
	case 'D':
		col = COL(0xFFAA77);
		break;
	case 'C':
		col = COL(0x77FFAA);
		break;
	case 'H':
		col = COL(0xFF77AA);
		break;
	}
	return col;
}

void display_info()
{
	int deck_len = d_size(deck);
	deck_dp[0].c = deck_len / 10 + '0';
	deck_dp[1].c = deck_len % 10 + '0';

	struct boss *boss = &dungeon[boss_id];
	bossid_dp[0].c = (1 + boss_id) / 10 + '0';
	bossid_dp[1].c = (1 + boss_id) % 10 + '0';
	boss_dp[0].c = boss->val;
	boss_dp[1].c = boss->suit;
	hp_dp[0].c = boss->hp / 10 + '0';
	hp_dp[1].c = boss->hp % 10 + '0';
	dp_dp[0].c = boss->dp / 10 + '0';
	dp_dp[1].c = boss->dp % 10 + '0';

	boss_dp[0].col = suit_col(boss->suit);
	boss_dp[1].col = suit_col(boss->suit);

	struct node *n = hand;
	int i = 0;
	while (n->prev != NULL) {
		card_dp[i][0].c = n->top.val % 10 + '0';
		card_dp[i][1].c = n->top.suit;

		card_dp[i][0].col = suit_col(n->top.suit);
		card_dp[i][1].col = suit_col(n->top.suit);

		i++;
		n = n->prev;
	}
	for (; i < HAND_SIZE; i++) {
		card_dp[i][0].c = 'X';
		card_dp[i][1].c = 'X';
		card_dp[i][0].col = COL(0x222222);
		card_dp[i][1].col = COL(0x222222);
	}
}

void cleanup()
{
	deck_free(deck);
	deck_free(hand);
}
