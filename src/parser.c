#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "estado.h"
#include "parser.h"

/** Funcao que avalia se uma posicao esta ocupada ou nao*/
int posvalida(ESTADO e,int x,int y){
	int r=1;
	int i=0;
	if(x<0 || y<0 || x>=SIZE || y>=SIZE) r=0;

	/*verificar posicao do jogador*/
	if( x==e.jog.x && y==e.jog.y)r=0;
	/*verificar posicao do objetivo*/
	if( x==e.goal.x && y==e.goal.y) r=0;
	/*verificar posicao dos inimigos*/
	for (i=0;i<e.num_inimigos;i++){
		if(e.inimigo[i].x==x && e.inimigo[i].y==y){
			r=0;
			break;
		}
	}
	/*verificar posicao dos obstaculos*/
	for (i=0;i<e.num_obstaculos;i++){
		if(e.obstaculo[i].x==x && e.obstaculo[i].y==y){
			r=0;
			break;
		}
	}
	return r;

}

/** Funcao que inicializa o jogo*/
ESTADO inicializar(int nivel) {
	ESTADO e={{0}};
	int i=0;
	int ni=10;
	int no=20;
	int x,y;
	srand(time(NULL));
	e.acao = 0;
	e.nivel=nivel;
	e.jog.x = 5;
	e.jog.y = 9;
	e.goal.x = 5;
	e.goal.y = 0;
	e.num_inimigos = 0;
	while(i<ni+nivel){
		x=rand()%(SIZE-1);
		y=rand()%(SIZE-1);
		if(posvalida(e,x,y)==1){
			e.inimigo[i].x = x;
			e.inimigo[i].y = y;
			i++;
			e.num_inimigos++;
		}

	}
	e.num_obstaculos = 0;
	i=0;
	while(i<no){
		x=rand()%(SIZE-1);
		y=rand()%(SIZE-1);
		if(posvalida(e,x,y)==1){
			e.obstaculo[i].x = x;
			e.obstaculo[i].y = y;
			i++;
			e.num_obstaculos++;
		}

	}
	return e;
}

int estainimigo(ESTADO e,int x, int y)
{
	int i, r=0;
	for (i=0;i<e.num_inimigos;i++){
		if(e.inimigo[i].x==x && e.inimigo[i].y==y){
			r=1;
			break;

		}
	}
	return r;

}


/** Funcao que imprime um unico quadrado do tabuleiro*/
void print_square(int x, int y, int tam ){
	char *cor[]={"#555500","#999900"};
	int idx = (x+y)%2;
	printf("<rect x=%d y=%d height=%d width=%d style=\"fill:%s\"\n/>",tam*x,tam*y,tam,tam,cor[idx]);
}


/** Funcao que imprime o tabuleiro*/
void print_board(){
	int x,y;
	for(y=0;y<SIZE;y++)
		for(x=0; x<SIZE;x++)
			print_square(x,y,TAM);
}


/** Funcao que imprime uma imagem*/
void print_image(int px, int py, int tamanho, char *figura){
	printf("<image x=%d y=%d height=%d width=%d xlink:href=\"%s\"\n/>",px*tamanho,py*tamanho,tamanho,tamanho,figura);
}

/** Funcao que imprime o objetivo*/
void print_goal(ESTADO e){
	print_image(e.goal.x, e.goal.y,TAM,GOAL);
}

void print_enemies(ESTADO e);
void darTiro(ESTADO e, int x,int y)
{      int i;
        for(i=0; i<e.num_inimigos;i++)
        {if( e.inimigo[i].x==x && e.inimigo[i].y==y) {
        	/* ver o que acontece a posiçao do inimigo*/
        	e.inimigo[i].x=-1;
        	e.inimigo[i].y=-1;

            }


      }
  }

/** Funcao que nos permite movimentar o jogador no tabuleiro */
void print_move(ESTADO e, int dx,int dy){
	int x =e.jog.x +dx;
	int y = e.jog.y +dy;
	/*estado para qual o jogo transita ao clicar no link*/
	ESTADO ne=e;
	if(e.goal.x==x && e.goal.y==y){
		ne.acao=1;
		printf("<a xlink:href=http://127.0.0.1/cgi-bin/jogo?%s>\n",estado2str(ne));
		print_goal(e);
		printf("</a >\n");
	}else{
		if(posvalida(e,x,y)==0){
			ne.jog.x=x;
			ne.jog.y=y;
			printf("<a xlink:href=http://127.0.0.1/cgi-bin/jogo?%s>\n",estado2str(ne));
			print_enemies(e);



			printf("</a >\n");

		}else{
			ne.jog.x=x;
			ne.jog.y=y;
			printf("<a xlink:href=http://127.0.0.1/cgi-bin/jogo?%s>\n",estado2str(ne));
			print_square(x,y,TAM);
			printf("</a >\n");
		}



		}


		}





void print_move_enemie(ESTADO e, int dx,int dy){
	int i=0;
		ESTADO ne = e;
		while(i<e.num_inimigos){
			int x= e.inimigo[i].x+dx;
			int y= e.inimigo[i].y+dy;

			if(posvalida(e,x,y)!=0){
				ne.inimigo[i].x=x;
				ne.inimigo[i].y=y;
			}

			i++;
		}

}



/** Funcao que imprime o jogador*/
void print_player(ESTADO e){
	print_image(e.jog.x, e.jog.y, TAM,PLAYER);
	print_move(e,+1,0);
	print_move(e,-1,0);
	print_move(e,0,+1);
	print_move(e,0,-1);
	print_move(e,+1,+1);
	print_move(e,-1,-1);
	print_move(e,+1,-1);
	print_move(e,-1,+1);
}

/** Funcao que imprime os inimigos*/
void print_enemies(ESTADO e) {
	int i;
	for(i = 0; i < e.num_inimigos; i++){
		print_move_enemie(e,+1,0);
		print_image(e.inimigo[i].x, e.inimigo[i].y, TAM,ENEMY);
	}
}

/** Funcao que imprime os obstaculos*/
void print_walls(ESTADO e) {
	int i;
	for(i = 0; i < e.num_obstaculos; i++)
	print_image(e.obstaculo[i].x, e.obstaculo[i].y, TAM,WALL);
}



void parse(){
	ESTADO e;
	char *args=getenv("QUERY_STRING");
	if(strlen(args) == 0) e = inicializar(0);
	else e = str2estado(args);
	if(e.acao==1){
		e = inicializar(++e.nivel);
	}
	print_board();
	print_enemies(e);
	print_walls(e);
	print_goal(e);
	print_player(e);
}
