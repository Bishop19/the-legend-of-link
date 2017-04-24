#ifndef ___ESTADO_H___
#define ___ESTADO_H___

/**
@file estado.h
Definição do estado e das funções que convertem estados em strings e vice-versa
*/

/** \brief O nº máximo de inimigos */
#define MAX_INIMIGOS		100

/** \brief O nº máximo de obstáculos */
#define MAX_OBSTACULOS		100

/**
\brief Estrutura que armazena uma posição
*/
typedef struct posicao {
	char x;
	char y;
} POSICAO; 
/**
\brief Estrutura que armazena uma posição
*/
typedef struct enemyState {
	char x;
	char y;
	char tipo;
	char vida;
	char item;
	char visivel;
	char range;
} ENEMY;



/**
\brief Estrutura que armazena uma posição
*/
typedef struct playerState {
	char x;
	char y;
	char vida;
	char mana;
	char atk;
	char crit;
} PLAYER;

/**
\brief Estrutura que armazena uma posição
*/
typedef struct treasureState {
	char x;
	char y;
	char visivel;
} TREASURE;

typedef struct itemState {
	char x;
	char y;
	char visivel;
	char tipo;
} ITEM;

/**
\brief Estrutura que armazena o estado do jogo
*/
typedef struct estado {
	/** Nivel de jogo*/
	char nivel;
	/** Ação 0-em jogo 1-novo nivel */
	char acao;
	/**Pontuação do jogador */
	int score;
	/** A posição do jogador */
	PLAYER jog;
	/** A posição da porta */
	POSICAO door;
	/** Tesouro que aumenta o score aleatoriamente */
	TREASURE treasure;
	/** Item dropado */
	ITEM item;
	/** O nº de inimigos */
	char num_inimigos;
	/** O nº de obstáculos */
	char num_obstaculos;
	/** Array com a posição dos inimigos */
	ENEMY inimigo[MAX_INIMIGOS];
	/** Array com a posição dos obstáculos */
	POSICAO obstaculo[MAX_OBSTACULOS];
	/** Opção de mostrar casas que os inimigos podem atacar */
	char range;

} ESTADO;

/**
\brief Função que converte um estado numa string
@param e O estado
@returns A string correspondente ao estado e
*/
char *estado2str(ESTADO e);

/**
\brief Função que converte uma string num estado 
@param argumentos Uma string contendo os argumentos passados à CGI
@returns O estado correspondente à string dos argumentos
*/
ESTADO str2estado(char *argumentos);

#endif
