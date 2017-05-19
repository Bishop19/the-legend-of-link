#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "highScore.h"


void guardar_Score(char *jogador, int new_score){
    FILE *high_score;
    int  i=0, j;
    SCORE record[6];

// Abre o ficheiro com os melhores scores. Caso não exista cria   
    high_score = fopen ("/var/www/html/estado/scores.txt", "r");
    if (high_score == NULL){
        high_score = fopen ("/var/www/html/estado/scores.txt", "w");
        while (i<5){
            fprintf(high_score, "%s\t\t%d\n", "Default", 0);
            i++;
        }        
    }
    fclose (high_score);

// Lê o "nome" e o "score" em cada linha e coloca na struct
    i=0;
    high_score = fopen ("/var/www/html/estado/scores.txt", "r");
    while ((fscanf(high_score, "%s %d", record[i].nome, &(record[i]).score) == 2) && i<5) i++;
    fclose (high_score);

// Coloca ordenamente na struct o novo score
    for(i=0; new_score<record[i].score; i++);
    for(j=4; j>i; j--){
        record[j].score=record[j-1].score;
        strcpy(record[j].nome, record[j-1].nome);
    }
    record[i].score=new_score;
    strcpy(record[i].nome,jogador);
   
// Guarda os novos scores
    i=0;
    high_score = fopen ("/var/www/html/estado/scores.txt", "w");
    while (i<5){
        fprintf(high_score, "%s\t\t%d\n", record[i].nome, record[i].score);
        printf("%s\t\t%d\n", record[i].nome, record[i].score); // apenas para imprimir no terminal para verificar
        i++;
    }
    fclose (high_score);
}

void print_score(){
    FILE *high_score;
    int  i=0;
    SCORE record[6];

    // Abre o ficheiro com os melhores scores. Caso não exista cria   
    high_score = fopen ("/var/www/html/estado/scores.txt", "r");
    if (high_score == NULL){
        high_score = fopen ("/var/www/html/estado/scores.txt", "w");
        while (i<5){
            fprintf(high_score, "%s\t\t%d\n", "Default", 0);
            i++;
        }        
    }
    fclose (high_score);

    // Lê o "nome" e o "score" em cada linha e coloca na struct
    i=0;
    high_score = fopen ("/var/www/html/estado/scores.txt", "r");
    while ((fscanf(high_score, "%s %d", record[i].nome, &(record[i]).score) == 2) && i<5) i++;
    fclose (high_score);

    // Imprime os scores
    for(i=0; i<5; i++){
        if(i==0){
            printf("<text x=200 y=%d font-family=Verdana font-size=38 fill=white stroke=black> %s </text> \n", 400+35*i, record[i].nome);
            printf("<text x=400 y=%d font-family=Verdana font-size=38 fill=white stroke=black> %d </text> \n", 400+35*i, record[i].score);  
        }
        else{
            printf("<text x=200 y=%d font-family=Verdana font-size=28 fill=white stroke=black> %s </text> \n", 400+35*i, record[i].nome);
            printf("<text x=400 y=%d font-family=Verdana font-size=28 fill=white stroke=black> %d </text> \n", 400+35*i, record[i].score);
        }

    }
}