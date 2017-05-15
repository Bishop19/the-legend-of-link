#ifndef ___PARSER_H___
#include "estado.h"
#define ___PARSER_H___

#define SIZE 10
#define TAM 60
#define NUM_INIMIGOS 10
#define NUM_OBSTACULOS 20

#define PLAYER "http://127.0.0.1/player.png"
#define ENEMY "http://127.0.0.1/enemy1.png"
#define ENEMY2 "http://127.0.0.1/enemy2.png"
#define ENEMY3 "http://127.0.0.1/enemy3.png"
#define WALL "http://127.0.0.1/wall.png"
#define DOOR "http://127.0.0.1/door.png"
#define FLOOR "http://127.0.0.1/floor.png"
#define RANGEMOV "http://127.0.0.1/rangeMove.png"
#define RANGEATTACK "http://127.0.0.1/rangeAttack.png"
#define TREASURE "http://127.0.0.1/tesouro.png"
#define VIDA "http://127.0.0.1/vida.png"
#define VIDADROP "http://127.0.0.1/vida_Drop.png"
#define MANA "http://127.0.0.1/mana.png"
#define MANADROP "http://127.0.0.1/mana_Drop.png"
#define SWORD "http://127.0.0.1/sword.png"
#define CRIT "http://127.0.0.1/crit.png"
#define SCORE_5 "http://127.0.0.1/score5.png"
#define SCORE_10 "http://127.0.0.1/score10.png"
#define SCORE_25 "http://127.0.0.1/score25.png"
#define VIDA_INIMIGO "http://127.0.0.1/vida_inimigo.png"
#define HEX_FLOOR "http://127.0.0.1/floor_hex.png"
#define SHIELD_PU "http://127.0.0.1/shield.png"
#define SWORD_PU "http://127.0.0.1/sword_PU.png"
#define SWORD_PU_INV "http://127.0.0.1/sword_PU_inv.png"
#define SHIELD_PU_INV "http://127.0.0.1/shield_inv.png"
#define VIDA_INV "http://127.0.0.1/vida_inv.png"
#define MANA_INV "http://127.0.0.1/mana_inv.png"
#define MENU "http://127.0.0.1/menu1.png"
#define TITLE "http://127.0.0.1/Title_Screen.png"
#define START_BUTTON "http://127.0.0.1/start_button.png"
#define BACK_BUTTON "http://127.0.0.1/back_button.png"
#define SQUARE_LINK "http://127.0.0.1/square_link.png"
#define TOGGLE_RANGE "http://127.0.0.1/toggle_range.png"
#define TOGGLE_VIDA "http://127.0.0.1/toggle_vida.png"
#define TOPSCORE_BUTTON "http://127.0.0.1/topScore_button.png"
#define BOSS_SYMBOL "http://127.0.0.1/boss_symbol.png"





void print_door(ESTADO e);
void print_rangeMov(ESTADO e, int px, int py);
int casaLivre (ESTADO e, int x, int y);
void parser();
void print_move(ESTADO e, int difx, int dify, char *nomef, int acao);
void print_rangeAttack(ESTADO e, int px, int py);
ESTADO enemyMove(ESTADO newE);
int isEnemy (ESTADO e, int px, int py);
void print_image(int px, int py, char *imagem);
void print_treasure(ESTADO e);
int scoreTesouro ();
int tipoInimigo(int nivel, int x);
void print_enemy(ESTADO e);
void print_item(ESTADO e);
int inRange(ESTADO e, int i);
void print_enemy_specific(int x, int y, int tipo);
void print_item(ESTADO e);
int itemInimigo(int rand);
ESTADO itemTesouro (ESTADO e, int x, int y);
void print_treasure_item(ESTADO e);
ESTADO catchItem(int item, ESTADO e);
int isItem (ESTADO e, int px, int py);
void print_specific_item(int i, ESTADO e);
void print_rangeEnemy(ESTADO e);
int atk_Player(int vida, int crit, int atk, int sword);
void print_lama(ESTADO e);
void opcaoVida(char *nomef);
void print_enemy_vida(ESTADO e);
int atk_Inimigo(int tipo);
int vida_Inimigo(int tipo);
void print_hex(int x, int y);
ESTADO processar_mov(ESTADO e, int px, int py);
ESTADO processar_acao(ESTADO e,int acao, char *nomef, int numI);
void guardar_estado(ESTADO e, char *nomef);
ESTADO ler_estado(char *nomef);



#endif