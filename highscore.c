#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "game.h"

#define MAX_PLAYERS 100
#define MAX_NAME_LEN	256

struct player_score {
	char name[MAX_NAME_LEN];
	int score;
};

static char namev[MAX_NAME_LEN];

void name(void)
{
	printf("\x1b[2J\x1b[H");
	printf("The name? ");
	scanf("%255s", namev);
}

static int compare_scores(const void *a, const void *b)
{
	const struct player_score *player_a = a;
	const struct player_score *player_b = b;

	return player_b->score - player_a->score;
}

void highscore(void)
{
	struct player_score players[MAX_PLAYERS];
	int found = 0;
	int count = 0;
	FILE *f;
	int i;

	f = fopen("highscore.txt", "r");
	if (f) {
		while (count < MAX_PLAYERS &&
		       fscanf(f, "%255s %d", players[count].name,
			      &players[count].score) == 2)
			count++;
		fclose(f);
	}

	for (i = 0; i < count; i++) {
		if (strcmp(players[i].name, namev) == 0) {
			found = 1;
			if (boss_id+1 > players[i].score)
				players[i].score = boss_id+1;
			break;
		}
	}

	if (!found && count < MAX_PLAYERS && strlen(namev) > 0) {
		strcpy(players[count].name, namev);
		players[count].score = boss_id+1;
		count++;
	}

	qsort(players, count, sizeof(struct player_score), compare_scores);

	f = fopen("highscore.txt", "w");
	if (f) {
		for (i = 0; i < count; i++)
			fprintf(f, "%s %d\n",
				players[i].name, players[i].score);
		fclose(f);
	}

	if (count > 0) {
		if (strcmp(players[0].name, namev) == 0 &&
		    players[0].score == boss_id+1 && !found)
			printf("New record: %s %d\n", namev, boss_id+1);

		printf("High score: %s %d\n",
		       players[0].name, players[0].score);
	}
}
