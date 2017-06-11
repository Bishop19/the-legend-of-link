/**
@file highScore.h
Funções responsaveis pelos melhores scores.
*/

/** \brief Estrutura que armazena o score que um jogador alcançou.*/
typedef struct scores {
	char nome[20];
	int score;
} SCORE;

/** \brief Função que guarda ordenadamente a pontuação do jogador num array de scores.

	@param *jogador - Nome do jogador.
	@param new_score - Score a guardar.
*/
void guardar_Score(char *jogador, int new_score);

/** \brief Função que imprime os melhores scores.*/
void print_score();
