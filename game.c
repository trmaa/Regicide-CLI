#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "ui.h"
#include "game.h"

static int boss_id = 0;
struct boss dungeon[DUNGEON_SIZE];

list_t *deck;
list_t *hand;
list_t *pile;

static char suits[] = { 'S', 'D', 'C', 'H' };
static char faces[] = { 'J', 'Q', 'K' };

void fill_dungeon()
{

	for (int l = 0; l < 3; l++)
		for (int s = 0; s < 4; s++) {
			int id = s + l * 4;
			dungeon[id].hp = 20 + 10*l;
			dungeon[id].dp = 10 + 5*l;
			dungeon[id].val = faces[l];
			dungeon[id].suit = suits[s];
		}
}

void fill_deck()
{
	struct card aux[DECK_SIZE];

	for (int s = 0; s < 4; s++)
		for (int n = 0; n < 10; n++) {
			int id = n + s * 10;
			aux[id].val = n+1;
			aux[id].suit = suits[s];
		}
// Shufle aux

	deck = list_init();

	for (int i = 0; i < DECK_SIZE; i++)
		l_push(deck, aux[i]);

	struct node *n = deck;
	while (n != NULL) {
		char str[3] = { n->top.val+'0', n->top.suit, 0 };
		debug(str);
		n = n->prev;
	}

	hand = list_init();
	pile = list_init();
}

void draw(int n)
{
	if (n > 0 && l_size(hand) < HAND_SIZE) {
		l_push(hand, deck->top);
		l_pop(deck);

		draw(--n);
	}
}

void fill(int n)
{
	if (n > 0) {
		int size = l_size(pile);
		if (size < n)
			n = size;

		l_push(deck, pile->top);
		l_pop(pile); // stack, not queue... TODO

		fill(--n);
	}
}

void use(int id)
{
	struct boss *boss = &dungeon[boss_id];
	struct card card;

	struct node *n = l_at(hand, id);
	card = n->top;
	l_push(pile, n->top);
	n->prev->next = n->next;
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

}

void display_info()
{
	int deck_len = l_size(deck);
	deck_dp[0].c = deck_len / 10 + '0';
	deck_dp[1].c = deck_len % 10 + '0';

	struct boss *boss = &dungeon[boss_id];
	boss_dp[0].c = boss->val;
	boss_dp[1].c = boss->suit;
	hp_dp[0].c = boss->hp / 10 + '0';
	hp_dp[1].c = boss->hp % 10 + '0';
	dp_dp[0].c = boss->dp / 10 + '0';
	dp_dp[1].c = boss->dp % 10 + '0';

	struct node *n = hand;
	int i = 0;
	while (n != NULL) {
		card_dp[i][0].c = n->top.val % 10 + '0';
		card_dp[i][1].c = n->top.suit;

		i++;
		n = n->prev;
	}
}

void cleanup()
{
	list_free(deck);
	list_free(hand);
}
