#include <stdlib.h>
#include "data.h"

list_t *list_init()
{
	list_t *o;

	o = malloc(sizeof (struct node));
	o->top = (struct card){ -1, -1 };
	o->prev = NULL;
	o->next = NULL;

	return o;
}

void list_free(list_t *self)
{
	while (self->prev != NULL)
		l_pop(self);

	free(self);
	self = NULL;
}

void l_pop(list_t *self)
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

list_t *l_push(list_t *self, struct card val)
{
	struct node *next = malloc(sizeof (struct node));
	self->next = next;
	next->prev = self;
	next->next = NULL;
	next->top = val;

	return next;
}

struct node *l_at(struct node *n, int id)
{
	if (id == 0)
		return n;

	return l_at(n->prev, --id);
}

static void
size_aux(struct node *n, int *c)
{
	if (n->prev == NULL)
		return;

	(*c)++;
	size_aux(n->prev, c);
}

int l_size(struct node *n)
{
	int count = 0;
	size_aux(n, &count);
	return count;
}
