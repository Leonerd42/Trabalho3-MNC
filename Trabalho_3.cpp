/***************************************************
	Trabalho 3 - Métodos Numéricos Computacionais
	Leonardo Silva de Oliveira <171025903>
	
***************************************************/

#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>

#define maxpontos 15
#define maxgrau 10

/***************************************************
			Resolução de Sistema Linear
***************************************************/

/***************************************************
					Newton
***************************************************/

int Newton (int num, double tabela[2][maxpontos], double ponto){
	
}

/***************************************************
				Newton Gregory 
***************************************************/

int NewtonGregory (int num, double tabela[2][maxpontos], double ponto){
	
}

/***************************************************
			Coeficiente de Determinação 
***************************************************/

int CoefDeterminacao (int num, double tabela[2][maxpontos], double Y[maxpontos]){
	
}

/***************************************************
				Ajuste de Reta
***************************************************/

int AjusteReta (int num, double tabela[2][maxpontos], double a0, double *a1, double Y[maxpontos], double *cd){
	
}

/***************************************************
				Ajuste Polinomio 
***************************************************/

int AjustePolinomio (int num, int grau, double tabela[2][maxpontos], double A[maxgrau], double Y[maxpontos], double *cd){
	
}

/***************************************************
				Ajuste Exponencial 
***************************************************/

int AjusteExponencial (int num, double tabela[2][maxpontos], double *c1, double *c2, double Y[maxpontos], double *cf){
	
}

/***************************************************
				Menu e Interface 
***************************************************/

int menu (){
	
	int x; 
	
	system("cls"); 
	printf("\n\tMENU\n"); 
	
	printf("\n\t 1 - Newton"); 
	printf("\n\t 2 - Newton Gregory"); 
	printf("\n\t 3 - Ajuste de Reta"); 
	printf("\n\t 4 - Ajuste Polinomio"); 
	printf("\n\t 5 - Ajuste Exponencial");
	printf("\n\t 6 - Fechar Programa"); 
	printf("\n\n\tOpção: "); 
	do{
		scanf("%d",&x); 
	}while(x < 1 || x > 6); 
	
	return x; 
}

int main(){

	setlocale(LC_ALL,"Portuguese");
	int op; 
	
	do{
		op = menu(); 
		switch(op){
			case 1: 	
			
				break;
			case 2: 
				break; 
			case 3: 
				break; 
			case 4: 
				break; 
			case 5: 
				break; 
		}
		
	}while(op != 6); 

}

