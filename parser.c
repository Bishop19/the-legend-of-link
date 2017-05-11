#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "estado.h"
#include <time.h>



ESTADO inicializar(int nivel, int px, int py, int score, int vida, int mana, int atk, int crit, int vida_potion, int mana_potion, int sword, int shield){
	int i, x, y, z; 
	ESTADO e = {0};
	srand(time(NULL));
 
	e.nivel = nivel;
	e.acao = 0; 
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
	z=rand()%SIZE;
	if (z<8){
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
	while(i<NUM_INIMIGOS){
		x=rand()%11; 
		y=rand()%8;
		z=rand();
    		if(casaLivre(e,x,y)==1){
    			e.inimigo[i].x=x;
    			e.inimigo[i].y=y;
    			e.inimigo[i].tipo=tipoInimigo(e.nivel, rand());
    			e.inimigo[i].vida=vida_Inimigo(e.inimigo[i].tipo);
    			e.inimigo[i].atk=atk_Inimigo(e.inimigo[i].tipo);
    			e.inimigo[i].item=itemInimigo(z);
    			e.inimigo[i].visivel=0;
    			i++;
    			e.num_inimigos++;
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
	print_rangeMov(e, px, py);
	print_rangeAttack(e, px, py);
	printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s,%d\">\n", nomef, acao);
		print_hex(px,py);
	printf("</a>\n");
}


ESTADO enemyMove(ESTADO newE){
	int i, x, y, z=0;

	for(i=0; i<newE.num_inimigos; i++){
		if(newE.inimigo[i].vida>0){
			if (inRange(newE,i)==1){
				z+=newE.inimigo[i].atk;
				i++;
			}
			if (newE.jog.x > newE.inimigo[i].x){
				x=newE.inimigo[i].x + 1;
				if(casaLivre(newE, x, newE.inimigo[i].y)==1) newE.inimigo[i].x = x;
			}
			if (newE.jog.y > newE.inimigo[i].y){
				y=newE.inimigo[i].y + 1;
				if(casaLivre(newE, newE.inimigo[i].x, y)==1) newE.inimigo[i].y = y;
			}
			if (newE.jog.x < newE.inimigo[i].x){
				x=newE.inimigo[i].x - 1;
				if(casaLivre(newE, x, newE.inimigo[i].y)==1) newE.inimigo[i].x = x;
			}
			if (newE.jog.y < newE.inimigo[i].y){
					y=newE.inimigo[i].y - 1;
				if(casaLivre(newE, newE.inimigo[i].x, y)==1) newE.inimigo[i].y = y;
			}
		}
	}
	if (newE.jog.powerUp_shield==1) z=(z+1)/2;
	newE.jog.vida -= z;

	return newE;
}


int inRange(ESTADO e, int i){
	int r=0;
	if (e.jog.x == e.inimigo[i].x && e.inimigo[i].vida!=0 && (abs(e.jog.y-e.inimigo[i].y) == 1)) r=1;
	if (e.jog.y == e.inimigo[i].y && e.inimigo[i].vida!=0 && (abs(e.jog.x-e.inimigo[i].x) == 1)) r=1;
	if (e.inimigo[i].tipo==3 && abs(e.jog.x-e.inimigo[i].x)+abs(e.jog.y-e.inimigo[i].y) <= 2) r=1;
	return r;
}


int casaLivre (ESTADO e, int x, int y){
	int i=0, r=1;

	if(x<0 || y<0 || x>10 || y>7) r=0; // verificar se está fora do tabuleiro
	if(e.jog.x==x && e.jog.y==y) r=0; // verificar se está jogador
	if(e.door.x==x && e.door.y==y) r=0; // verificar se está por cima da porta
	if(isItem(e,x,y)!=(-1)) r=0; // verificar se está item
	if(e.item.x==x && e.item.y==y && e.item.visivel ==1)r=0;
	if(e.treasure.x==x && e.treasure.y==y && e.treasure.visivel==1) r=0; // verificar se está tesouro		 
	for(i=0; i < e.num_inimigos && r!=0; i++){ // verificar se está inimigo
		if(e.inimigo[i].x==x && e.inimigo[i].y==y && e.inimigo[i].vida!=0) r=0;
	}
	for(i=0; i < e.num_obstaculos && r!=0; i++){ // verificar se está obstáculo
		if(e.obstaculo[i].x==x && e.obstaculo[i].y==y) r=0;
	}
	return r;
}


int isEnemy (ESTADO e, int x, int y){ // funcao que retorna -1 se a casa nao tem inimigo, ou entao o seu numero
	int i, r=-1;

	for (i=0; i<e.num_inimigos && r==(-1); i++)
		if (x==e.inimigo[i].x && y==e.inimigo[i].y && e.inimigo[i].vida!=0) r=i;
	return r;
}


int isItem (ESTADO e, int px, int py){ // funcao que retorna -1 se a casa nao tem item, ou entao o inimigo que tem o item
	int i,r=(-1);

	for(i=0;i<e.num_inimigos && r==(-1) ;i++)
		if(e.inimigo[i].x==px &&  e.inimigo[i].y == py && e.inimigo[i].visivel==1) r=i;
	return r;
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
	else vida=2;

	return vida;
}


ESTADO itemTesouro (ESTADO e, int x, int y){
	srand(time(NULL));
	int z=rand()%24;

	e.item.x=x;
	e.item.y=y;

	if (z<=3) e.item.tipo=0;	
	else if (z>=4 && z<=6) e.item.tipo=1;
	else if (z==7 || z==8) e.item.tipo=2;
	else if (z>=9 && z<=11) e.item.tipo=3;
	else if (z>=12 && z<=14) e.item.tipo=4;
	else if (z>=15 && z<=17) e.item.tipo=5;
	else if (z==18 || z==19) e.item.tipo=6;	
	else if (z==20 || z==21) e.item.tipo=7;
	else if (z==22 || z==23) e.item.tipo=8;

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


int tipoInimigo(int nivel, int x){
	if (nivel==1) x=1;
	else if (nivel==2){
		if (x%3==0) x=1;
		else if (x%3==1) x=2;
		else x=3;
	}
	return x;
}

int itemInimigo(int rand){
	int item=rand%24;
	
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


void opcaoVida(ESTADO e){ // funcao que define se o range de ataque dos inimigos é ou nao impresso 
	ESTADO newE; int i;
	newE=e;
	
	newE.vidas = abs(e.vidas -1);
	if(newE.vidas == 1)
		for(i=0;i<e.num_inimigos;i++)
			if(newE.inimigo[i].vida!=0) newE.inimigo[i].showVida=1;
	if(newE.vidas == 0)
		for(i=0;i<e.num_inimigos;i++)
			if(newE.inimigo[i].vida!=0) newE.inimigo[i].showVida=0;	

	printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s\">\n", estado2str(newE));
			printf("<image x=750 y=550 width=20 height=20 xlink:href=\"%s\"/>\n", MANA);
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
			if(e.inimigo[i].x%2==1) printf("<text x=%d y=%d font-family=Verdana font-size=12 fill=white> %d </text> \n", x, y, vida); // Vida inimigo MUDAR!!!!!!!
			else printf("<text x=%d y=%d font-family=Verdana font-size=12 fill=white> %d </text> \n", x, y+35, vida); // Vida inimigo
		}
	}
}

void opcaoRange(ESTADO e){ // funcao que define se o range de ataque dos inimigos é ou nao impresso 
	ESTADO newE; int i;
	newE=e;
	
	newE.range = abs(e.range -1);
	if(newE.range == 1)
		for(i=0;i<e.num_inimigos;i++)
			if(newE.inimigo[i].vida!=0) newE.inimigo[i].range=1;
	if(newE.range == 0)
		for(i=0;i<e.num_inimigos;i++)
			if(newE.inimigo[i].vida!=0) newE.inimigo[i].range=0;	

	printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s\">\n", estado2str(newE));
			printf("<image x=700 y=550 width=20 height=20 xlink:href=\"%s\"/>\n", MANA);
	printf("</a>\n");
}

void selectRange(ESTADO e){ // funcao que permite selecionar um inimigo para mostrar o seu range
	ESTADO newE; int i=0;
	
	if(e.range == 0)
		while(i<e.num_inimigos){
			if(e.inimigo[i].vida>0 && inRange(e,i)==0){
				newE=e;
				newE.inimigo[i].range = abs(newE.inimigo[i].range-1);
				printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s\">\n", estado2str(newE));
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

ESTADO espada_giratoria(ESTADO e){
	int i;

	if (e.jog.mana>=2){
		for(i=0; i<e.num_inimigos; i++){
			if((abs(e.jog.x-e.inimigo[i].x)+abs(e.jog.y)-e.inimigo[i].y)==1) e.inimigo[i].vida--;
			else if((e.jog.x!=e.inimigo[i].x) && (e.jog.y!=e.inimigo[i].y) && (abs(e.jog.x-e.inimigo[i].x)+abs(e.jog.y-e.inimigo[i].y)==2)) e.inimigo[i].vida--;
		}
	}
	e.jog.mana-=2;

	return e;
}


void print_image(int px, int py, char *imagem){
	if(px%2==0) printf("<image x=%d y=%d width=80 height=70 xlink:href=\"%s\"/>\n", px*60, py*70 + 35,imagem); 
	else printf("<image x=%d y=%d width=80 height=70 xlink:href=\"%s\"/>\n", px*60, py*70,imagem);
} 


void print_player(ESTADO e, int acao, char *nomef){
	print_image(e.jog.x, e.jog.y, PLAYER);
	if(e.jog.x%2==0){
		print_move(e, +1, +0, nomef, acao);
		print_move(e, +0, +1, nomef, acao);
		print_move(e, +0, -1, nomef, acao);
		print_move(e, -1, +0, nomef, acao);
		print_move(e, +1, +1, nomef, acao);
		print_move(e, -1, +1, nomef, acao);
	}
	else{
		print_move(e, +1, +0, nomef, acao);
		print_move(e, +0, +1, nomef, acao);
		print_move(e, +0, -1, nomef, acao);
		print_move(e, -1, +0, nomef, acao);
		print_move(e, +1, -1, nomef, acao);
		print_move(e, -1, -1, nomef, acao);
	}
} 


void print_enemy(ESTADO e){
	int i;

	for(i = 0; i < e.num_inimigos; i++){
		if(e.inimigo[i].vida !=0 && e.inimigo[i].tipo==1) print_image(e.inimigo[i].x, e.inimigo[i].y, ENEMY);
		if(e.inimigo[i].vida !=0 && e.inimigo[i].tipo==2) print_image(e.inimigo[i].x, e.inimigo[i].y, ENEMY2);
		if(e.inimigo[i].vida !=0 && e.inimigo[i].tipo==3) print_image(e.inimigo[i].x, e.inimigo[i].y, ENEMY3);
	}
}

void print_enemy_specific(int x, int y, int tipo){
	if (tipo==1) print_image(x, y, ENEMY);
	else if (tipo==2) print_image(x, y, ENEMY2);
	else print_image(x, y, ENEMY3);
}

void print_rangeEnemy(ESTADO e){
	int i, x, y;

	for(i=0;i<e.num_inimigos;i++)
		if(e.inimigo[i].range == 1 && e.inimigo[i].vida >0){
			x = e.inimigo[i].x;
			y = e.inimigo[i].y;
			if(casaLivre(e,x+1,y)==1) print_rangeAttack(e, x+1, y);
			if(casaLivre(e,x-1,y)==1) print_rangeAttack(e, x-1, y);
			if(casaLivre(e,x,y+1)==1) print_rangeAttack(e, x, y+1);
			if(casaLivre(e,x,y-1)==1) print_rangeAttack(e, x, y-1);
	}
}


void print_wall(ESTADO e){
	int i;

	for(i = 0; i < e.num_obstaculos; i++)
		print_image(e.obstaculo[i].x, e.obstaculo[i].y, WALL);
}


void print_door(ESTADO e){ 
	print_image(e.door.x, e.door.y, DOOR);
}

void print_specific_item(int i, ESTADO e){ 
	if (e.inimigo[i].visivel==1){
		if (e.inimigo[i].item==0) print_image(e.inimigo[i].x, e.inimigo[i].y, SCORE_5);
		if (e.inimigo[i].item==1) print_image(e.inimigo[i].x, e.inimigo[i].y, SCORE_10);
		if (e.inimigo[i].item==2) print_image(e.inimigo[i].x, e.inimigo[i].y, SCORE_25);
		if (e.inimigo[i].item==3) print_image(e.inimigo[i].x, e.inimigo[i].y, VIDADROP);
		if (e.inimigo[i].item==4) print_image(e.inimigo[i].x, e.inimigo[i].y, MANADROP);
		if (e.inimigo[i].item==5) print_image(e.inimigo[i].x, e.inimigo[i].y, SWORD);
		if (e.inimigo[i].item==6) print_image(e.inimigo[i].x, e.inimigo[i].y, CRIT);
		if (e.inimigo[i].item==7) print_image(e.inimigo[i].x, e.inimigo[i].y, SWORD_PU);
		if (e.inimigo[i].item==8) print_image(e.inimigo[i].x, e.inimigo[i].y, SHIELD_PU);

	}
} 

void print_item(ESTADO e){
	int i;

	for(i=0; i<e.num_inimigos; i++)
		print_specific_item(i, e);
}

void print_treasure(ESTADO e){
	if (e.treasure.visivel==1) print_image(e.treasure.x, e.treasure.y, TREASURE);
}

void print_treasure_item(ESTADO e){
	if(e.item.visivel==1){
		if (e.item.tipo==0) print_image(e.item.x, e.item.y, SCORE_5);
		if (e.item.tipo==1) print_image(e.item.x, e.item.y, SCORE_10);
		if (e.item.tipo==2) print_image(e.item.x, e.item.y, SCORE_25);
		if (e.item.tipo==3) print_image(e.item.x, e.item.y, VIDADROP);
		if (e.item.tipo==4) print_image(e.item.x, e.item.y, MANADROP);
		if (e.item.tipo==5) print_image(e.item.x, e.item.y, SWORD);
		if (e.item.tipo==6) print_image(e.item.x, e.item.y, CRIT);
		if (e.item.tipo==7) print_image(e.item.x, e.item.y, SWORD_PU);
		if (e.item.tipo==8) print_image(e.item.x, e.item.y, SHIELD_PU);
	}
}
void print_menu(){
	printf("<image x=0 y=0 width=980 height=600 xlink:href=\"http://127.0.0.1/menu.png\"/>\n");
}


void print_stats(ESTADO e){
	int i;

	for (i=0;i<e.jog.vida;i++) 
		printf("<image x=%d y=36 width=20 height=20 xlink:href=\"%s\"/>\n", 600+81+80+20*i, VIDA); // Vida

	for (i=0;i<e.jog.mana;i++) 
		printf("<image x=%d y=80 width=20 height=20 xlink:href=\"%s\"/>\n", 600+81+80+20*i, MANA); // Mana

	printf("<text x=880 y=210 font-family=Verdana font-size=24 fill=white> %d </text> \n", e.nivel); // Nivel
	if(e.jog.powerUp_sword==1) printf("<text x=760 y=210 font-family=Verdana font-size=24 fill=green> %d </text> \n", e.jog.atk*2); // Ataque
	else printf("<text x=760 y=210 font-family=Verdana font-size=24 fill=white> %d </text> \n", e.jog.atk);
	printf("<text x=760 y=245 font-family=Verdana font-size=24 fill=white> %d%c</text> \n", e.jog.crit*10, '%'); // Crit
	printf("<text x=880 y=245 font-family=Verdana font-size=24 fill=white> %d </text> \n", e.score); // Score
}

 
void print_rangeMov(ESTADO e, int px, int py){
	if(casaLivre(e, px, py)==1) print_image(px, py, RANGEMOV);
} 


void print_rangeAttack (ESTADO e, int px, int py){
	if(isEnemy(e, px, py)!=(-1)) print_image(px, py, RANGEATTACK);
}


void print_inventory(ESTADO e){
	int i=0;
	ESTADO newE=e;

	if(e.jog.item_vida>0){
		newE.jog.item_vida--;
		if(newE.jog.vida<8) newE.jog.vida+=2;
		else newE.jog.vida=10;
		printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s\">\n", estado2str(newE));
			printf("<image x=%d y=312 width=39 height=39 xlink:href=\"%s\"/>\n", 708+43*i, VIDA_INV);
		printf("</a>\n");	
		printf("<text x=%d y=350 font-family=Verdana font-size=9 fill=white> %d </text> \n", 600+29+80+40*i, e.jog.item_vida);
		i++;
	}
	newE=e;
	if(e.jog.item_mana>0){
		newE.jog.item_mana--;
		if(newE.jog.mana<8) newE.jog.mana+=2;
		else newE.jog.mana=10;
		printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s\">\n", estado2str(newE));
			printf("<image x=%d y=312 width=39 height=39 xlink:href=\"%s\"/>\n", 708+43*i, MANA_INV);
		printf("</a>\n");	
		printf("<text x=%d y=350 font-family=Verdana font-size=9 fill=white> %d </text> \n", 600+29+80+2*i+40*i, e.jog.item_mana);
		i++;
	}
	newE=e;
	if(e.jog.item_sword>0){
		newE.jog.item_sword--;
		newE.jog.powerUp_sword=1;

		printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s\">\n", estado2str(newE));
			printf("<image x=%d y=312 width=39 height=39 xlink:href=\"%s\"/>\n", 708+43*i, SWORD_PU_INV); // mudar IMAGEM
		printf("</a>\n");	
		printf("<text x=%d y=350 font-family=Verdana font-size=9 fill=white> %d </text> \n", 600+29+80+2*i+40*i, e.jog.item_sword);
		i++;
	}
	newE=e;
	if(e.jog.item_shield>0){
		newE.jog.item_shield--;
		newE.jog.powerUp_shield=1;

		printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s\">\n", estado2str(newE));
			printf("<image x=%d y=312 width=39 height=39 xlink:href=\"%s\"/>\n", 708+43*i, SHIELD_PU_INV);
		printf("</a>\n");	
		printf("<text x=%d y=350 font-family=Verdana font-size=9 fill=white> %d </text> \n", 600+29+80+2*i+40*i, e.jog.item_shield);
		i++;
	}
}


void print_board(){ 
	int x, y;
	for (x=0;x<11;x++)
		for (y=0;y<8;y++) 
			if(x%2==0) printf("<image x=%d y=%d width=%d height=%d xlink:href=\"%s\"/>\n", x*60, y*70 + 35,80,70,HEX_FLOOR); 
			else printf("<image x=%d y=%d width=%d height=%d xlink:href=\"%s\"/>\n", x*60, y*70,80,70,HEX_FLOOR);
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

	strcpy(path, "/var/www/html/estado/");
	strcat(path, nomef);

	fp=fopen(path, "r");
	if (fp==NULL) printf ("Erro");
	else{ 
		fscanf(fp, "%s\n", st);
		fclose(fp);
	}
	e=str2estado(st);

	return e;
}

ESTADO processar_acao(ESTADO e, int acao, char *nomef){

	if (acao==0 || acao==10) e=inicializar(1,0,0,0,10,10,1,0,1,1,1,1);
	else{
		e=ler_estado(nomef);
		int x=e.jog.x; int y=e.jog.y;
		if (acao==1){
			e = inicializar(++e.nivel, e.door.x, e.door.y, e.score+10, e.jog.vida, e.jog.mana, e.jog.atk, e.jog.crit, e.jog.item_vida, e.jog.item_mana, e.jog.item_sword, e.jog.item_shield);
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
	}
	return e;
}

ESTADO processar_mov(ESTADO e, int px, int py){
	int i;

	if (casaLivre(e, px, py)==1){
		e.jog.x=px;
		e.jog.y=py;
	}
	else if(isItem(e, px, py)!=(-1)){
		i=isItem(e, px, py);
		e=catchItem(e.inimigo[i].item, e);
		e.inimigo[i].visivel=0;
	}
	else if(isEnemy(e, px, py)!=(-1)){ 
		i=isEnemy(e, px, py);
		e.inimigo[i].vida=atk_Player(e.inimigo[i].vida, e.jog.crit, e.jog.atk, e.jog.powerUp_sword);
		if(e.inimigo[i].vida==0){
			e.score+=5;
			e.inimigo[i].visivel=1;
		}
	}
	else if(px==e.treasure.x && py==e.treasure.y && e.treasure.visivel==1){
		e=itemTesouro(e, px, py);
		e.treasure.visivel=0;
		e.item.visivel=1;
	}
	else if(px==e.item.x && py==e.item.y && e.item.visivel==1){
		e.item.visivel=0;
		e=catchItem(e.item.tipo, e);
	}


	//e=enemyMove(e);

	return e;
}


void parser(){
	ESTADO e={0};
    int num,acao;
    char nomef[100];
    char *args = getenv("QUERY_STRING");

    if(strlen(args) == 0){ //aqui detecta-se que não foi passado nenhum parametro, neste caso precisas de escolher um nome para o ficheiro e que acao queres fazer
                        acao=0;
            strcpy(nomef,"Default");

    }
    else { //aqui vou fazer um scan dos parametros ficando em num a quantidade de parametros lidos
            num =sscanf(args,"%[^,],%d", nomef, &acao);
            if (num==1)acao = 10;  //se só for 1 quer dizer que só coloquei o nome do jogador(ficheiro) pelo que escolho uma acao para mostrar esse estado
          }                                     // se for maior que 1 então estou a receber nos parametros o nome do ficheiro e a acao pelo que devo

                                                //avançar para o processamento da acao especificada no link
		
	e=processar_acao(e, acao, nomef); //equivalente a print_move

	print_menu(); 
	print_board();
	print_item(e);
	print_enemy(e); 
	print_treasure(e);
	print_treasure_item(e);
	print_door(e);
	print_wall(e);
	if(e.jog.vida != 0) print_player(e, acao, nomef);
	print_inventory(e);
	print_stats(e);
	opcaoRange(e);
	print_rangeEnemy(e);
	selectRange(e);
	opcaoVida(e);
	print_enemy_vida(e);

	guardar_estado(e, nomef);

}





















/* void parser(){
	ESTADO e;
	char *args=getenv("QUERY_STRING");

	if(strlen(args) == 0) 
		e = inicializar(1,0,0,0,10,10,1,0,1,1,1,1);
	else 
		e = str2estado(args);
	if(e.acao==1)
		e = inicializar(++e.nivel, e.door.x, e.door.y, e.score+10, e.jog.vida, e.jog.mana, e.jog.atk, e.jog.crit, e.jog.item_vida, e.jog.item_mana, e.jog.item_sword, e.jog.item_shield);
	print_menu();
	print_board();
	print_item(e);
	print_enemy(e); 
	print_treasure(e);
	print_treasure_item(e);
	print_door(e);
	if(e.jog.vida != 0) print_player(e);
	print_wall(e);
	print_inventory(e);
	print_stats(e);
	opcaoRange(e);
	print_rangeEnemy(e);
	selectRange(e);
	opcaoVida(e);
	print_enemy_vida(e);
} */