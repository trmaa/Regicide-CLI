#pragma once

struct card {
	char val, suit;
};

typedef struct node {
	struct card top;
	struct node *prev;
	struct node *next;
} list_t;

list_t *list_init();
void list_free(list_t *);

void l_pop(list_t *);
list_t *l_push(list_t *, struct card top);
int l_size(struct node *);
struct node *l_at(struct node *, int id);
