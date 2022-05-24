#include <stdio.h>
#include <stdlib.h>

#define SIZE 8

int is_ok(int *board, int order) {
	for(int i=0;i<order;i++)
		if((board[order] == board[i]) ||
			(board[order] == (board[i] << (order-i))) ||
			(board[order] == (board[i] >> (order-i))))
			return 0;
	return 1;
}

void write_solution(int *board) {
	static int cnt = 1;
	register int i,j;
	fprintf(stdout, "\n\n\tCozum %d\n\n", cnt++);

	for(i=0;i<SIZE;i++) {
		fprintf(stdout, "\t");
		for(j=(1 << (SIZE-1));j>0;j >>= 1)
			fprintf(stdout, "|%c", board[i] == j ? 'V' : '.');
		fprintf(stdout, "|\n");
	}
}

void place_queen(int *board, int order) {
	if(order == SIZE)
		write_solution(board);
	else {
		for(board[order] = 1;board[order] < (1<<SIZE);board[order] <<= 1)
			if(is_ok(board, order))
				place_queen(board, order+1);
	}
}

int main(void) {
	int board[SIZE];
	place_queen(board, 0);
}
