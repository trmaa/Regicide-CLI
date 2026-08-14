#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include "ui.h"
#include "game.h"

int boss_id = 0;
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

	deck = list_init();

	for (int i = 0; i < DECK_SIZE; i++)
		deck = l_push(deck, aux[i]);

	hand = list_init();
	pile = list_init();
}

void draw(int n)
{
	if (n > 0 && l_size(hand) < HAND_SIZE && l_size(deck) > 0) {
		hand = l_push(hand, deck->top);
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
		if (n == 0)
			return;

		deck = l_push(deck, pile->top);
		l_pop(pile); // stack, not queue... TODO

		fill(--n);
	}
}

void discard(int id)
{
	if (id < 0 || id >= l_size(hand))
		return;

	struct node *n = l_at(hand, id);
	pile = l_push(pile, n->top);
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

	if (id < 0 || id >= l_size(hand))
		return;

	struct node *n = l_at(hand, id);
	card = n->top;
	pile = l_push(pile, n->top);

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

	switch (boss->suit) {
	case 'S':
		boss_dp[0].col = COL(0x77AAFF);
		boss_dp[1].col = COL(0x77AAFF);
		break;
	case 'D':
		boss_dp[0].col = COL(0xFFAA77);
		boss_dp[1].col = COL(0xFFAA77);
		break;
	case 'C':
		boss_dp[0].col = COL(0x77FFAA);
		boss_dp[1].col = COL(0x77FFAA);
		break;
	case 'H':
		boss_dp[0].col = COL(0xFF77AA);
		boss_dp[1].col = COL(0xFF77AA);
		break;
	}

	struct node *n = hand;
	int i = 0;
	while (n->prev != NULL) {
		card_dp[i][0].c = n->top.val % 10 + '0';
		card_dp[i][1].c = n->top.suit;

		switch (n->top.suit) {
		case 'S':
			card_dp[i][0].col = COL(0x77AAFF);
			card_dp[i][1].col = COL(0x77AAFF);
			break;
		case 'D':
			card_dp[i][0].col = COL(0xFFAA77);
			card_dp[i][1].col = COL(0xFFAA77);
			break;
		case 'C':
			card_dp[i][0].col = COL(0x77FFAA);
			card_dp[i][1].col = COL(0x77FFAA);
			break;
		case 'H':
			card_dp[i][0].col = COL(0xFF77AA);
			card_dp[i][1].col = COL(0xFF77AA);
			break;
		}

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
	list_free(deck);
	list_free(hand);
}
