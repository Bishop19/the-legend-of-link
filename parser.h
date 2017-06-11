#ifndef ___PARSER_H___
#include "estado.h"
#define ___PARSER_H___

/**
@file parser.h
Funções responsaveis pelo funcionamento do jogo.
*/


#define SIZE 10
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
#define BOLA_FOGO "http://127.0.0.1/imagens/bolaFogo.png"
#define MENU_BUTTON1 "http://127.0.0.1/imagens/menu_button1.png"
#define MENU_BUTTON2 "http://127.0.0.1/imagens/menu_button2.png"
#define ESPADA_GIR "http://127.0.0.1/imagens/espada_giratoria.png"
#define ESPADA_GIR2 "http://127.0.0.1/imagens/espada_giratoria2.png"



/** \brief Função que cria um estado de jogo.

	@param nivel - Nível a que o jogo se encontra.
	@param px - Posição.
	@param py - Posição.
	@param score - Score atual do jogagor.
	@param vida - Vida do jogador.
	@param mana - Mana do jogador.
	@param atk - Pontos de ataque do jogador.
	@param crit - Percentagem de critical chance.
	@param vida_potion - Número de poções de vida no inventário.
	@param mana_potion - Número de poções de mana no inventário.
	@param sword - Número de items do tipo "Sword" no inventário. 
	@param shield - Número de items do tipo "Shield" no inventário.
	@param screen - Momento em que o jogo se encontra.
	@returns O novo estado de jogo.
*/ 
ESTADO inicializar(int nivel, int px, int py, int score, int vida, int mana, int atk, int crit, int vida_potion, int mana_potion, int sword, int shield, int screen);

/** \brief Função que movimenta o jogador.

	Os vários tipos de movimento do jogador são mover-se para uma casa livre, atacar um inimigo que esteja no range, apanhar um item ou avançar
	de nível.
	@param e  Estado atual do jogo.
	@param difx  Posição.
	@param dify  Posição.
	@param *nomef  Nome do Ficheiro.
*/
void print_move(ESTADO e, int difx, int dify, char *nomef, int acao);

/** \brief Função que move os inimigos.

	O movimento dos inimigos é feito conforme a posição do jogador e o estado do tabuleiro (onde se situa a porta e o tesouro).
	@param e Estado atual de jogo
	@returns 
*/
ESTADO enemyMove(ESTADO e);

/** \brief Função que determina se o jogador está em range do ataque do inimigo.

	Conforme o tipo do inimigo (meelee ou ranged) é determinado se o jogador está no range para ser atacado.
	@param e Estado do jogo.
	@param i Índice do inimigo.
	@returns 1 se está no alcance, 0 caso contrário.
*/
int inRange(ESTADO e, int i);

/** \brief Função que determina se uma casa do tabuleiro de jogo está livre.

	A função retorna 0 caso esteja ocupada, ou seja, caso contenha um monstro, um obstáculo, um item, o tesouro, a porta ou o próprio jogador.
	@param e  Estado atual do jogo.
	@param x  Posição.
	@param y  Posição.
	@returns 1 se a casa está livre, 0 caso contrário.
*/
int casaLivre (ESTADO e, int x, int y);

/** \brief Função que verifica qual o índice do monstro numa casa.

	@param e  Estado atual do jogo.
	@param x  Posição.
	@param y  Posição.
	@returns O índice do monstro na posição (x,y) do tabuleiro. Caso não esteja nenhum monstro a função retorna -1.
*/
int isEnemy (ESTADO e, int x, int y);

/** \brief Função que verifica se uma certa posição é parede ou não.

	@param e  Estado atual do jogo.
	@param x  Posição
	@param y  Posição
	@returns 1 se for parede, 0 caso contrário.
*/
int isWall (ESTADO e, int x, int y);

/** \brief Função que verifica se uma casa tem item.

	@param e  Estado atual do jogo.
	@param px  Posição
	@param py  Posição
	@returns  O índice do monstro que deixou o item na posição (x,y) do tabuleiro ou -1 caso nao exista item nessa posição.
*/
int isItem (ESTADO e, int px, int py);

/** \brief Função que atribui o ataque do inimigo.

	A função atribui, conforme o tipo do inimigo, o seu ataque.
	@param tipo  Tipo do inimigo para diferenciar os respetivos ataques.
	@returns O número de pontos de ataque do inimigo.
*/
int atk_Inimigo(int tipo);

/** \brief Função que atribui a vida do inimigo.

	A função atribui, conforme o tipo do inimigo, a sua vida.
	@param tipo  Tipo do inimigo para diferenciar as respetivas vidas.
	@returns A vida do inimigo. 
*/
int vida_Inimigo(int tipo);

/** \brief Função que atribui o item do tesouro.

	A função, através de um número pseudo-aleatório, determina o item que o tesouro contem.
	@param e  Estado atual do jogo.
	@param x  Posição.
	@param y  Posicao.
	@returns O estado resultante de atribuir o item ao tesouro.

*/
ESTADO itemTesouro (ESTADO e, int x, int y);

/** \brief Função que apanha um item.

	A função altera o estado do jogador (vida, mana, ataque, crítico ou o inventário) conforme o item na posição (x,y).
	@param item Tipo de item.
	@param e Estado de jogo.
	@returns O estado resultante de apanhar o item.

*/
ESTADO catchItem(int item, ESTADO e);

/** \brief Função que atribui o tipo de um inimigo.

	A função atribui, conforme um número pseudo-aleatório, o tipo do inimigo.
	@param nivel  Nível a que o jogo se encontra.
	@param randNum  Número aleatório.
	@returns O tipo de inimigo.
*/
int tipoInimigo(int nivel, int randNum);

/** \brief Função que determina o item deixado por um inimigo.

	A função determina, conforme um número pseudo-aleatório, o item deixado por um inimigo. 
	A probabilidade de um inimigo deixar um item é de 30%.
	@param randNum  Número aleatório.
	@returns O tipo de item.
*/
int itemInimigo(int randNum);

/** \brief Função que funciona como interruptor para a ajuda de mostrar a vida dos inimigos.
 
	@param *nomef  Nome do ficheiro.
*/
void opcaoVida(char *nomef);

/** \brief Função que mostra a vida dos inimigos.

	A função imprime no jogo a vida de todos os inimigos. Caso o inimigo seja um Boss também imprime um símbolo para o sinalizar.
	@param e  Estado atual do jogo.
*/
void print_enemy_vida(ESTADO e);

/** \brief Função que funciona como interruptor para a ajuda de mostrar o range dos inimigos.
 
	@param *nomef  Nome do ficheiro.
*/
void opcaoRange(char *nomef);

/** \brief Função que permiter selecionar um inimigo fora de alcance de ataque e mostrar o seu range de ataque.

	@param e  Estado atual do jogo.
	@param *nomef  Nome do ficheiro.
*/
void selectRange(ESTADO e, char *nomef);

/** \brief Função determina a vida de um inimigo após o ataque do jogador.

	A função determina a vida final do monstro atacado após calcular o ataque do jogador (que varia com a percentagem de crítico e o power up).
	@param vida
	@param crit
	@param atk
	@param sword
	@returns A vida restante do inimigo.
*/
int atk_Player(int vida, int crit, int atk, int sword);

/** \brief Função do ataque especial "Bola de Fogo".

	A função faz com que todos os monstros possam ser atacados, independentemente da posição do jogador. Este ataque tem um custo de mana.
	@param e - Estado atual do jogo.
	@param *nomef - Nome do ficheiro.
*/
void bola_Fogo(ESTADO e, char *nomef);


/** \brief Função faz a animação do ataque especial "Bola de Fogo".

	@param x - Posição x do inimigo.
	@param y - Posição y do inimigo.
*/
void print_bolaFogo_animation(int x, int y);


/** \brief Função do movimento especial "Flash".

	A função permite ao jogador movimentar-se mais casas do que o normal. Este movimento tem um custo de mana.
	@param e - Estado atual do jogo.
	@param *nomef - Nome do ficheiro.
*/
void mov_Flash(ESTADO e, char *nomef);

/** \brief Função que faz a animação do movimento especial "Flash".

	Conforme a acao executada, a função faz uma animação do movimento.
	@param acao - Última ação que o jogador realizou.
*/
void print_flash_animation(int acao);


/** \brief Função do ataque especial "Espada Giratória".  

	A função faz com que todos os monstro dentro do range sejam atacados.
	@param *nomef - Nome do ficheiro.
*/
void espada_giratoria(char *nomef);


/** \brief Função do movimento especial "Dormir".  

	A função faz com que o jogador durma e restaure vida e mana.
	@param *nomef  Nome do ficheiro.
*/
void dormir (char *nomef);


/** \brief Função do movimento especial "Dormir".  

	A função faz com que o jogador durma e restaure vida e mana.
	@param *nomef  Nome do ficheiro.
*/
void print_dormir_animation();


/** \brief Função que imprime uma imagem dadas as suas coordenadas.

	@param px  Posição.
	@param py  Posição.
	@param *imagem  Imagem a imprimir.
*/
void print_image(int px, int py, char *imagem);


/** \brief Função que imprime imagens atribuindo-lhes um ID.

	@param px  Posição.
	@param py  Posição.
	@param *imagem  Imagem a imprimir.
	@param jog  Indicação se é imagem do jogador ou de um inimigo.
*/
void print_imageID(int px, int py, char *imagem, int jogador);


/** \brief Função que o jogador e os seus possíveis movimentos.

	@param e  Estado atual do jogo.
	@param *nomef  Nome do ficheiro.
*/
void print_player(ESTADO e, char *nomef);


/** \brief Função que imprime todos os inimigos.

	@param e  Estado atual do jogo.
*/
void print_enemy(ESTADO e);


/** \brief Função que imprime o range de todos os inimigos.

	@param e  Estado atual do jogo.
*/
void print_rangeEnemy(ESTADO e);


/** \brief Função que imprime todos os obstáculos do jogo.

	@param e  Estado atual do jogo.
*/

void print_wall(ESTADO e);

/** \brief Função que imprime a porta para o próximo nível.

	@param e  Estado atual do jogo.
*/
void print_door(ESTADO e);


/** \brief Função que imprime o item dropado por um inimigo.

	@param i índice do inimigo que continha o item.
	@param e  Estado atual do jogo.
*/
void print_specific_item(int i, ESTADO e);


/** \brief Função que imprime todos os items existentes num dado estado de jogo.

	@param e  Estado atual do jogo.
*/
void print_item(ESTADO e);


/** \brief Função que imprime o tesouro.

	@param e  Estado atual do jogo.
*/
void print_treasure(ESTADO e);


/** \brief Função que o menu lateral de jogo.  */   
void print_menu_lateral(ESTADO e);


/** \brief Função que imprime o menu quando o jogador morre. */
void print_dead_screen(char *nomef);


/** \brief Função que imprime o menu de Top Scores.

	@param *nomef  Nome do ficheiro.
*/
void print_score_screen(char *nomef);


/** \brief Função que imprime as Stats (vida, mana, nível, ataque, crítico e score) do jogador.

	@param e  Estado atual do jogo.
*/
void print_stats(ESTADO e);


/** \brief Função que imprimi o ecrã inicial do jogo.

	@param *nomef  Nome do ficheiro.
*/
void print_start(char *nomef);


/** \brief Função que imprime as casas livres para onde o jogador se pode mover.

	@param e  Estado atual do jogo.
	@param px  Posição.
	@param py  Posição.
*/
void print_rangeMov(ESTADO e, int px, int py);


/** \brief Função que imprime as casas com monstro que o jogador pode atacar.

	@param e  Estado atual do jogo.
	@param px  Posição.
	@param py  Posição.
*/ 
void print_rangeAttack (ESTADO e, int px, int py);


/** \brief Função que imprime o inventário do jogador.

	@param e  Estado atual do jogo.
	@param *nomef  Nome do ficheiro.
*/ 
void print_inventory(ESTADO e, char *nomef);


/** \brief Função que imprime as animações do movimento do jogador ou dos inimigos.

	@param x  Posição.
	@param y  Posição.
	@param px  Posição.
	@param py  Posição.
	@param id  ID da imagem.
*/ 
void print_animation(int difx,int dify, int posx, int id);


/** \brief Função que imprime o tabuleiro de jogo.

	@param e  Estado atual do jogo.
*/ 
void print_board(ESTADO e);


/** \brief Função que imprime hexagonos transparentes como hiperligações.

	@param x  Posição.
	@param y  Posição.
*/ 
void print_hex(int x, int y);


/** \brief Função que guarda o estado num ficheiro.

	@param e  Estado atual do jogo.
	@param *nomef  Nome do ficheiro.
*/ 
void guardar_estado(ESTADO e, char *nomef);


/** \brief Função que lê o estado a partir de um ficheiro.

	@param *nomef  Nome do ficheiro.
	@returns O estado presente no ficheiro.
*/ 
ESTADO ler_estado(char *nomef);


/** \brief Função que mostra ao jogador que não tem mana para realizar a ação.*/ 
void print_noMana();


/** \brief Função que desenha o menu após o jogador ter acabado o jogo.

	@param score  Pontuação final do jogador
	@param *nomef Nome do ficheiro,
*/
void print_end_game(int score, char *nomef);


/** \brief Função que processa as várias ações do jogo.

	@param e  Estado atual do jogo.
	@param acao  Ação a ser processada.
	@param *nomef  Nome do ficheiro.
	@param numI Índice do inimigo. 
	@returns O estado após a ação.
*/ 
ESTADO processar_acao(ESTADO e, int acao, char *nomef, int numI);


/** \brief Função que processa o movimento do jogador

	@param e  Estado atual do jogo.
	@param posx  Posição.
	@param posy  Posição.
	@returns O estado resultante do movimento do jogador.
*/ 
ESTADO processar_mov(ESTADO e, int posx, int posy);


/** \brief Função principal do jogo */
void parser();


#endif