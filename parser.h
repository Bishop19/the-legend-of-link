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
void print_animation(int x,int y, int px, int id);
int isWall (ESTADO e, int x, int y);

#endif