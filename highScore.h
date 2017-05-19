typedef struct scores {
	char nome[20];
	int score;
} SCORE;


void guardar_Score(char *jogador, int new_score);
void print_score();