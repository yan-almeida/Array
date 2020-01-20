#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>

#define B 219
#define b 52 

// prot. functs.
void gotoxy(int x, int y); // coordenadas
void info(); // painel informativo >> description
void infoLC(int x, int y); // painel informativo >> lin/col
void sizeMatriz(); // recebe o tamanho >> matriz
void getMatriz(int x, int y); // monta >> matriz
void randInsert(int x, int y); // insere os valores no array >> valores aleatorios
void randShow(int x, int y, int n[][y]); // mostra os valores >> randInsert
void insert(int x, int y); // insere os valores no array >> stdin
void show(int x, int y, int n[][y]); // mostra os valores >> insert
int maior(int x, int y, int n[][y]); // achar o maior valor e passa valores >> digits(n);
int digits(int n); // retorna a quantidade de digitos
void lines(int n); // linhas >> horizontais
void vLines(int n, int x, int y); // linhas >> verticais com coordenadas
void deb(); // loading

/* 
	20 de janeiro de 2020	
    Departamento de T.I., UniProjeção (Taguatinga, Campus I)
    
    Sistemas de Informação (3º semestre)
    Autor: Yan Almeida Garcia
    
    00) Indentação de saída de uma matriz de design responsivo e mutável.
		- Entrada de dados: sizing off >> linhas e colunas
		- opt 1 - Entrada de dados: preenchendo array (srand)
		- opt 2 - Entrada de dados: preenchendo array (stdin)
		- Exibição de dados >> srand/stdin	
*/

// global vars.
	int i, j;
	char opt;
	
int main(){
	
	sizeMatriz();
	
	return 0;
}

// functions
	// coordenadas
void gotoxy(int x, int y){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
	// painel informativo >> description
void info(){
	system("cls");
	
	gotoxy(8, 3);
	lines(b);
	
	printf("\n\t%c"
		   "\n\t%c  Este %c um algoritmo feito de aluno para aluno!", B, B, 130);
	printf("\n\t%c"
		   "\n\t%c  O programa foi feito para que os alunos tenham", B, B);
	printf("\n\t%c  uma melhor visualiza%c%co de n%cmeros em uma ma-", B, 135, 198, 163);
	printf("\n\t%c  triz de dimens%ces adapt%cveis."
		   "\n\t%c\n\t", B, 228, 160, B);
	
	lines(b);
	vLines(7, 59, 4);
}
	// painel informativo >> lin/col
void infoLC(int x, int y){
	int o = 24, Aa = 68, Bb = 71, Cc = 7;
	info();
	
	gotoxy(Aa, 3);
	lines(o);
	
	gotoxy(Bb, 5);
	printf("DIMENS%cO DA MATRIZ", 199);
	gotoxy(Bb, 7);
	printf("Linha(s):  %.3d", x);
	gotoxy(Bb, 8);
	printf("Coluna(s): %.3d  ", y);	
	
	gotoxy(Aa, 10);
	lines(o);
	vLines(Cc, Aa, 3); // left side
	vLines(Cc, 91, 3); // right side
}
	// recebe o tamanho >> matriz
void sizeMatriz(){
	int size[2], o = 13, LIN = 0, COL = 0;
	
	info();
	
	gotoxy(8, 14);
	lines(o);
	
	for(i = 0; i < 2; i++){
		if(i == 0) printf("\n\t%c\n\t%c  Linhas:  ", B, B);
		else printf("\t%c  Colunas: ", B);
		scanf(" %d", &size[i]);
	}
	printf("\t%c\n\t", B);
	lines(o);
		
	LIN = size[0];
	COL = size[1]; 
	
	Sleep(550);
	getMatriz(LIN, COL); // passagem de valor >> size[' ']
}
	//  valores >> aleatorios/inseridos
void getMatriz(int x, int y){
	int o = 27;
	
	do{
		infoLC(x, y);
	
		gotoxy(8, 14);
		lines(o);
		printf("\n\n\t   1 - VALORES ALEAT%cRIOS", 224);
		printf("\n\t   2 - INSERIR VALORES");
		printf("\n\t   0 - VOLTAR");
		
		gotoxy(8, 20);
		lines(o);
		vLines(5, 8, 15);
		vLines(7, 35, 14);
		
		printf("\n\n\tOp%c%co: ", 135, 198);
		scanf(" %d", &opt);
		fflush(stdin);
		
		Sleep(450);
		
		if(opt == 0) sizeMatriz();
		if(opt == 1) randInsert(x, y); 
		if(opt == 2) insert(x, y);		
	}while(opt < 1 || opt > 2);	
}
	// opt: 1 - insere os valores no array >> valores aleatorios
void randInsert(int x, int y){
	int M[x][y], o = 22;
	
	for(i = 0; i < x; i++){
		puts("");
		for(j = 0; j < y; j++) M[i][j] = 1 + rand() % 9999;
	}
	
	Sleep(550);
	randShow(x, y, M);
}
	// mostra os valores >> randInsert	
void randShow(int x, int y, int n[][y]){
	int res, resM;

	do{
		infoLC(x, y);
		
		resM = maior(x, y, n);
		res = digits(resM);
		
		gotoxy(11, 14);
		for(j = 0; j < y; j++) printf("%-*i ", res + 3, j); // imprime o(s) indice(s) da(s) coluna(s)
		
		for(i = 0; i < x; i++){
			printf("\n\t %d ", i); 
			for(j = 0; j < y; j++) printf("[ %*i ]", res, n[i][j]); 
		}
		
		printf("\n\n\n\t Voltar ao menu [S/N]: ");
		scanf(" %c", &opt);
		
		if(toupper(opt) == 'S') sizeMatriz();
		else if(toupper(opt) == 'N') exit(0);
	}while(toupper(opt) != 'S' || toupper(opt) != 'N');	
}
	// opt: 2 - insere os valores no array >> stdin
void insert(int x, int y){
	int M[x][y], o = 23;
	
	infoLC(x, y);
	
	gotoxy(8, 14);	
	lines(o);
	printf("\n\t%c", B);
	
	for(i = 0; i < x; i++){
		puts("");
		for(j = 0; j < y; j++){
			printf("\t%c  %cndice [ %d ][ %d ]: ", B, 214, i, j);
			scanf(" %d", &M[i][j]);
			fflush(stdin);
		}
	}
	printf("\t%c\n\t", B);
	lines(o);
	
	deb();
	show(x, y, M);
}
	// mostra os valores >> insert
void show(int x, int y, int n[][y]){
	int res, resM;
	
	do{
		infoLC(x, y);
		
		resM = maior(x, y, n);
		res = digits(resM);
		
		gotoxy(11, 14);
		for(j = 0; j < y; j++) printf("%-*i ", res + 3, j); // imprime o(s) indice(s) da(s) coluna(s)
		
		for(i = 0; i < x; i++){
			printf("\n\t %d ", i); 
			for(j = 0; j < y; j++) printf("[ %*i ]", res, n[i][j]); 
		}
		
		printf("\n\n\n\t Voltar ao menu [S/N]: ");
		scanf(" %c", &opt);
		
		if(toupper(opt) == 'S') sizeMatriz();
		else if(toupper(opt) == 'N') exit(0);
	}while(toupper(opt) != 'S' || toupper(opt) != 'N');
}
	// achar o maior valor e passa valores >> digits(n);
int maior(int x, int y, int n[][y]){
	int qtNum = 0, maior;
	
	maior = n[0][0]; 
	for(i = 0; i < x; i++){ 
		for(j = 0; j < y; j++){
			if(maior < n[i][j]) maior = n[i][j];
		}
	}
	
	return maior;
}
	// retorna a quantidade de digitos 
int digits(int n){ 
	int qtNum = 0;
		
	do{
    	qtNum += 1;
        n /= 10;
    }while (n != 0);
	
	return qtNum;
}
	// linhas >> horizontais
void lines(int n){
	for(i = 0; i < n; i++) printf("%c", B);
}
	// linhas >> verticais com coordenadas
void vLines(int n, int x, int y){	
	for(i = 0; i < n; i++){
		gotoxy(x, y + i);
		printf("%c", B);	
	} 
}	
	// loading
void deb(){
	Sleep(420);
	
	printf("\n\n\tCaptando Dados");
	
	for(i = 0; i < 3; i++){
			printf(".");
			Sleep(230);
	}	
	
	Sleep(400);
	printf("\n\tRegistrado!");
	Sleep(625);
}
