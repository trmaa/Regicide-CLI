#include <stdlib.h>
#include "deck.h"

deck_t *deck_init()
{
	deck_t *o;

	o = malloc(sizeof (struct node));
	o->top = (struct card){ -1, -1 };
	o->prev = NULL;
	o->next = NULL;

	return o;
}

void deck_free(deck_t *self)
{
	while (self->prev != NULL)
		d_pop(self);

	free(self);
	self = NULL;
}

void d_pop(deck_t *self)
{
	if (self->prev == NULL)
		return;

	struct node *aux = self->prev;
	self->top = aux->top;
	self->prev = aux->prev;
	self->next = NULL;
	if (aux->prev != NULL)
		aux->prev->next = self;
	free(aux);
}

deck_t *d_push(deck_t *self, struct card val)
{
	struct node *next = malloc(sizeof (struct node));
	self->next = next;
	next->prev = self;
	next->next = NULL;
	next->top = val;

	return next;
}

struct node *d_at(struct node *n, int id)
{
	if (n == NULL)
		return NULL;

	if (id == 0)
		return n;

	return d_at(n->prev, --id);
}

static void
size_aux(struct node *n, int *c)
{
	if (n->prev == NULL)
		return;

	(*c)++;
	size_aux(n->prev, c);
}

int d_size(struct node *n)
{
	int count = 0;
	size_aux(n, &count);
	return count;
}
