#ifndef ___ESTADO_H___
#define ___ESTADO_H___

/**
@file estado.h
Definição do estado e das funções que convertem estados em strings e vice-versa
*/

/** \brief O nº máximo de inimigos */
#define MAX_INIMIGOS		20

/** \brief O nº máximo de obstáculos */
#define MAX_OBSTACULOS		20

/**
\brief Estrutura que armazena uma posição
*/
typedef struct posicao {
	char x;
	char y;
} POSICAO; 
/**
\brief Estrutura que armazena informação de um inimigo.
*/
typedef struct enemyState {
	char x;
	char y;
	char tipo;
	char vida;
	char atk;
	char item;
	char visivel;
	char range;
	char showVida;
} ENEMY;



/**
\brief Estrutura que armazena informação do jogador.
*/
typedef struct playerState {
	char x;
	char y;
	char vida;
	char mana;
	char atk;
	char crit;
	char item_vida;
	char item_mana;
	char item_sword;
	char item_shield;
	char powerUp_sword;
	char powerUp_shield;
} PLAYER;

/**
\brief Estrutura que armazena informação sobre o tesouro.
*/
typedef struct treasureState {
	char x;
	char y;
	char visivel;
} TREASURE;

/**
\brief Estrutura que armazena informação sobre o item dropado pelo tesouros.
*/
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
	/** Momento em que o jogo se encontra */
	char screen;
	/** Indicador da utilização do Power Up "Bola de Fogo" */
	char bolaFogo;
	/** Indicador da ultilização do Power Up "Flash*/
	char flash;
	/**Pontuação do jogador */
	int score;
	/** A posição do jogador */
	PLAYER jog;
	/** A posição da porta */
	POSICAO door;
	/** Tesouro que contém um item*/
	TREASURE treasure;
	/** Item dropado pelo tesouro */
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
	/** Opção de mostrar a vida dos inimigos */
	char vidas;
	/** Indicativo que o jogador se encontra sem mana */
	char noMana;

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
