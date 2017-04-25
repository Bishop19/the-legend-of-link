#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "estado.h"
#include <time.h>



ESTADO inicializar(int nivel, int px, int py, int score, int vida, int mana, int atk, int crit){
	int i, x, y, z, l; 
	ESTADO e = {0};
	srand(time(NULL));

	e.nivel = nivel; 
	e.acao = 0; 
	e.jog.x = px;
	e.jog.y = py; 
	e.jog.vida=vida;
	e.jog.mana=mana;
	e.jog.atk=atk;
	e.jog.crit=crit;
	e.score = score;
	e.range=0;
	
	x=px;
	y=py;
	while (abs(x-px)+abs(y-py)<12){ // gerar porta a 12 casas do jogador no minimo
		x=rand()%SIZE;
		y=rand()%SIZE;
		e.door.x = x; 
		e.door.y = y;  
	}

	i=0;
	z=rand()%SIZE;
	if (z<8){
		while(i==0){ // gerar tesouro com 80% de possibilidade
			x=rand()%SIZE;
			y=rand()%SIZE;
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
	while(i<NUM_INIMIGOS+(e.nivel/2)){ // gerar inimigos conforme o nivel
		x=rand()%SIZE; 
		y=rand()%SIZE;
		z=rand();
    		if(casaLivre(e,x,y)==1){
    			e.inimigo[i].x=x;
    			e.inimigo[i].y=y;
    			e.inimigo[i].vida=2;
    			e.inimigo[i].tipo=tipoInimigo(e.nivel,rand());
    			e.inimigo[i].item=itemInimigo(z);
    			e.inimigo[i].visivel=0;
    			i++;
    			e.num_inimigos++;
    		}	
   	}

   	e.num_obstaculos = 0;
  	i=0;
    while(i<NUM_OBSTACULOS+e.nivel){ // gerar objetos conforme o nivel
		x=rand()%SIZE; 
		y=rand()%SIZE; 
    		if(casaLivre(e,x,y)==1){
    			e.obstaculo[i].x=x;
    			e.obstaculo[i].y=y;
    			i++;
    			e.num_obstaculos++;
    		}	 
    }

    i=0;
    l=rand()%SIZE;
	if (l<6){
		while(i==0){ // gerar lama com 60% de possibilidade
			x=rand()%SIZE;
			y=rand()%SIZE;
			if(casaLivre(e,x,y)==1){
				e.lama.x = x;
				e.lama.y = y;
				i++;
			}
		}
	}

	return e;
}


void print_move(ESTADO e, int difx, int dify){
	ESTADO newE = e;
	int px = e.jog.x + difx;
	int py = e.jog.y + dify;

	if (px==e.door.x && py==e.door.y){
		newE.acao=1;
		printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s\">\n", estado2str(newE));
			print_door(e);
			print_rangeMov(px, py, TAM); 
		printf("</a>\n");
	}
	else if (casaLivre(e, px, py)==1){ 
		newE.jog.x = px; 
		newE.jog.y = py;
		newE=enemyMove(newE); //jogada dos inimigos
		printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s\">\n", estado2str(newE));
			print_rangeMov(px, py, TAM);
		printf("</a>\n");
	}
	else if (isItem(e,px, py)!=(-1)){
		int i = isItem(e,px, py); // int i - indica o inimigo que tem o item em causa
		newE=catchItem(e.inimigo[i].item, e); // apanha o respetivo item
		newE.inimigo[i].visivel=0; // e torna-o invisivel
		newE=enemyMove(newE); //jogada dos inimigos
		printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s\">\n", estado2str(newE));
			print_specific_item(i, e);
		printf("</a>\n");
	}
	else if (isEnemy(e, px, py)!=(-1)){
		int i = isEnemy(e, px, py);
		newE.inimigo[i].vida=atk_Player(newE.inimigo[i].vida, newE.jog.crit, newE.jog.atk);
		if (newE.inimigo[i].vida==0) {
			newE.inimigo[i].visivel=1;
			newE.score+=5;
		}
		newE=enemyMove(newE); // jogada dos inimigos
		print_rangeAttack(px, py, TAM); //indica ao jogador que pode atacar o inimigo
		printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s\">\n", estado2str(newE));
			print_enemy_specific(px, py, e.inimigo[i].tipo); //cria hiperligacao para atacar o inimigo em especifico
		printf("</a>\n");
	}	
	else if (px==e.treasure.x && py==e.treasure.y && newE.treasure.visivel==1){
		newE=itemTesouro(e, px, py);
		newE.treasure.visivel=0;
		newE.item.visivel=1; 
		newE=enemyMove(newE); //jogada dos inimigos
		printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s\">\n", estado2str(newE));
			print_treasure(e);
		printf("</a>\n");
	}
	else if (px==e.item.x && py==e.item.y && e.item.visivel==1){
		newE.item.visivel=0;
		newE=catchItem(e.item.tipo, newE);
		newE=enemyMove(newE);
		printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s\">\n", estado2str(newE));
			print_treasure_item(e);
		printf("</a>\n");
	}
	else if (px==e.lama.x && py==e.lama.y){
		newE=enemyMove(enemyMove(newE));
		printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/Rogue?%s\">\n", estado2str(newE));
			print_lama(e);
		printf("</a>\n");
	}
}


ESTADO enemyMove(ESTADO newE){
	int i, x, y, z=0;

	for(i=0; i<newE.num_inimigos; i++){
		if(newE.inimigo[i].vida>0){
			if (inRange(newE,i)==1){
				z++;
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
	newE.jog.vida -= z;
	return newE;
}


int inRange(ESTADO e, int i){
	int r=0;
	if (e.jog.x == e.inimigo[i].x && e.inimigo[i].vida!=0 && (abs(e.jog.y-e.inimigo[i].y) == 1)) r=1;
	if (e.jog.y == e.inimigo[i].y && e.inimigo[i].vida!=0 && (abs(e.jog.x-e.inimigo[i].x) == 1)) r=1;
	return r;
}


int casaLivre (ESTADO e, int x, int y){
	int i=0, r=1;

	if(x<0 || y<0 || x>=SIZE || y>=SIZE) r=0; // verificar se está fora do tabuleiro
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

	for (i=0; i<e.num_inimigos; i++)
		if (x==e.inimigo[i].x && y==e.inimigo[i].y && e.inimigo[i].vida!=0) r=i;
	return r;
}

int isItem (ESTADO e, int px, int py){ // funcao que retorna -1 se a casa nao tem item, ou entao o inimigo que tem o item
	int i,r=(-1);

	for(i=0;i<e.num_inimigos && r==(-1) ;i++)
		if(e.inimigo[i].x==px &&  e.inimigo[i].y == py && e.inimigo[i].visivel==1) r=i;
	return r;
}

ESTADO itemTesouro (ESTADO e, int x, int y){
	srand(time(NULL));
	int z=rand()%20;

	e.item.x=x;
	e.item.y=y;

	if (z<=3) e.item.tipo=0;	
	else if (z>=4 && z<=6) e.item.tipo=1;
	else if (z==7 && z==8) e.item.tipo=2;
	else if (z>=9 && z<=11) e.item.tipo=3;
	else if (z>=12 && z<=14) e.item.tipo=4;
	else if (z>=15 && z<=17) e.item.tipo=5;
	else if (z==18 && z==19) e.item.tipo=6;

	return e;
}

ESTADO catchItem(int item, ESTADO e){
	if (item==0) e.score+=5;
	else if (item==1) e.score+=10;
	else if (item==2) e.score+=25;
	else if (item==3 && e.jog.vida<=8) e.jog.vida+=2;
	else if (item==3 && e.jog.vida>8) e.jog.vida=10;
	else if (item==4 && e.jog.mana<=8) e.jog.mana+=2;
	else if (item==4 && e.jog.mana>8) e.jog.mana=10;
	else if (item==5) e.jog.atk+=1;
	else if (item==6) e.jog.crit+=1;

	return e;
}


int tipoInimigo(int nivel, int x){
	if (nivel==1) x=1;
	else if (nivel==2){
		if (x%2==0) x=1;
		else x=2;
	}
	return x;
}

int itemInimigo(int rand){
	int item=rand%20;
	
	if (item<=3) item=0;	
	else if (item>=4 && item<=6) item=1;
	else if (item==7 || item==8) item=2;
	else if (item>=9 && item<=11) item=3;
	else if (item>=12 && item<=14) item=4;
	else if (item>=15 && item<=17) item=5;
	else if (item==18 || item==19) item=6;		
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
	int i;

	for(i=0;i<e.num_inimigos;i++){
		if(e.inimigo[i].showVida == 1){
			print_image(e.inimigo[i].x, e.inimigo[i].y, TAM, DOOR);
			printf("<text x=%d y=%d font-family=Verdana font-size=12 fill=white> %d </text> \n", e.inimigo[i].x*TAM, e.inimigo[i].y*TAM, e.inimigo[i].vida); // Vida inimigo
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
					print_enemy_specific(e.inimigo[i].x, e.inimigo[i].y, e.inimigo[i].tipo);
				printf("</a>\n");
			}	
			i++;	
		}
	else print_enemy(e);	
}


int atk_Player(int vida, int crit, int atk){
	srand(time(NULL));
	int x=rand()%10, r;

	if(x<crit) r=vida-2*atk;
	else r=vida-atk;
	if (r<0) r=0;

	return r;
}

void print_image(int px, int py, int tam, char *imagem){
	printf("<image x=%d y=%d width=%d height=%d xlink:href=\"%s\"/>\n", px*tam, py*tam, tam, tam, imagem); 
}


void print_player(ESTADO e){
	print_image(e.jog.x, e.jog.y, TAM, PLAYER);
	print_move(e, +1, +0);
	print_move(e, +0, +1);
	print_move(e, +0, -1);
	print_move(e, -1, +0);
}


void print_lama(ESTADO e){
	print_image(e.lama.x, e.lama.y, TAM, LAMA);
}


void print_enemy(ESTADO e){
	int i;

	for(i = 0; i < e.num_inimigos; i++){
		if(e.inimigo[i].vida !=0 && e.inimigo[i].tipo==1) print_image(e.inimigo[i].x, e.inimigo[i].y, TAM, ENEMY);
		if(e.inimigo[i].vida !=0 && e.inimigo[i].tipo==2) print_image(e.inimigo[i].x, e.inimigo[i].y, TAM, ENEMY2);
	}
}

void print_enemy_specific(int x, int y, int tipo){
	if (tipo==1) print_image(x, y, TAM, ENEMY);
	else print_image(x, y, TAM, ENEMY2);
}

void print_rangeEnemy(ESTADO e){
	int i, x, y;

	for(i=0;i<e.num_inimigos;i++)
		if(e.inimigo[i].range == 1){
			x = e.inimigo[i].x;
			y = e.inimigo[i].y;
			if(casaLivre(e,x+1,y)==1) print_rangeAttack(x+1, y,TAM);
			if(casaLivre(e,x-1,y)==1) print_rangeAttack(x-1, y,TAM);
			if(casaLivre(e,x,y+1)==1) print_rangeAttack(x, y+1,TAM);
			if(casaLivre(e,x,y-1)==1) print_rangeAttack(x, y-1,TAM);
	}
}


void print_wall(ESTADO e){
	int i;

	for(i = 0; i < e.num_obstaculos; i++)
		print_image(e.obstaculo[i].x, e.obstaculo[i].y, TAM, WALL);
}


void print_door(ESTADO e){ 
	print_image(e.door.x, e.door.y, TAM, DOOR);
}

void print_specific_item(int i, ESTADO e){ 
	if (e.inimigo[i].visivel==1){
		if (e.inimigo[i].item==0) print_image(e.inimigo[i].x, e.inimigo[i].y, TAM, SCORE_5);
		if (e.inimigo[i].item==1) print_image(e.inimigo[i].x, e.inimigo[i].y, TAM, SCORE_10);
		if (e.inimigo[i].item==2) print_image(e.inimigo[i].x, e.inimigo[i].y, TAM, SCORE_25);
		if (e.inimigo[i].item==3) print_image(e.inimigo[i].x, e.inimigo[i].y, TAM, VIDADROP);
		if (e.inimigo[i].item==4) print_image(e.inimigo[i].x, e.inimigo[i].y, TAM, MANADROP);
		if (e.inimigo[i].item==5) print_image(e.inimigo[i].x, e.inimigo[i].y, TAM, SWORD);
		if (e.inimigo[i].item==6) print_image(e.inimigo[i].x, e.inimigo[i].y, TAM, CRIT);
	}
} 

void print_item(ESTADO e){
	int i;

	for(i=0;i<e.num_inimigos;i++)
		print_specific_item(i, e);
}

void print_treasure(ESTADO e){
	if (e.treasure.visivel==1) print_image(e.treasure.x, e.treasure.y, TAM, TREASURE);
}

void print_treasure_item(ESTADO e){
	if(e.item.visivel==1){
		if (e.item.tipo==0) print_image(e.item.x, e.item.y, TAM, SCORE_5);
		if (e.item.tipo==1) print_image(e.item.x, e.item.y, TAM, SCORE_10);
		if (e.item.tipo==2) print_image(e.item.x, e.item.y, TAM, SCORE_25);
		if (e.item.tipo==3) print_image(e.item.x, e.item.y, TAM, VIDADROP);
		if (e.item.tipo==4) print_image(e.item.x, e.item.y, TAM, MANADROP);
		if (e.item.tipo==5) print_image(e.item.x, e.item.y, TAM, SWORD);
		if (e.item.tipo==6) print_image(e.item.x, e.item.y, TAM, CRIT);
	}
}
void print_menu(){
	printf("<image x=600 y=0 width=300 height=600 xlink:href=\"http://127.0.0.1/menu.png\"/>\n");
}


void print_square(int px, int py, int tam){
	print_image(px, py, tam, FLOOR);
} 


void print_stats(ESTADO e){
	int i;

	for (i=0;i<e.jog.vida;i++) 
		printf("<image x=%d y=36 width=20 height=20 xlink:href=\"%s\"/>\n", 600+81+20*i, VIDA); // Vida

	for (i=0;i<e.jog.vida;i++) 
		printf("<image x=%d y=80 width=20 height=20 xlink:href=\"%s\"/>\n", 600+81+20*i, MANA); // Mana     alterar

	printf("<text x=800 y=210 font-family=Verdana font-size=24 fill=white> %d </text> \n", e.nivel); // Nivel
	printf("<text x=680 y=210 font-family=Verdana font-size=24 fill=white> %d </text> \n", e.jog.atk); // Ataque
	printf("<text x=680 y=245 font-family=Verdana font-size=24 fill=white> %d </text> \n", e.jog.crit*10); // Crit
	printf("<text x=800 y=245 font-family=Verdana font-size=24 fill=white> %d </text> \n", e.score); // Score
}

 
void print_rangeMov(int px, int py, int tam){
	print_image(px, py, tam, RANGEMOV);
} 


void print_rangeAttack (int px, int py, int tam){
	 print_image(px, py, tam, RANGEATTACK);
}

void print_board(){ 
	int x, y;
	for (y=0;y<SIZE;y++)
		for (x=0;x<SIZE;x++) 
			print_square(x,y,TAM); 
}


void parser(){
	ESTADO e;
	char *args=getenv("QUERY_STRING");

	if(strlen(args) == 0) 
		e = inicializar(1,0,0,0,10,10,1,0);
	else 
		e = str2estado(args);
	if(e.acao==1)
		e = inicializar(++e.nivel, e.door.x, e.door.y, e.score+10, e.jog.vida, e.jog.mana, e.jog.atk, e.jog.crit);

	print_board();
	print_item(e);
	//print_enemy(e);
	print_treasure(e);
	print_treasure_item(e);
	print_door(e);
	print_lama(e);
	if(e.jog.vida != 0) print_player(e);
	print_wall(e);
	print_menu();
	print_stats(e);
	opcaoRange(e);
	opcaoVida(e);
	print_enemy_vida(e);
	print_rangeEnemy(e);
	selectRange(e);
}