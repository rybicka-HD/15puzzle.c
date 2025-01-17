#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MOVES 255

void display(char board[4][4][3]) {
	for (int i = 0; i < 4; i++) {
		printf("%s %s %s %s\n", board[i][0], board[i][1], board[i][2], board[i][3]);
	}
}

int main(void) {
	system("clear");
	printf("--------15puzzle.c---------\n\n");
	printf("instructions:\n");
	printf("type one or more single-letter commands into the prompt\n");
	printf("these commands are:\n");
	printf(" w - move tile up\n");
	printf(" s - move tile down\n");
	printf(" a - move tile left\n");
	printf(" d - move tile right\n");
	printf(" h - print this help\n");
	printf(" q - quit\n\n");

	char board[4][4][3];
	memcpy(board, (char[4][4][3]){
		{" 1", " 2", " 3", " 4"},
		{" 5", " 6", " 7", " 8"},
		{" 9", "10", "11", "12"},
		{"13", "14", "15", "  "}
	}, 4*4*3);

	int spacex = 3;
	int spacey = 3;

	int moves_counter = 0;
	int moves_len = 0;
	char moves[MOVES<64 ? 64 : MOVES];

	srand(time(NULL));
	for (int i = 0; i < MOVES; i++) {
		moves[i] = "wsad"[rand() % 4];
	}

	moves_counter = MOVES;
	moves_len = MOVES;

	char inputbuf[64];
	char input;
	while (1) {
		if (moves_counter != 0) {
			input = moves[moves_len-moves_counter];
			moves_counter--;
		} else {
			display(board);

			printf("> ");
			fgets(inputbuf, sizeof(inputbuf), stdin);
			input = inputbuf[0];
			if (strlen(inputbuf) > 2) {
				memcpy(moves, inputbuf+1, strlen(inputbuf)-1);
				moves_counter = strlen(inputbuf)-2;
				moves_len = strlen(inputbuf)-2;
			}

			system("clear");
			printf("> %s\n\n", inputbuf);
		}

		switch (input) {
			case 'w':
				if (spacex < 0 || spacex > 3 || spacey < 0 || spacey+1 > 3) break;
				strcpy(board[spacey][spacex], board[spacey+1][spacex]);
				strcpy(board[spacey+1][spacex], "  ");
				spacey++;
				break;
			case 's':
				if (spacex < 0 || spacex > 3 || spacey-1 < 0 || spacey > 3) break;
				strcpy(board[spacey][spacex], board[spacey-1][spacex]);
				strcpy(board[spacey-1][spacex], "  ");
				spacey--;
				break;
			case 'a':
				if (spacex < 0 || spacex+1 > 3 || spacey < 0 || spacey > 3) break;
				strcpy(board[spacey][spacex], board[spacey][spacex+1]);
				strcpy(board[spacey][spacex+1], "  ");
				spacex++;
				break;
			case 'd':
				if (spacex-1 < 0 || spacex > 3 || spacey < 0 || spacey > 3) break;
				strcpy(board[spacey][spacex], board[spacey][spacex-1]);
				strcpy(board[spacey][spacex-1], "  ");
				spacex--;
				break;
			case 'q':
				printf("are you sure you want to quit? [y/n] ");
				fgets(inputbuf, sizeof(inputbuf), stdin);

				if (inputbuf[0] == 'y' || inputbuf[0] == 'Y') {
					system("clear");
					goto quit;
				} else {
					system("clear");
					break;
				}
			default:
				printf("unknown command: %c\n", input);
				printf("valid commands are:\n");
				goto help;
			case 'h':
				printf("type one or more single-letter commands into the prompt\n");
				printf("these commands are:\n");
			
			help:
				printf(" w - move tile up\n");
				printf(" s - move tile down\n");
				printf(" a - move tile left\n");
				printf(" d - move tile right\n");
				printf(" h - print this help\n");
				printf(" q - quit\n\n");
				break;
		}

		if (memcmp(board, (char[4][4][3]){
			{" 1", " 2", " 3", " 4"},
			{" 5", " 6", " 7", " 8"},
			{" 9", "10", "11", "12"},
			{"13", "14", "15", "  "}
		}, 4*4*3) == 0) {
			if (moves_counter == 0) {
				display(board);
				printf("congratulations!\n");
				break;
			}
		}

	}
	quit:
	
	return 0;
}
