/***************************************************
	Trabalho 3 - M�todos Num�ricos Computacionais
Lucas Henrique Russo do Nascimento  RA: 171025709
Bruna Lika Tamake					RA: 171024427
Leonardo Silva de Oliveira			RA: 171025903
	
***************************************************/

#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>

#define maxpontos 15
#define maxgrau 10

/***************************************************
			Resolu��o de Sistema Linear
***************************************************/

		//Decidir qual m�todo de resolu��o de 
		//sistema que vai usar
		//LU ou cholesky

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
			Coeficiente de Determina��o 
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
	printf("\n\n\tOp��o: "); 
	do{
		scanf("%d",&x); 
	}while(x < 1 || x > 6); 
	
	return x; 
}
//--------------------------------------------------
int ColetaDados(){
	
}
//--------------------------------------------------

int main(){

	setlocale(LC_ALL,"Portuguese");
	int op; 
	
	do{
		op = menu(); 
		switch(op){
			case 1: 	//NEWTON
				system("cls"); 
				printf("\n\tM�todo de Newton");
				
				// c�lculos
				
				printf("\n\t");
				system("pause");			
				break;
			case 2: 	//NEWTON GREGORY
				system("cls"); 
				printf("\n\tM�todo de Newton Gregory");
				
				// c�lculos
				
				printf("\n\t");
				system("pause");
			
				break; 
			case 3: 	//AJUSTE DE RETA
				system("cls"); 
				printf("\n\tAjuste de Reta");
				
				// c�lculos
				
				printf("\n\t");
				system("pause");
			
				break; 
			case 4: 	//AJUSTE POLINOMIAL
				system("cls"); 
				printf("\n\tAjuste Polinomial");
				
				// c�lculos
				
				printf("\n\t");
				system("pause");
			
				break; 
			case 5: 	//AJUSTE EXPONENCIAL
				system("cls"); 
				printf("\n\tAjuste Exponencial");
				
				// c�lculos
				
				printf("\n\t");
				system("pause");
			
				break; 
		}		
	}while(op != 6); 
	
	printf("\n\tFim do Programa!"); 
}

