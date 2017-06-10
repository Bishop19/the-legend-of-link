#ifndef ___PARSER_H___
#include "estado.h"
#define ___PARSER_H___

#define SIZE 10
#define TAM 60
#define NUM_INIMIGOS 10
#define NUM_OBSTACULOS 20

#define PLAYER "http://127.0.0.1/imagens/player.png"
#define ENEMY "http://127.0.0.1/imagens/enemy1.png"
#define ENEMY2 "http://127.0.0.1/imagens/enemy2.png"
#define ENEMY3 "http://127.0.0.1/imagens/enemy3.png"
#define ENEMY5 "http://127.0.0.1/imagens/enemy5.png"
#define ENEMY6 "http://127.0.0.1/imagens/enemy6.png"
#define ENEMY7 "http://127.0.0.1/imagens/enemy7.png"
#define BOSS1 "http://127.0.0.1/imagens/boss1.png"
#define BOSS2 "http://127.0.0.1/imagens/boss2.png"
#define WALL "http://127.0.0.1/imagens/wall.png"
#define WALL2 "http://127.0.0.1/imagens/wall2.png"
#define DOOR "http://127.0.0.1/imagens/door.png"
#define RANGEMOV "http://127.0.0.1/imagens/rangeMove.png"
#define RANGEATTACK "http://127.0.0.1/imagens/rangeAttack.png"
#define TREASURE "http://127.0.0.1/imagens/tesouro.png"
#define VIDA "http://127.0.0.1/imagens/vida.png"
#define VIDADROP "http://127.0.0.1/imagens/vida_Drop.png"
#define MANA "http://127.0.0.1/imagens/mana.png"
#define MANADROP "http://127.0.0.1/imagens/mana_Drop.png"
#define SWORD "http://127.0.0.1/imagens/sword.png"
#define CRIT "http://127.0.0.1/imagens/crit.png"
#define SCORE_5 "http://127.0.0.1/imagens/score5.png"
#define SCORE_10 "http://127.0.0.1/imagens/score10.png"
#define SCORE_25 "http://127.0.0.1/imagens/score25.png"
#define VIDA_INIMIGO "http://127.0.0.1/imagens/vida_inimigo.png"
#define HEX_FLOOR "http://127.0.0.1/imagens/floor_hex.png"
#define HEX_FLOOR_GRASS "http://127.0.0.1/imagens/floor_hex_grass.png"
#define SHIELD_PU "http://127.0.0.1/imagens/shield.png"
#define SWORD_PU "http://127.0.0.1/imagens/sword_PU.png"
#define SWORD_PU_INV "http://127.0.0.1/imagens/sword_PU_inv.png"
#define SHIELD_PU_INV "http://127.0.0.1/imagens/shield_inv.png"
#define VIDA_INV "http://127.0.0.1/imagens/vida_inv.png"
#define MANA_INV "http://127.0.0.1/imagens/mana_inv.png"
#define MENU "http://127.0.0.1/imagens/menu1.png"
#define MENU2 "http://127.0.0.1/imagens/menu2.png"
#define TITLE "http://127.0.0.1/imagens/Title_Screen.png"
#define START_BUTTON "http://127.0.0.1/imagens/start_button.png"
#define BACK_BUTTON "http://127.0.0.1/imagens/back_button.png"
#define SQUARE_LINK "http://127.0.0.1/imagens/square_link.png"
#define TOGGLE_RANGE "http://127.0.0.1/imagens/toggle_range.png"
#define TOGGLE_VIDA "http://127.0.0.1/imagens/toggle_vida.png"
#define TOPSCORE_BUTTON "http://127.0.0.1/imagens/topScore_button.png"
#define BOSS_SYMBOL "http://127.0.0.1/imagens/boss_symbol.png"
#define DEAD "http://127.0.0.1/imagens/dead_screen.png"
#define NO_MANA "http://127.0.0.1/imagens/no_mana.png"
#define END_SCREEN "http://127.0.0.1/imagens/end_screen.png"



/**
@file parser.c
Definição do estado e das funções que convertem estados em strings e vice-versa
*/


/** \brief ????????????????????????????????????????????

	@param nivel 
	@param px
	@param py
	@param score
	@param vida
	@param mana
	@param atk
	@param crit
	@param vida_potion
	@param mana_potion
	@param sword
	@param shield
	@param screen
*/ 
ESTADO inicializar(int nivel, int px, int py, int score, int vida, int mana, int atk, int crit, int vida_potion, int mana_potion, int sword, int shield, int screen);

/** \brief Função que movimenta o jogador.

	Os vários tipos de movimento do jogador são mover-se para uma casa livre, atacar um inimigo que esteja no range, apanhar um item ou avançar
	de nível.
	@param e
	@param difx posição
	@param dify posição
	@param *nomef
	@param acao 
*/
void print_move(ESTADO e, int difx, int dify, char *nomef, int acao);

/** \brief Função que move os inimigos.

	O movimento dos inimigos é feito conforme a posição do jogador e o estado do tabuleiro (onde se situa a porta e o tesouro).
	@param newE
*/
ESTADO enemyMove(ESTADO newE);

/** \brief Função que determina se o jogador está em range do ataque do inimigo.

	Conforme o tipo do inimigo (meelee ou ranged) é determinado se o jogador está no range para ser atacado.
	@param e Estado do jogo.
	@param i Índice do inimigo.
*/
int inRange(ESTADO e, int i);

/** \brief Função que determina se uma casa do tabuleiro de jogo está livre.

	A função retorna 0 caso esteja ocupada, ou seja, caso contenha um monstro, um obstáculo, um item, o tesouro, a porta ou o próprio jogador.
	@param e
	@param x posição
	@param y posição
*/
int casaLivre (ESTADO e, int x, int y);

/** \brief Função que verifica qual o índice do monstro numa casa.

	A função retorna o índice do monstro na posição (x,y) do tabuleiro. Caso não esteja nenhum monstro a função retorna -1.
	@param e
	@param x posição
	@param y posição
*/
int isEnemy (ESTADO e, int x, int y);

/** \brief Função que verifica qual o índice da parede numa casa.

	A função retorna o índice da parede na posição (x,y) do tabuleiro. Caso não esteja nenhuma parede a função retorna -1.
	@param e
	@param x posição
	@param y posição
*/
int isWall (ESTADO e, int x, int y);

/** \brief Função que verifica se uma casa tem item.

	A função retorna o índice do monstro que deixou o item na posição (x,y) do tabuleiro. 
	Caso não esteja nenhum item a função retorna -1.
	@param e
	@param px posição
	@param py posição
*/
int isItem (ESTADO e, int px, int py);

/** \brief Função que atribui o ataque do inimigo.

	A função atribui, conforme o tipo do inimigo, o seu ataque.
	@param tipo
*/
int atk_Inimigo(int tipo);

/** \brief Função que atribui a vida do inimigo.

	A função atribui, conforme o tipo do inimigo, a sua vida.
	@param tipo
*/
int vida_Inimigo(int tipo);

/** \brief Função que atribui o item do tesouro.

	A função, através de um número pseudo-aleatório, determina o item que o tesouro contem.
	@param e
	@param x
	@param y

*/
ESTADO itemTesouro (ESTADO e, int x, int y);

/** \brief Função que apanha um item.

	A função altera o estado do jogador (vida, mana, ataque, crítico ou o inventário) conforme o item na posição (x,y).
	@param e
	@param x
	@param y

*/
ESTADO catchItem(int item, ESTADO e);

/** \brief Função que atribui o tipo de um inimigo.

	A função atribui, conforme um número pseudo-aleatório, o tipo do inimigo.
	@param nivel
	@param randNum
*/
int tipoInimigo(int nivel, int randNum);

/** \brief Função que atribui o item deixado por um inimigo.

	A função atribui, conforme um número pseudo-aleatório, o item deixado por um inimigo. 
	A probabilidade de um inimigo deixar um item é de 30%.
	@param rand
*/
int itemInimigo(int randNum);

/** \brief Função que funciona como interruptor para a ajuda de mostrar a vida dos inimigos.
 
	@param *nomef
*/
void opcaoVida(char *nomef);

/** \brief Função que mostra a vida dos inimigos.

	A função imprime no jogo a vida de todos os inimigos. Caso o inimigo seja um Boss também imprime um símbolo para o sinalizar.
	@param e
*/
void print_enemy_vida(ESTADO e);

/** \brief Função que funciona como interruptor para a ajuda de mostrar o range dos inimigos.
 
	@param *nomef
*/
void opcaoRange(char *nomef);

/** \brief Função que permiter selecionar um inimigo fora de alcance de ataque e mostrar o seu range de ataque.

	@param e
	@param *nomef
*/
void selectRange(ESTADO e, char *nomef);

/** \brief Função determina a vida de um inimigo após o ataque do jogador.

	A função determina a vida final do monstro atacado após calcular o ataque do jogador (que varia com a percentagem de crítico e o power up).
	@param vida
	@param crit
	@param atk
	@param sword
*/
int atk_Player(int vida, int crit, int atk, int sword);

/** \brief Função do ataque especial "Bola de Fogo".

	A função faz com que todos os monstros possam ser atacados, independentemente da posição do jogador. Este ataque tem um custo de mana.
	@param e
	@param *nomef
*/
void bola_Fogo(ESTADO e, char *nomef);

/** \brief Função do movimento especial "Flash".

	A função permite ao jogador movimentar-se mais casas do que o normal. Este movimento tem um custo de mana.
	@param e
	@param *nomef
*/
void mov_Flash(ESTADO e, char *nomef);

/** \brief Função do ataque especial "Espada Giratória".  (!!!!!!!!!!!!!!!!!!!!!!!!!!!!! nao é isto que ela faz)

	A função faz com que todos os monstro dentro do range sejam atacados.
	@param *nomef
*/
void espada_giratoria(char *nomef);

/** \brief Função do movimento especial "Dormir".  (!!!!!!!!!!!!!!!!!!!!!!!!!!!!! nao é isto que ela faz)

	A função faz com que o jogador durma e restaure vida e mana.
	@param *nomef
*/
void dormir (char *nomef);

/** \brief Função que imprime uma imagem dadas as suas coordenadas.

	@param px
	@param py
	@param *imagem
*/
void print_image(int px, int py, char *imagem);

/** \brief Função que imprime imagens atribuindo-lhes um ID.

	@param px
	@param py
	@param *imagem
	@param jog
*/
void print_imageID(int px, int py, char *imagem, int jogador);

/** \brief Função que o jogador e os seus possíveis movimentos.

	@param e
	@param acao
	@param *nomef
*/
void print_player(ESTADO e, int acao, char *nomef);

/** \brief Função que imprime todos os inimigos.

	@param e
*/
void print_enemy(ESTADO e);

/** \brief Função que imprime o range de todos os inimigos.

	@param e
*/
void print_rangeEnemy(ESTADO e);

/** \brief Função que imprime todos os obstáculos do jogo.

	@param e
*/
void print_wall(ESTADO e);

/** \brief Função que imprime a porta para o próximo nível.

	@param e
*/
void print_door(ESTADO e);

/** \brief Função que imprime o item dropado por um inimigo.

	@param i - índice do inimigo que continha o item.
	@param e - Estado atual do jogo.
*/
void print_specific_item(int i, ESTADO e);

/** \brief Função que imprime todos os items existentes num dado estado de jogo.

	@param e - Estado atual do jogo.
*/
void print_item(ESTADO e);

/** \brief Função que imprime o tesouro.

	@param e
*/
void print_treasure(ESTADO e);

/** \brief Função que o menu lateral de jogo.  */   
void print_menu_lateral(ESTADO e);

/** \brief Função que imprime o menu quando o jogador morre. */
void print_dead_screen(char *nomef);

/** \brief Função que imprime o menu de Top Scores.

	@param *nomef
*/
void print_score_screen(char *nomef);

/** \brief Função que imprime as Stats (vida, mana, nível, ataque, crítico e score) do jogador.

	@param e
*/
void print_stats(ESTADO e);

/** \brief Função que imprimi o ecrã inicial do jogo.

	@param *nomef
*/
void print_start(char *nomef);

/** \brief Função que imprime as casas livres para onde o jogador se pode mover.

	@param e
	@param px
	@param py
*/ 
void print_rangeMov(ESTADO e, int px, int py);

/** \brief Função que imprime as casas com monstro que o jogador pode atacar.

	@param e
	@param px
	@param py
*/ 
void print_rangeAttack (ESTADO e, int px, int py);

/** \brief Função que imprime o inventário do jogador.

	@param e
	@param *nomef
*/ 
void print_inventory(ESTADO e, char *nomef);

/** \brief Função que imprime as animações do movimento do jogador ou dos inimigos.

	@param x
	@param y
	@param px
	@param py
	@param id
*/ 
void print_animation(int difx,int dify, int posx, int id);

/** \brief Função que imprime o tabuleiro de jogo.

	@param e
	@param px
	@param py
*/ 
void print_board(ESTADO e);

/** \brief Função que imprime hexagonos transparentes como hiperligações.

	@param x
	@param y
*/ 
void print_hex(int x, int y);

/** \brief Função que guarda o estado num ficheiro.

	@param e
	@param *nomef
*/ 
void guardar_estado(ESTADO e, char *nomef);

/** \brief Função que lê o estado a partir de um ficheiro.

	@param *nomef
*/ 
ESTADO ler_estado(char *nomef);


/** \brief Função que mostra ao jogador que não tem mana para realizar a ação.

	@param e
*/ 
void print_noMana();

/** \brief Função que desenha o menu após o jogador ter acabado o jogo.

	@param score - Pontuação final do jogador
*/ 
void print_end_game(int score, char *nomef);


/** \brief Função que processa as várias ações do jogo.

	@param e
	@param acao
	@param *nomef
	@param numI
*/ 
ESTADO processar_acao(ESTADO e, int acao, char *nomef, int numI);


/** \brief Função que processa o movimento do jogador

	@param e
	@param px
	@param py
*/ 
ESTADO processar_mov(ESTADO e, int posx, int posy);

void parser();




	







#endif