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
#define RANGEMOV "http://127.0.0.1/rangeMov10.png"
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
#define LAMA "http://127.0.0.1/lama.png"
#define VIDA_INIMIGO "http://127.0.0.1/vida_inimigo.png"





void print_door(ESTADO e);
void print_square(int px, int py, int tam);
void print_rangeMov(int px, int py, int tam);
int casaLivre (ESTADO e, int x, int y);
void parser();
void print_move(ESTADO e, int difx, int dify);
void print_rangeAttack(int px, int py, int tam);
ESTADO enemyMove(ESTADO newE);
int isEnemy (ESTADO e, int x, int y);
void print_image(int px, int py, int tam, char *imagem);
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
int atk_Player(int vida, int crit, int atk);
void print_lama(ESTADO e);
void opcaoVida(ESTADO e);
void print_enemy_vida(ESTADO e);
int atk_Inimigo(int tipo);
int vida_Inimigo(int tipo);



#endif