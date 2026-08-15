#pragma once

struct card {
	char val, suit;
};

typedef struct node {
	struct card top;
	struct node *prev;
	struct node *next;
} deck_t;

deck_t *deck_init();
void deck_free(deck_t *);

void d_pop(deck_t *);
deck_t *d_push(deck_t *, struct card top);
int d_size(struct node *);
struct node *d_at(struct node *, int id);
