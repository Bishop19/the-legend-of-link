#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "estado.h"
#include <time.h>  
#include "highScore.h"



ESTADO inicializar(int nivel, int px, int py, int score, int vida, int mana, int atk, int crit, int vida_potion, int mana_potion, int sword, int shield, int screen){
	int i,aux, x, y, randNum; 
	ESTADO e = {0};
	srand(time(NULL));

	e.screen=screen;
	e.nivel = nivel;
	e.bolaFogo = 0; 
	e.flash=0;
	e.jog.x = px;
	e.jog.y = py;  
	e.jog.vida=vida;
	e.jog.mana=mana;
	e.jog.atk=atk; 
	e.jog.item_vida=vida_potion;
	e.jog.item_mana=mana_potion;
	e.jog.item_sword=sword;
	e.jog.item_shield=shield;
	e.jog.powerUp_sword=0;
	e.jog.powerUp_shield=0;
	e.jog.crit=crit;
	e.score = score;
	e.range=0;
	
	x=px;
	y=py;
	while (abs(x-px)+abs(y-py)<12){ // gerar porta a 12 casas do jogador no minimo
		x=rand()%11;
		y=rand()%8;
		e.door.x = x; 
		e.door.y = y;  
	}

	i=0;
	randNum=rand()%SIZE;
	if (randNum<8){
		while(i==0){ // gerar tesouro com 80% de possibilidade
			x=rand()%11;
			y=rand()%8;
			if((casaLivre(e,x,y)==1) && (abs(e.door.x-x)+abs(e.door.y-y)>7) && (abs(e.jog.x-x)+abs(e.jog.y-y)>7)){
				e.treasure.x = x;
				e.treasure.y = y;
				e.treasure.visivel = 1;
				i++;
			}
		}
	}

	e.item.x=x;
	e.item.y=y;
	e.item.visivel=0;

	e.num_inimigos = 0;
	i=0;
	aux=0;
	if (e.nivel%5==0){ // cria boss
		while(aux==0){
			randNum=rand();
			x=rand()%11; 
			y=rand()%8;
			if((casaLivre(e,x,y)==1) && (abs(e.door.x-x)+abs(e.door.y-y)>5) && (abs(e.jog.x-x)+abs(e.jog.y-y)>5)){
				e.inimigo[0].x=x;
	    		e.inimigo[0].y=y;
	    		e.inimigo[0].tipo=4*(e.nivel/5);
	    		e.inimigo[0].vida=4+2*(e.nivel/5);
	    		e.inimigo[0].atk=1+(e.nivel/5);
	    		e.inimigo[0].item=itemInimigo(randNum);
	    		e.inimigo[0].visivel=0;
	    		e.num_inimigos++;
	    		aux=6; 
	    		i++;	
			}
		}
	}
	while(aux<NUM_INIMIGOS){
		x=rand()%11; 
		y=rand()%8;
		randNum=rand();
    		if(casaLivre(e,x,y)==1){
    			e.inimigo[i].x=x;
    			e.inimigo[i].y=y;
    			e.inimigo[i].tipo=tipoInimigo(e.nivel, rand());
    			e.inimigo[i].vida=vida_Inimigo(e.inimigo[i].tipo);
    			e.inimigo[i].atk=atk_Inimigo(e.inimigo[i].tipo);
    			e.inimigo[i].item=itemInimigo(randNum);
    			e.inimigo[i].visivel=0;
    			i++;
    			e.num_inimigos++;
    			aux++;
    		}	
   	}

   	e.num_obstaculos = 0;
  	i=0;
    while(i<NUM_OBSTACULOS){
		x=rand()%11; 
		y=rand()%8; 
    		if(casaLivre(e,x,y)==1){
    			e.obstaculo[i].x=x;
    			e.obstaculo[i].y=y;
    			i++;
    			e.num_obstaculos++;
    		}	 
    }

	return e;
}


void print_move(ESTADO e, int difx, int dify, char *nomef, int acao){
	int px = e.jog.x + difx;
	int py = e.jog.y + dify;


	if (px==e.door.x && py==e.door.y){
		acao=1;
		print_rangeMov(e, px, py);
		printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s,%d\">\n", nomef, acao);
			print_hex(e.door.x,e.door.y);
		printf("</a>\n");
	}
	
	else if (difx==0 && dify==(-1) && py>=0 && py<8){
		acao=2; 
	}
	else if (difx==0 && dify==1 && py>=0 && py<8){
		acao=3; 
	}
	else if (difx==(-1) && dify==0 && px>=0 && px<11){
		acao=4; 
	}
	else if (difx==1 && dify==0 && px>=0 && px<=11){ 
		acao=5;  
	}
	else if (e.jog.x%2==0 && difx==1 && dify==1 && py>=0 && py<8 && px>=0 && px<11){
		acao=6; 
	}
	else if (e.jog.x%2==1 && difx==(-1) && dify==(-1) && py>=0 && py<8 && px>=0 && px<11){
		acao=7; 
	}
	else if (e.jog.x%2==0 && difx==(-1) && dify==1 && py>=0 && py<8 && px>=0 && px<11){
		acao=8; 
	}
	else if (e.jog.x%2==1 && difx==1 && dify==(-1) && py>=0 && py<8 && px>=0 && px<11){
		acao=9; 		
	}
	if(isWall(e, px, py)==(-1)){
		print_rangeMov(e, px, py);
		print_rangeAttack(e, px, py);
		printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s,%d\">\n", nomef, acao);
			print_hex(px,py);
		printf("</a>\n");
	}
}



ESTADO enemyMove(ESTADO e){
	int i, x, y, danoSofrido=0;

	for(i=0; i<e.num_inimigos; i++){
		if(e.inimigo[i].vida>0){
			if (inRange(e,i)==1){
				danoSofrido+=e.inimigo[i].atk;
				print_attack_animation(e, i);
				i++;
			}
			if (abs(e.inimigo[i].x-e.door.x)+abs(e.inimigo[i].y-e.door.y)<=4) e=enemyMove_door(e, i);
			else if (abs(e.inimigo[i].x-e.treasure.x)+abs(e.inimigo[i].y-e.treasure.y)<=2) e=enemyMove_treasure(e, i);
			else{
				if (e.jog.x > e.inimigo[i].x){
					x=e.inimigo[i].x + 1;
					if(casaLivre(e, x, e.inimigo[i].y)==1){ 
							e.inimigo[i].x = x;
							print_animation(1,0,x,i);
					}
				}
				else if (e.jog.y > e.inimigo[i].y){
					y=e.inimigo[i].y + 1;
					if(casaLivre(e, e.inimigo[i].x, y)==1){ 
							e.inimigo[i].y = y;
							print_animation(0,1,e.inimigo[i].x,i);

					}
				}
				else if (e.jog.x < e.inimigo[i].x){
					x=e.inimigo[i].x - 1;
					if(casaLivre(e, x, e.inimigo[i].y)==1){ 
							e.inimigo[i].x = x;
							print_animation(-1,0,x,i);

					}
				}
				else if (e.jog.y < e.inimigo[i].y){
						y=e.inimigo[i].y - 1;
					if(casaLivre(e, e.inimigo[i].x, y)==1){ 
							e.inimigo[i].y = y;
							print_animation(0,-1,e.inimigo[i].x,i);

					}
				}
			}
		}
	}
	if (e.jog.powerUp_shield==1) danoSofrido=(danoSofrido+1)/2;
	e.jog.vida -= danoSofrido;

	return e;
}


ESTADO enemyMove_door(ESTADO e, int i){
	int x, y;

	if (e.door.x > e.inimigo[i].x){
		x=e.inimigo[i].x + 1;
		if(casaLivre(e, x, e.inimigo[i].y)==1){ 
			e.inimigo[i].x = x;
			print_animation(1,0,x,i);
		}
	}
	else if (e.door.y > e.inimigo[i].y){
		y=e.inimigo[i].y + 1;
		if(casaLivre(e, e.inimigo[i].x, y)==1){ 
			e.inimigo[i].y = y;
			print_animation(0,1,e.inimigo[i].x,i);
		}
	}
	else if (e.door.x < e.inimigo[i].x){
		x=e.inimigo[i].x - 1;
		if(casaLivre(e, x, e.inimigo[i].y)==1){ 
			e.inimigo[i].x = x;
			print_animation(-1,0,x,i);
		}
	}
	else if (e.door.y < e.inimigo[i].y){
		y=e.inimigo[i].y - 1;
		if(casaLivre(e, e.inimigo[i].x, y)==1){ 
			e.inimigo[i].y = y;
			print_animation(0,-1,e.inimigo[i].x,i);
		}
	}

	return e;
}


ESTADO enemyMove_treasure(ESTADO e, int i){
	int x, y;

	if (e.treasure.x > e.inimigo[i].x){
		x=e.inimigo[i].x + 1;
		if(casaLivre(e, x, e.inimigo[i].y)==1){ 
			e.inimigo[i].x = x;
			print_animation(1,0,x,i);
		}
	}
	else if (e.treasure.y > e.inimigo[i].y){
		y=e.inimigo[i].y + 1;
		if(casaLivre(e, e.inimigo[i].x, y)==1){ 
			e.inimigo[i].y = y;
			print_animation(0,1,e.inimigo[i].x,i);
		}
	}
	else if (e.treasure.x < e.inimigo[i].x){
		x=e.inimigo[i].x - 1;
		if(casaLivre(e, x, e.inimigo[i].y)==1){ 
			e.inimigo[i].x = x;
			print_animation(-1,0,x,i);
		}
	}
	else if (e.treasure.y < e.inimigo[i].y){
		y=e.inimigo[i].y - 1;
		if(casaLivre(e, e.inimigo[i].x, y)==1){ 
			e.inimigo[i].y = y;
			print_animation(0,-1,e.inimigo[i].x,i);
		}
	}

	return e;
}


int inRange(ESTADO e, int i){
	int r=0;
	int x=e.inimigo[i].x, y=e.inimigo[i].y;
	int px=e.jog.x, py=e.jog.y;

	if(x+1==px && y==py) r=1;
	else if(x-1==px && y==py)r=1;
	else if(x==px && (y+1)==py) r=1;
	else if(x==px && (y-1)==py) r=1;
	else if(x==px && (y-1)==py) r=1;
	else{
		if(x%2==0){
			if(x+1==px && y+1==py) r=1;
			else if (x-1==px && y+1==py) r=1;
		}
		else{
			if(x-1==px && y-1==py) r=1;
			else if(x+1==px && y-1==py) r=1;
		}	
	}
	if(e.inimigo[i].tipo==3 || e.inimigo[i].tipo==7){
		if(x-2==px && y==py)r=1;
		else if(x+2==px && y==py) r=1;
			 else if(x%2==0){
					if(x-1==px && y-1==py) r=1;
					else if(x+1==px && y-1==py) r=1;
					else if(x+1==px && y+2==py) r=1;
					else if(x-1==px && y+2==py) r=1;
				  }
				  else{
				  	if(x-1==px && y-2==py) r=1;
				  	else if(x+1==px && y-2==py) r=1;
				  	else if(x+1==px && y+1==py) r=1;
				  	else if(x-1==px && y+1==py) r=1;
				  } 
	}
	return r;
}


int casaLivre (ESTADO e, int x, int y){
	int i=0, r=1;

	if(x<0 || y<0 || x>10 || y>7) r=0; 
	if(e.jog.x==x && e.jog.y==y) r=0; 
	if(e.door.x==x && e.door.y==y) r=0; 
	if(isItem(e,x,y)!=(-1)) r=0; 
	if(e.item.x==x && e.item.y==y && e.item.visivel==1) r=0;
	if(e.treasure.x==x && e.treasure.y==y && e.treasure.visivel==1) r=0; 		 
	for(i=0; i < e.num_inimigos && r!=0; i++){ 
		if(e.inimigo[i].x==x && e.inimigo[i].y==y && e.inimigo[i].vida>0) r=0;
	}
	for(i=0; i < e.num_obstaculos && r!=0; i++){ 
		if(e.obstaculo[i].x==x && e.obstaculo[i].y==y) r=0;
	}
	return r;
}


int isEnemy (ESTADO e, int x, int y){
	int i, r=-1;

	for (i=0; i<e.num_inimigos && r==(-1); i++)
		if (x==e.inimigo[i].x && y==e.inimigo[i].y && e.inimigo[i].vida!=0) r=i;
	return r;
}

int isWall (ESTADO e, int x, int y){ 
	int i, r=-1;

	for (i=0; i<e.num_obstaculos && r==(-1); i++)
		if (x==e.obstaculo[i].x && y==e.obstaculo[i].y) r=i;
	return r;
}

int isItem (ESTADO e, int px, int py){ 
	int i,result=(-1);

	for(i=0;i<e.num_inimigos && result==(-1) ;i++)
		if(e.inimigo[i].x==px &&  e.inimigo[i].y == py && e.inimigo[i].visivel==1 && e.inimigo[i].item >=0 && e.inimigo[i].item<=8) result=i;
	return result;
}

int atk_Inimigo(int tipo){
	int atk;

	if (tipo<4) atk=1;
	else atk=2;

	return atk;
}

int vida_Inimigo(int tipo){
	int vida;

	if (tipo==1 || tipo==3) vida=1;
	else if (tipo==2 || tipo==5 || tipo== 7) vida=2;
	else vida=3;

	return vida;
}


ESTADO itemTesouro (ESTADO e, int x, int y){
	srand(time(NULL));
	int randNum=rand()%24;

	e.item.x=x;
	e.item.y=y;

	if (randNum<=3) e.item.tipo=0;	
	else if (randNum>=4 && randNum<=6) e.item.tipo=1;
	else if (randNum==7 || randNum==8) e.item.tipo=2;
	else if (randNum>=9 && randNum<=11) e.item.tipo=3;
	else if (randNum>=12 && randNum<=14) e.item.tipo=4;
	else if (randNum>=15 && randNum<=17) e.item.tipo=5;
	else if (randNum==18 || randNum==19) e.item.tipo=6;	
	else if (randNum==20 || randNum==21) e.item.tipo=7;
	else if (randNum==22 || randNum==23) e.item.tipo=8;

	return e;
}


ESTADO catchItem(int item, ESTADO e){
	if (item==0) e.score+=5;
	else if (item==1) e.score+=10;
	else if (item==2) e.score+=25;
	else if (item==3) e.jog.item_vida+=1;
	else if (item==4) e.jog.item_mana+=1;
	else if (item==5) e.jog.atk+=1;
	else if (item==6) e.jog.crit+=1;
	else if (item==7) e.jog.item_sword+=1;
	else if (item==8) e.jog.item_shield+=1;

	return e;
}


int tipoInimigo(int nivel, int randNum){
	int tipo=0;

	if (nivel==1) tipo=1;
	else if(nivel==2){
		if(randNum%2==0) tipo=1;
		else tipo=2;
	}
	else if (nivel==3 || nivel==4 || nivel==5){ 
		if (randNum%5==0 || randNum%5==1) tipo=1;
		else if (randNum%5==2 || randNum%5==3) tipo=2;
		else tipo=3;
	}
	else if (nivel==6) tipo=5;
	else if(nivel==7 || nivel==8){
		if(randNum%2==0) tipo=6;
		else tipo=7;
	}
	else if (nivel==9 || nivel==10){ 
		if (randNum%5==0 || randNum%5==1) tipo=1;
		else if (randNum%5==2 || randNum%5==3) tipo=2;
		else tipo=3;
	}
	return tipo;
}

int itemInimigo(int randNum){
	int item=randNum%240;
	
	if (item<=3) item=0;								// 5 score 		4
	else if (item>=4 && item<=6) item=1;				// 10 Score 	3
	else if (item==7 || item==8) item=2;				// 25 score 	2
	else if (item>=9 && item<=11) item=3;				// vida 		3
	else if (item>=12 && item<=14) item=4;				// mana 		3
	else if (item>=15 && item<=17) item=5;				// sword 		3
	else if (item==18 || item==19) item=6;				// crit 		2
	else if (item==20 || item==21) item=7;				// sword pu     2
	else if (item==22 || item==23) item=8;				// shield 		2
	return item;
}

void opcaoVida(char *nomef){ 
	int acao=17;

	printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s,%d\">\n",nomef,acao);
			printf("<image x=942 y=563 xlink:href=\"%s\"/>\n", TOGGLE_VIDA);
	printf("</a>\n");
}


void print_enemy_vida(ESTADO e){
	int i, x, y, vida;

	for(i=0;i<e.num_inimigos;i++){
		if(e.inimigo[i].showVida == 1){
			x=e.inimigo[i].x*60+48;
			y=e.inimigo[i].y*70+15;
			vida=e.inimigo[i].vida;

			print_image(e.inimigo[i].x, e.inimigo[i].y, VIDA_INIMIGO);
			if(e.inimigo[i].tipo==4*(e.nivel/5)) print_image(e.inimigo[i].x, e.inimigo[i].y, BOSS_SYMBOL);
			if(e.inimigo[i].x%2==1)	printf("<text x=%d y=%d font-family=Verdana font-size=12 fill=white> %d </text> \n", x, y, vida);			
			else printf("<text x=%d y=%d font-family=Verdana font-size=12 fill=white> %d </text> \n", x, y+35, vida);
		}
	}
}


void opcaoRange(char *nomef){ 
	int acao=11;

	printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s,%d\">\n",nomef,acao);
			printf("<image x=903 y=563 xlink:href=\"%s\"/>\n", TOGGLE_RANGE);
	printf("</a>\n");
}


void selectRange(ESTADO e, char *nomef){ // funcao que permite selecionar um inimigo para mostrar o seu range
	int i=0;
	
	if(e.range == 0)
		while(i<e.num_inimigos){
			if(e.inimigo[i].vida>0 && inRange(e,i)==0){
				int acao=19;
				printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s,%d,%d\">\n",nomef,acao,i);
					print_hex(e.inimigo[i].x, e.inimigo[i].y);
				printf("</a>\n");
			}	
			i++;	
		}
	else print_enemy(e);	
}


int atk_Player(int vida, int crit, int atk, int sword){
	srand(time(NULL));
	int x=rand()%10;

	if(x<crit) vida=vida-2*(atk+atk*sword);
	else vida=vida-(atk+atk*sword);
	if (vida<0) vida=0;

	return vida;
}


void bola_Fogo(ESTADO e, char *nomef){
	int acao=20, i=0;

	if(e.bolaFogo == 1)
		while(i<e.num_inimigos){
			if(e.inimigo[i].vida>0){
				int acao=21;
				printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s,%d,%d\">\n",nomef,acao,i);
					print_hex(e.inimigo[i].x, e.inimigo[i].y);
				printf("</a>\n");
			}	
			i++;	
		}
	printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s,%d\">\n", nomef, acao);
			printf("<image x=753 y=416 xlink:href=\"%s\"/>\n", SQUARE_LINK);
	printf("</a>\n");
	printf("<text x=754 y=453 font-family=Verdana font-size=9 fill=white> %d </text> \n", 3);
}


void print_bolaFogo_animation(int x, int y){

	print_imageID(x, y, BOLA_FOGO, 20);
	printf("<animate xlink:href=#20 attributeName='opacity' to='0' dur='1.2s' begin='0s' fill='freeze' /> \n");	
}


void mov_Flash(ESTADO e, char *nomef){
	int acao=22;

	if(e.flash == 1){
		if(casaLivre(e, e.jog.x+2, e.jog.y)==1) print_move(e, +2, +0, nomef, 23);
		if(casaLivre(e, e.jog.x-2, e.jog.y)==1) print_move(e, -2, +0, nomef, 24);
		if(e.jog.x%2==0){
			if(casaLivre(e, e.jog.x-1, e.jog.y-1)==1) print_move(e, -1, -1, nomef, 25);
			if(casaLivre(e, e.jog.x+1, e.jog.y-1)==1) print_move(e, +1, -1, nomef, 26);
			if(casaLivre(e, e.jog.x-1, e.jog.y+2)==1) print_move(e, -1, +2, nomef, 27);
			if(casaLivre(e, e.jog.x+1, e.jog.y+2)==1) print_move(e, +1, +2, nomef, 28);
		}
		else{
			if(casaLivre(e, e.jog.x-1, e.jog.y-2)==1) print_move(e, -1, -2, nomef, 29);
			if(casaLivre(e, e.jog.x+1, e.jog.y-2)==1) print_move(e, +1, -2, nomef, 30);
			if(casaLivre(e, e.jog.x-1, e.jog.y+1)==1) print_move(e, -1, +1, nomef, 31);
			if(casaLivre(e, e.jog.x+1, e.jog.y+1)==1) print_move(e, +1, +1, nomef, 32);
		}
	}		
	printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s,%d\">\n", nomef, acao);
			printf("<image x=711 y=512 xlink:href=\"%s\"/>\n", SQUARE_LINK);
	printf("</a>\n");
	printf("<text x=712 y=550 font-family=Verdana font-size=9 fill=white> %d </text> \n", 2);
} 

void print_flash_animation(int acao){
	if (acao==23) printf("<animateMotion xlink:href=#jog dur=0.75s begin=0s fill=freeze path='M%d,%d 0,0' /> \n", -120, 0);
	else if (acao==24) printf("<animateMotion xlink:href=#jog dur=0.75s begin=0s fill=freeze path='M%d,%d 0,0' /> \n", 120, 0);
	else if (acao==25 || acao==29) printf("<animateMotion xlink:href=#jog dur=0.75s begin=0s fill=freeze path='M%d,%d 0,0' /> \n", 60, 105);
	else if (acao==26 || acao==30) printf("<animateMotion xlink:href=#jog dur=0.75s begin=0s fill=freeze path='M%d,%d 0,0' /> \n", -60, 105);
	else if (acao==27 || acao==31) printf("<animateMotion xlink:href=#jog dur=0.75s begin=0s fill=freeze path='M%d,%d 0,0' /> \n", 60, -105);
	else if (acao==28 || acao==32) printf("<animateMotion xlink:href=#jog dur=0.75s begin=0s fill=freeze path='M%d,%d 0,0' /> \n", -60, -105);

}

void espada_giratoria(char *nomef){
	int acao=18;

	printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s,%d\">\n", nomef, acao);
			printf("<image x=711 y=416 xlink:href=\"%s\"/>\n", SQUARE_LINK);
	printf("</a>\n");
	printf("<text x=712 y=453 font-family=Verdana font-size=9 fill=white> %d </text> \n", 2);
}


void print_espadaGiratoria_animation(int x, int y){
	if(x==10){
		printf("<image id=espada x=%d y=%d xlink:href=\"%s\"/>\n", (x-1)*60, y*70+35, ESPADA_GIR2);
		printf("<animate xlink:href=#espada attributeName='opacity' to='0' dur='1s' begin='0s' fill='freeze' /> \n");
	}
	else if (x%2==0){
		printf("<image id=espada x=%d y=%d xlink:href=\"%s\"/>\n", (x-1)*60, y*70-30, ESPADA_GIR);
		printf("<animate xlink:href=#espada attributeName='opacity' to='0' dur='1s' begin='0s' fill='freeze' /> \n");
	}
	else{
		printf("<image id=espada x=%d y=%d xlink:href=\"%s\"/>\n", (x-1)*60, y*70-65, ESPADA_GIR);
		printf("<animate xlink:href=#espada attributeName='opacity' to='0' dur='1s' begin='0s' fill='freeze' /> \n");
	}
}


void dormir(char *nomef){
	int acao=45;

	printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s,%d\">\n", nomef, acao);
			printf("<image x=753 y=512 xlink:href=\"%s\"/>\n", SQUARE_LINK);
	printf("</a>\n");
	printf("<text x=754 y=550 font-family=Verdana font-size=9 fill=white> %d </text> \n", 0);
}

void print_dormir_animation(){
	printf("<animate attributeName='opacity' to='0' dur='1s' begin='0s' fill='freeze' /> \n");
	printf("<animate attributeName='opacity' to='1' dur='1s' begin='1s' fill='freeze' /> \n");
}


void print_image(int px, int py, char *imagem){
	if(px%2==0) printf("<image x=%d y=%d width=80 height=70 xlink:href=\"%s\"/>\n", px*60, py*70+35, imagem); 
	else printf("<image x=%d y=%d width=80 height=70 xlink:href=\"%s\"/>\n", px*60, py*70, imagem);
} 



void print_imageID(int px, int py, char *imagem, int jogador){
	if(jogador==-1)
		if(px%2==0) {
			printf("<image id=jog x=%d y=%d width=80 height=70 xlink:href=\"%s\"/>\n", px*60, py*70+35, imagem);
		}
		else printf("<image id=jog x=%d y=%d width=80 height=70 xlink:href=\"%s\"/>\n", px*60, py*70, imagem);
	else 
		if(px%2==0) {
			printf("<image id=%d x=%d y=%d width=80 height=70 xlink:href=\"%s\"/>\n", jogador, px*60, py*70+35, imagem);
		}
		else printf("<image id=%d x=%d y=%d width=80 height=70 xlink:href=\"%s\"/>\n", jogador, px*60, py*70, imagem);
} 


void print_player(ESTADO e, char *nomef){
	print_imageID(e.jog.x, e.jog.y, PLAYER,-1);
	if(e.jog.x%2==0){
		print_move(e, +1, +0, nomef, 0);
		print_move(e, +0, +1, nomef, 0);
		print_move(e, +0, -1, nomef, 0);
		print_move(e, -1, +0, nomef, 0);
		print_move(e, +1, +1, nomef, 0);
		print_move(e, -1, +1, nomef, 0);
	}
	else{
		print_move(e, +1, +0, nomef, 0);
		print_move(e, +0, +1, nomef, 0);
		print_move(e, +0, -1, nomef, 0);
		print_move(e, -1, +0, nomef, 0);
		print_move(e, +1, -1, nomef, 0);
		print_move(e, -1, -1, nomef, 0);
	}
} 


/** \brief Função que imprime todos os inimigos.

	@param e
*/
void print_enemy(ESTADO e){
	int i;

	for(i = 0; i < e.num_inimigos; i++){
		if(e.inimigo[i].vida !=0 && e.inimigo[i].tipo==1) print_imageID(e.inimigo[i].x, e.inimigo[i].y, ENEMY, i);
		if(e.inimigo[i].vida !=0 && e.inimigo[i].tipo==2) print_imageID(e.inimigo[i].x, e.inimigo[i].y, ENEMY2, i);
		if(e.inimigo[i].vida !=0 && e.inimigo[i].tipo==3) {
			print_imageID(e.inimigo[i].x, e.inimigo[i].y, ENEMY3, i);
			print_imageID(e.inimigo[i].x, e.inimigo[i].y, ROCK, i+30);
		}
		if(e.inimigo[i].vida !=0 && e.inimigo[i].tipo==4) print_imageID(e.inimigo[i].x, e.inimigo[i].y, BOSS1, i);
		if(e.inimigo[i].vida !=0 && e.inimigo[i].tipo==5) print_imageID(e.inimigo[i].x, e.inimigo[i].y, ENEMY5, i);
		if(e.inimigo[i].vida !=0 && e.inimigo[i].tipo==6) print_imageID(e.inimigo[i].x, e.inimigo[i].y, ENEMY6, i);
		if(e.inimigo[i].vida !=0 && e.inimigo[i].tipo==7) {
			print_imageID(e.inimigo[i].x, e.inimigo[i].y, ENEMY7, i);
			print_imageID(e.inimigo[i].x, e.inimigo[i].y, ROCK, i+30);
		}
		if(e.inimigo[i].vida !=0 && e.inimigo[i].tipo==8) print_imageID(e.inimigo[i].x, e.inimigo[i].y, BOSS2, i);
	}
}

void print_rangeEnemy(ESTADO e){
	int i, x, y,px,py;

	for(i=0;i<e.num_inimigos;i++)
		if(e.inimigo[i].range == 1 && e.inimigo[i].vida >0){
			x = e.inimigo[i].x; px=e.jog.x;
			y = e.inimigo[i].y; py=e.jog.y;
			if(casaLivre(e, x+1, y)==1 ||(x+1==px && y==py)) print_image(x+1, y, RANGEATTACK);
			if(casaLivre(e, x-1, y)==1 ||(x-1==px && y==py)) print_image(x-1, y, RANGEATTACK);
			if(casaLivre(e, x, y+1)==1 ||(x==px && (y+1)==py)) print_image(x, y+1, RANGEATTACK);
			if(casaLivre(e, x, y-1)==1 ||(x==px && (y-1)==py)) print_image(x, y-1, RANGEATTACK);
			if(x%2==0){
				if(casaLivre(e, x+1, y+1)==1 ||(x+1==px && y+1==py)) print_image(x+1, y+1, RANGEATTACK);
				if(casaLivre(e, x-1, y+1)==1 ||(x-1==px && y+1==py)) print_image(x-1, y+1, RANGEATTACK);
			}
			if(x%2==1){
				if(casaLivre(e, x-1, y-1)==1 ||(x-1==px && y-1==py)) print_image(x-1, y-1, RANGEATTACK);
				if(casaLivre(e, x+1, y-1)==1 ||(x+1==px && y-1==py)) print_image(x+1, y-1, RANGEATTACK);
			}
			if(e.inimigo[i].tipo==3 || e.inimigo[i].tipo==7){
				if(casaLivre(e, x-2, y)==1 ||(x-2==px && y==py)) print_image(x-2, y, RANGEATTACK);
				if(casaLivre(e, x+2, y)==1 ||(x+2==px && y==py)) print_image(x+2, y, RANGEATTACK);
				if(x%2==0){
					if(casaLivre(e, x-1, y-1)==1 ||(x-1==px && y-1==py)) print_image(x-1, y-1, RANGEATTACK);
					if(casaLivre(e, x+1, y-1)==1 ||(x+1==px && y-1==py)) print_image(x+1, y-1, RANGEATTACK);
					if(casaLivre(e, x+1, y+2)==1 ||(x+1==px && y+2==py)) print_image(x+1, y+2, RANGEATTACK);
					if(casaLivre(e, x-1, y+2)==1 ||(x-1==px && y+2==py)) print_image(x-1, y+2, RANGEATTACK);
				}
				else{
					if(casaLivre(e, x-1, y-2)==1 ||(x-1==px && y-2==py)) print_image(x-1, y-2, RANGEATTACK);
					if(casaLivre(e, x+1, y-2)==1 ||(x+1==px && y-2==py)) print_image(x+1, y-2, RANGEATTACK);
					if(casaLivre(e, x+1, y+1)==1 ||(x+1==px && y+1==py)) print_image(x+1, y+1, RANGEATTACK);
					if(casaLivre(e, x-1, y+1)==1 ||(x-1==px && y+1==py)) print_image(x-1, y+1, RANGEATTACK);

				}
			}
	}
}


void print_wall(ESTADO e){
	int i;

	if (e.nivel<=5) 
		for(i = 0; i < e.num_obstaculos; i++)
			print_image(e.obstaculo[i].x, e.obstaculo[i].y, WALL);
	else for(i = 0; i < e.num_obstaculos; i++)
			print_image(e.obstaculo[i].x, e.obstaculo[i].y, WALL2);
}


void print_door(ESTADO e){ 
	print_image(e.door.x, e.door.y, DOOR);
}


void print_specific_item(int i, ESTADO e){ 
	int posx, posy, item=-1;
	if (i==(-1)){
		posx=e.treasure.x;
		posy=e.treasure.y;
		item=e.item.tipo;
	}
	else if(e.inimigo[i].visivel==1){
		posx=e.inimigo[i].x;
		posy=e.inimigo[i].y;
		item=e.inimigo[i].item;
	}

	if (item==0) print_image(posx, posy, SCORE_5);
	if (item==1) print_image(posx, posy, SCORE_10);
	if (item==2) print_image(posx, posy, SCORE_25);
	if (item==3) print_image(posx, posy, VIDADROP);
	if (item==4) print_image(posx, posy, MANADROP);
	if (item==5) print_image(posx, posy, SWORD);
	if (item==6) print_image(posx, posy, CRIT);
	if (item==7) print_image(posx, posy, SWORD_PU);
	if (item==8) print_image(posx, posy, SHIELD_PU);

}
 


void print_item(ESTADO e){
	int i;

	for(i=0; i<e.num_inimigos; i++)
		print_specific_item(i, e);
}


void print_treasure(ESTADO e){
	if (e.treasure.visivel==1) print_image(e.treasure.x, e.treasure.y, TREASURE);
	else if(e.item.visivel==1) print_specific_item(-1,e);
}



void print_menu_lateral(ESTADO e){
	if (e.nivel<=5) printf("<image x=0 y=0 width=980 height=600 xlink:href=\"%s\"/>\n", MENU);
	else printf("<image x=0 y=0 width=980 height=600 xlink:href=\"%s\"/>\n", MENU2);
}


void print_dead_screen(char *nomef){
	printf("<image x=0 y=0 width=980 height=600 xlink:href=\"%s\"/>\n", DEAD);

	printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s,%d\">\n", nomef, 44);
		printf("<image x=830 y=535 xlink:href=\"%s\"/>\n", MENU_BUTTON2);
	printf("</a>\n");
}


void print_score_screen(char *nomef){
	printf("<image x=0 y=0 width=980 height=600 xlink:href=\"%s\"/>\n", HIGHSCORE_SCREEN);

	printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s,%d\">\n", nomef, 42);
		printf("<image x=830 y=535 xlink:href=\"%s\"/>\n", BACK_BUTTON);
	printf("</a>\n");
}


void print_stats(ESTADO e){
	int i;

	for (i=0;i<e.jog.vida;i++) 
		printf("<image x=%d y=36 xlink:href=\"%s\"/>\n", 600+81+80+10*i, VIDA); // Vida

	for (i=0;i<e.jog.mana;i++) 
		printf("<image x=%d y=80 xlink:href=\"%s\"/>\n", 600+81+80+20*i, MANA); // Mana

	printf("<text x=877 y=207 font-family=Verdana font-size=22 fill=white> %d </text> \n", e.nivel); // Nivel
	if(e.jog.powerUp_sword==1) printf("<text x=753 y=207 font-family=Verdana font-size=22 fill=green> %d </text> \n", e.jog.atk*2); // Ataque
	else printf("<text x=753 y=207 font-family=Verdana font-size=22 fill=white> %d </text> \n", e.jog.atk);
	printf("<text x=753 y=242 font-family=Verdana font-size=22 fill=white> %d%c </text> \n", e.jog.crit*10, '%'); // Crit
	printf("<text x=877 y=242 font-family=Verdana font-size=22 fill=white> %d </text> \n", e.score); // Score
}


void print_start(char *nomef){
	printf("<image x=0 y=0 width=980 height=600 xlink:href=\"%s\"/>\n", TITLE);

	printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s,%d\">\n", nomef, 40);
		printf("<image x=378 y=351 xlink:href=\"%s\"/>\n", START_BUTTON);
	printf("</a>\n");

	printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s,%d\">\n", nomef, 41);
		printf("<image x=880 y=515 xlink:href=\"%s\"/>\n", TOPSCORE_BUTTON);
	printf("</a>\n");	
}


void print_rangeMov(ESTADO e, int px, int py){
	if(casaLivre(e, px, py)==1) print_image(px, py, RANGEMOV);
} 



void print_rangeAttack (ESTADO e, int px, int py){
	if(isEnemy(e, px, py)!=(-1)) print_image(px, py, RANGEATTACK);
}


void print_inventory(ESTADO e, char *nomef){
	int i=0, acao;

	if(e.jog.item_vida>0){
		acao=13;
		printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s,%d\">\n", nomef, acao);
			printf("<image x=%d y=312 width=39 height=39 xlink:href=\"%s\"/>\n", 708+43*i, VIDA_INV);
		printf("</a>\n");	
		printf("<text x=%d y=350 font-family=Verdana font-size=9 fill=white> %d </text> \n", 600+29+80+40*i, e.jog.item_vida);
		i++;
	}
	if(e.jog.item_mana>0){
		acao=14;
		printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s,%d\">\n", nomef, acao);
			printf("<image x=%d y=312 width=39 height=39 xlink:href=\"%s\"/>\n", 708+43*i, MANA_INV);
		printf("</a>\n");	
		printf("<text x=%d y=350 font-family=Verdana font-size=9 fill=white> %d </text> \n", 600+29+80+2*i+40*i, e.jog.item_mana);
		i++;
	}
	if(e.jog.item_sword>0){
		acao=15;
		printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s,%d\">\n", nomef, acao);
			printf("<image x=%d y=312 width=39 height=39 xlink:href=\"%s\"/>\n", 708+43*i, SWORD_PU_INV); // mudar IMAGEM
		printf("</a>\n");	
		printf("<text x=%d y=350 font-family=Verdana font-size=9 fill=white> %d </text> \n", 600+29+80+2*i+40*i, e.jog.item_sword);
		i++;
	}
	if(e.jog.item_shield>0){
		acao=16;
		printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s,%d\">\n", nomef, acao);
			printf("<image x=%d y=312 width=39 height=39 xlink:href=\"%s\"/>\n", 708+43*i, SHIELD_PU_INV);
		printf("</a>\n");	
		printf("<text x=%d y=350 font-family=Verdana font-size=9 fill=white> %d </text> \n", 600+29+80+2*i+40*i, e.jog.item_shield);
		i++;
	}
}

 
void print_animation(int difx,int dify, int posx, int id){
	if(id==-1)
		if((difx==0&&dify==-1)||(difx==0&&dify==1))
			printf("<animateMotion xlink:href=#jog dur=0.5s begin=0s fill=freeze path='M%d,%d 0,0' /> \n", 0, -(70*dify));
		else if(difx==1&&dify==1)
			printf("<animateMotion xlink:href=#jog dur=0.5s begin=0s fill=freeze path='M%d,%d 0,0' /> \n", -60, -35);
		else if(difx==-1&&dify==-1)
			printf("<animateMotion xlink:href=#jog dur=0.5s begin=0s fill=freeze path='M%d,%d 0,0' /> \n", 60, 35);
		else if(difx==-1&&dify==1)
			printf("<animateMotion xlink:href=#jog dur=0.5s begin=0s fill=freeze path='M%d,%d 0,0' /> \n", 60, -35);
		else if(difx==1&&dify==-1)
			printf("<animateMotion xlink:href=#jog dur=0.5s begin=0s fill=freeze path='M%d,%d 0,0' /> \n", -60, 35);
		else if(posx%2==0)
			printf("<animateMotion xlink:href=#jog dur=0.5s begin=0s fill=freeze path='M%d,%d 0,0' /> \n", -(60*difx), -35);
		else 
			printf("<animateMotion xlink:href=#jog dur=0.5s begin=0s fill=freeze path='M%d,%d 0,0' /> \n", -(60*difx), 35);
	else
		if((difx==0&&dify==-1)||(difx==0&&dify==1))
			printf("<animateMotion xlink:href=#%d dur=0.5s begin=0s fill=freeze path='M%d,%d 0,0' /> \n", id, 0, -(70*dify));
		else if(difx==1&&dify==1)
			printf("<animateMotion xlink:href=#%d dur=0.5s begin=0s fill=freeze path='M%d,%d 0,0' /> \n", id, -60, -35);
		else if(difx==-1&&dify==-1)
			printf("<animateMotion xlink:href=#%d dur=0.5s begin=0s fill=freeze path='M%d,%d 0,0' /> \n", id, 60, 35);
		else if(difx==-1&&dify==1)
			printf("<animateMotion xlink:href=#%d dur=0.5s begin=0s fill=freeze path='M%d,%d 0,0' /> \n", id, 60, -35);
		else if(difx==1&&dify==-1)
			printf("<animateMotion xlink:href=#%d dur=0.5s begin=0s fill=freeze path='M%d,%d 0,0' /> \n", id, -60, 35);
		else if(posx%2==0)
			printf("<animateMotion xlink:href=#%d dur=0.5s begin=0s fill=freeze path='M%d,%d 0,0' /> \n", id, -(60*difx), -35);
		else 
			printf("<animateMotion xlink:href=#%d dur=0.5s begin=0s fill=freeze path='M%d,%d 0,0' /> \n", id, -(60*difx), 35);
}


void print_attack_animation(ESTADO e, int numI){
	int difx, dify, id;

	if(e.inimigo[numI].tipo==3 || e.inimigo[numI].tipo==7){
		id=numI+30;
		difx=e.jog.x-e.inimigo[numI].x;
		dify=e.jog.y-e.inimigo[numI].y;

		printf("<animateMotion xlink:href=#%d dur=0.75s begin=0.3s fill=freeze path='M%d,%d 0,0' /> \n", id, -60*difx, 70*dify);
		printf("<animate xlink:href=#%d attributeName='opacity' to='0' dur='0.2s' begin='0.75s' fill='freeze' /> \n", id);
	}
		
	else {
		difx=e.jog.x-e.inimigo[numI].x;
		dify=e.jog.y-e.inimigo[numI].y;
		printf("<animateMotion xlink:href=#%d dur=0.5s begin=0.5s fill=freeze path='M0,0, %d,%d 0,0' /> \n", numI, 60*difx, 70*dify);
	}

}


void print_board(ESTADO e){ 
	int x, y;
	if(e.nivel<=5){
		for (x=0;x<11;x++)
			for (y=0;y<8;y++) 
				if(x%2==0) printf("<image x=%d y=%d width=%d height=%d xlink:href=\"%s\"/>\n", x*60, y*70+35, 80, 70,HEX_FLOOR); 
				else printf("<image x=%d y=%d width=%d height=%d xlink:href=\"%s\"/>\n", x*60, y*70, 80, 70, HEX_FLOOR);
	}
	else{
		for (x=0;x<11;x++)
			for (y=0;y<8;y++) 
				if(x%2==0) printf("<image x=%d y=%d width=%d height=%d xlink:href=\"%s\"/>\n", x*60, y*70+35, 80, 70,HEX_FLOOR_GRASS); 
				else printf("<image x=%d y=%d width=%d height=%d xlink:href=\"%s\"/>\n", x*60, y*70, 80, 70, HEX_FLOOR_GRASS);
	}
}

 
void print_hex(int x, int y){
	if(x%2==1) {
		printf("<polygon points='%d,%d %d,%d %d,%d %d,%d %d,%d %d,%d' fill=%s stroke=%s opacity='0'/> \n", 20+60*x,70*y,60+60*x,70*y,80+60*x,35+70*y,60+60*x,70+70*y,20+60*x,70+70*y,60*x,35+70*y,"green","purple");	
	}
	else{
		printf("<polygon points='%d,%d %d,%d %d,%d %d,%d %d,%d %d,%d' fill=%s stroke=%s opacity='0'/> \n", 20+60*x,70*y+35,60+60*x,70*y+35,80+60*x,35+70*y+35,60+60*x,70+70*y+35,20+60*x,70+70*y+35,60*x,35+70*y+35,"green","purple");
	}
}


void guardar_estado(ESTADO e, char *nomef){ // no fim do parser guardar_estado(e, nomef)
	char path[200];
	FILE *fp;

	strcpy(path, "/var/www/html/estado/");
	strcat(path, nomef);

	fp=fopen(path, "w");
	if (fp==NULL) printf ("Erro");
	else{
		fprintf(fp,"%s\n", estado2str(e));
		fclose(fp);
	}
}

ESTADO ler_estado(char *nomef){
	ESTADO e;
	char path[200];
	FILE *fp;
	char st[5000];
	int x;

	strcpy(path, "/var/www/html/estado/");
	strcat(path, nomef);

	fp=fopen(path, "r");
	if (fp==NULL) printf ("Erro");
	else{ 
		x=fscanf(fp, "%s\n", st);
		if (x==0) printf("Erro");
		fclose(fp);
	}
	e=str2estado(st);

	return e;
}


void print_noMana(){
	printf("<image id=noMana x=788 y=107 xlink:href=\"%s\"/>\n", NO_MANA);
	printf("<animate xlink:href=#noMana attributeName='opacity' to='0' dur='1.2s' begin='0s' fill='freeze' /> \n");	
}

void print_end_game(int score, char *nomef){
	printf("<image x=0 y=0 width=980 height=600 xlink:href=\"%s\"/>\n", END_SCREEN);
	printf("<text x=420 y=350 font-family=Verdana font-size=80 stroke= black fill=white> %d </text> \n", score);

	printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s,%d\">\n", nomef, 44);
		printf("<image x=830 y=535 xlink:href=\"%s\"/>\n", MENU_BUTTON1);
	printf("</a>\n");
}

 
ESTADO processar_acao(ESTADO e, int acao, char *nomef, int numI){
	int i;

	if (acao==0 || acao==10) e=inicializar(4,0,0,0,20,10,1,0,1,1,1,1,1);
	else{
		e=ler_estado(nomef);
		int x=e.jog.x; int y=e.jog.y;
		if (acao==1){
			e = inicializar(++e.nivel, e.door.x, e.door.y, e.score+10, e.jog.vida, e.jog.mana, e.jog.atk, e.jog.crit, e.jog.item_vida, e.jog.item_mana, e.jog.item_sword, e.jog.item_shield, 1);
		}
		else if (acao==2){
			e=processar_mov(e,x,y-1);
		}
		else if (acao==3){
			e=processar_mov(e,x,y+1);
		}
		else if (acao==4){
			e=processar_mov(e,x-1,y);
		}
		else if (acao==5){
			e=processar_mov(e,x+1,y);
		}
		else if (acao==6){
			e=processar_mov(e,x+1,y+1);
		}
		else if (acao==7){
			e=processar_mov(e,x-1,y-1);
		}
		else if (acao==8){
			e=processar_mov(e,x-1,y+1);
		}
		else if (acao==9){
			e=processar_mov(e,x+1,y-1);
		}
		else if(acao==11){
				e.range = abs(e.range-1);
				if(e.range == 1)
					for(i=0;i<e.num_inimigos;i++)
						if(e.inimigo[i].vida!=0) e.inimigo[i].range=1;
				if(e.range == 0)
					for(i=0;i<e.num_inimigos;i++)
						if(e.inimigo[i].vida!=0) e.inimigo[i].range=0;
		}
		else if(acao==13){
			e.jog.item_vida--;
			if(e.jog.vida<18) e.jog.vida+=2;
			else e.jog.vida=20;
		}
		else if(acao==14){
			e.jog.item_mana--;
			if(e.jog.mana<8) e.jog.mana+=2;
			else e.jog.mana=10;
		}
		else if(acao==15){
			e.jog.item_sword--;
			e.jog.powerUp_sword=1;
		}
		else if(acao==16){
			e.jog.item_shield--;
			e.jog.powerUp_shield=1;
		}
		else if(acao==17){
			e.vidas = abs(e.vidas -1);
			if(e.vidas == 1)
				for(i=0;i<e.num_inimigos;i++)
					if(e.inimigo[i].vida!=0) e.inimigo[i].showVida=1;
			if(e.vidas == 0)
				for(i=0;i<e.num_inimigos;i++)
					if(e.inimigo[i].vida!=0) e.inimigo[i].showVida=0;	
		}
		else if(acao==18){
			if (e.jog.mana>=2){
				for(i=0; i<e.num_inimigos; i++){
					if(e.inimigo[i].vida>0 && (abs(e.jog.x-e.inimigo[i].x)+abs(e.jog.y-e.inimigo[i].y))==1) 
						if (e.inimigo[i].vida>1) e.inimigo[i].vida--;
						else{
							e.inimigo[i].vida=0;
							e.score+=5;
							if(e.inimigo[numI].tipo==(4*(e.nivel/5))) e.score+=45;
							if(e.inimigo[i].item<=8) e.inimigo[i].visivel=1;
						}
					else if( ((e.inimigo[i].vida>0) && (e.jog.x%2==0) && ( (e.jog.x==e.inimigo[i].x+1) || (e.jog.x==e.inimigo[i].x-1) ) && (e.jog.y==e.inimigo[i].y-1) && (abs(e.jog.x-e.inimigo[i].x)+abs(e.jog.y-e.inimigo[i].y)==2)) || 
							 ((e.inimigo[i].vida>0) && (e.jog.x%2==1) && ( (e.jog.x==e.inimigo[i].x+1) || (e.jog.x==e.inimigo[i].x-1) ) && (e.jog.y==e.inimigo[i].y+1) && (abs(e.jog.x-e.inimigo[i].x)+abs(e.jog.y-e.inimigo[i].y)==2)) ){
						if (e.inimigo[i].vida>1) e.inimigo[i].vida--;
						else{
							e.inimigo[i].vida=0;
							e.score+=5;
							if(e.inimigo[numI].tipo==(4*(e.nivel/5))) e.score+=45;
							if(e.inimigo[i].item<=8) e.inimigo[i].visivel=1;
						}
					}
				}	
				e.jog.mana-=2;
			}
			else e.noMana=1;
		}
		else if(acao==19){
			e.inimigo[numI].range=abs(e.inimigo[numI].range-1);
		}
		else if(acao==20){
			if(e.jog.mana>=3) e.bolaFogo=abs(e.bolaFogo-1);
			else e.noMana=1;
		}		
		else if(acao==21){
			if(e.inimigo[numI].vida>2) e.inimigo[numI].vida-=2;
			else {
				e.inimigo[numI].vida=0;
				e.score+=5;
				if(e.inimigo[numI].tipo==(4*(e.nivel/5))) e.score+=45;
				if(e.inimigo[numI].item<=8) e.inimigo[numI].visivel=1;
			}
			e.jog.mana-=3;
			e=enemyMove(e);
			e.bolaFogo=2;
		}
		else if(acao==22){
			if(e.jog.mana>=2) e.flash=abs(e.flash-1);
			else e.noMana=1;
		}		
		else if(acao==23){
			e=processar_mov(e, x+2, y);
			e.jog.mana-=2;
			e.flash=2;
			e=enemyMove(e);

		}
		else if(acao==24){
			e=processar_mov(e, x-2, y);
			e.jog.mana-=2;
			e.flash=2;
			e=enemyMove(e);
		}
		else if(acao==25){
			e=processar_mov(e, x-1, y-1);
			e.jog.mana-=2;
			e.flash=2;
			e=enemyMove(e);
		}
		else if(acao==26){
			e=processar_mov(e, x+1, y-1);
			e.jog.mana-=2;
			e.flash=2;
			e=enemyMove(e);
		}
		else if(acao==27){
			e=processar_mov(e, x-1, y+2);
			e.jog.mana-=2;
			e.flash=2;
			e=enemyMove(e);
		}
		else if(acao==28){
			e=processar_mov(e, x+1, y+2);
			e.jog.mana-=2;
			e.flash=2;
			e=enemyMove(e);
		}
		else if(acao==29){
			e=processar_mov(e, x-1, y-2);
			e.jog.mana-=2;
			e.flash=2;
			e=enemyMove(e);
		}
		else if(acao==30){
			e=processar_mov(e, x+1, y-2);
			e.jog.mana-=2;
			e.flash=2;
			e=enemyMove(e);
		}
		else if(acao==31){
			e=processar_mov(e, x-1, y+1);
			e.jog.mana-=2;
			e.flash=2;
			e=enemyMove(e);
		}
		else if(acao==32){
			e=processar_mov(e, x+1, y+1);
			e.jog.mana-=2;
			e.flash=2;
			e=enemyMove(e);
		}
		else if(acao==40){
			e.screen=1;
		}
		else if(acao==41){
			e.screen=2;
		}
		else if(acao==42 || acao==44){
			e.screen=0;
		}
		else if(acao==43){
			e.screen=3;
		}
		else if(acao==45){
			if(e.jog.vida<=18) e.jog.vida+=2;
			else e.jog.vida=20;
			if(e.jog.mana<=8) e.jog.mana+=2;
			else e.jog.mana=10;
			e=enemyMove(e);
		}
	}
	return e;
}	


ESTADO processar_mov(ESTADO e, int posx, int posy){
	int i,difx,dify;

	if (casaLivre(e, posx, posy)==1){
		difx=posx-e.jog.x,dify=posy-e.jog.y;
		e.jog.x=posx;
		e.jog.y=posy;
		print_animation(difx,dify,posx,-1);
	}
	else if(isItem(e, posx, posy)!=(-1)){
		i=isItem(e, posx, posy);
		e=catchItem(e.inimigo[i].item, e);
		e.inimigo[i].visivel=0;
	}
	else if(isEnemy(e, posx, posy)!=(-1)){ 
		i=isEnemy(e, posx, posy);
		e.inimigo[i].vida=atk_Player(e.inimigo[i].vida, e.jog.crit, e.jog.atk, e.jog.powerUp_sword);
		if(e.inimigo[i].vida==0){
			e.score+=5;
			if(e.inimigo[i].tipo==(4*(e.nivel/5))) e.score+=45;

			if (e.inimigo[i].item<=8) e.inimigo[i].visivel=1;
		}
	}
	else if(posx==e.treasure.x && posy==e.treasure.y && e.treasure.visivel==1){
		e=itemTesouro(e, posx, posy);
		e.treasure.visivel=0;
		e.item.visivel=1;
	}
	else if(posx==e.item.x && posy==e.item.y && e.item.visivel==1){
		e.item.visivel=0;
		e=catchItem(e.item.tipo, e);
	}
	e=enemyMove(e);

	return e;
}
 
void parser(){
	ESTADO e={0};
    int num,acao, i=0, j;
    char nomef[100];
    char *args = getenv("QUERY_STRING");

    if(strlen(args) == 0){
        acao=0;
        strcpy(nomef,"Default");
    }
    else{ 
    	num=sscanf(args,"%[^,],%d,%d", nomef, &acao, &i);
    	if (num==1) acao = 10;
    }

	if(acao==44) acao=10; // para voltar ao inicio e reiniciar o jogo

	e=processar_acao(e, acao, nomef, i); 

	if(e.screen==0) print_start(nomef);
	else if(e.nivel==11){
		guardar_Score(nomef, e.score);
		print_end_game(e.score, nomef);
	}

	else if(e.screen==2){
		print_score_screen(nomef); 
		print_score();
	}
	else if(e.jog.vida>0){ // e.screen==1
		print_menu_lateral(e); 
		print_board(e);
		print_wall(e);
		print_item(e);
		if(e.bolaFogo==1){
			for(j=0; j<e.num_inimigos;j++){
				if (e.inimigo[j].vida>0) 
					print_image(e.inimigo[j].x, e.inimigo[j].y, RANGEATTACK);
			}
		}
		print_enemy(e); 
		opcaoRange(nomef);
		selectRange(e,nomef);
		print_treasure(e);
		print_door(e);
		if (e.bolaFogo==2){
			print_bolaFogo_animation(e.inimigo[i].x, e.inimigo[i].y);
			e.bolaFogo=0;
		}
		if(acao==18) print_espadaGiratoria_animation(e.jog.x, e.jog.y);
		print_player(e, nomef);
		print_inventory(e, nomef);
		opcaoVida(nomef);
		print_enemy_vida(e);
		print_rangeEnemy(e);
		espada_giratoria(nomef);
		bola_Fogo(e, nomef);
		mov_Flash(e, nomef);
		dormir(nomef);
		print_stats(e);
		if (e.noMana==1){
			print_noMana();
			e.noMana=0;
		}
		if(acao==45) print_dormir_animation();
		if(e.flash==2){
			print_flash_animation(acao);
			e.flash=0;
		}
	}
	else{
		guardar_Score(nomef, e.score);
		print_dead_screen(nomef);
	}
	guardar_estado(e, nomef);	
}