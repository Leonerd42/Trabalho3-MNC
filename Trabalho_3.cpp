/***************************************************
	Trabalho 3 - Métodos Numéricos Computacionais
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
			Resolução de Sistema Linear
***************************************************/

		//Decidir qual método de resolução de 
		//sistema que vai usar
		//LU ou cholesky

/***************************************************
					Newton
***************************************************/
void MostraMatriz(int linhas, int colunas, double matriz[maxpontos][maxpontos]){
	for(int i=0; i<linhas; i++){
		for(int j=0; j<colunas; j++){
			printf("%lf\t", matriz[i][j]);
		}
		printf("\n");
	}
}
//-------------------------------------------------
double Newton(int num, double tabela[2][maxpontos], double ponto){
	double x_x0=1, Px=0, mdd[maxpontos][maxpontos]; //mdd = Matriz de Diferencas Divididas
	for(int i=0; i<2; i++){ //transpoe a tabela para a mdd
		for(int j=0; j<num; j++){
			mdd[j][i]=tabela[i][j];
		}
	}
	//diferencas divididas:
	for(int j=2; j<=num; j++){
		for(int i=0; i<num-j+1; i++){
			mdd[i][j]=(mdd[i+1][j-1]-mdd[i][j-1])/(mdd[j+i-1][0]-mdd[i][0]);
			//printf("%lf - %lf / %lf - %lf", mdd[i+1][j-1], mdd[i][j-1], mdd[j+i-1][0], mdd[i][0]);
			//system("pause");
		}
	}
	//MostraMatriz(num, num+1, mdd); //Mostra a tabela de diferencas difididas
	
	//Calculo do valor
	for(int i=0; i<num; i++){
		if(i==0){
			Px=mdd[0][i+1];
			//printf("\nPx = %lf", Px);
			continue;
		}
		x_x0*=(ponto-tabela[0][i-1]);
		//printf("\nx_x0 = %lf", x_x0);
		Px+=(x_x0*mdd[0][i+1]);
		//printf("\nPx = %lf", Px);
	}
	return Px;
}
/***************************************************
				Newton Gregory 
***************************************************/
double NewtonGregory (int num, double tabela[2][maxpontos], double ponto){
	unsigned long int fat=1;
	double h, x_x0=1, Px=0, mdf[maxpontos][maxpontos]; //mdf = Matriz de Diferencas Divididas
	for(int i=0; i<2; i++){ //transpoe a tabela para a mdf
		for(int j=0; j<num; j++){
			mdf[j][i]=tabela[i][j];
		}
	}
	h=mdf[1][0]-mdf[0][0];
	//diferencas finitas:
	for(int j=2; j<=num; j++){
		for(int i=0; i<num-j+1; i++){
			mdf[i][j]=(mdf[i+1][j-1]-mdf[i][j-1]);
			//printf("%lf - %lf", mdf[i+1][j-1], mdf[i][j-1]);
			//system("pause");
		}
	}
	//MostraMatriz(num, num+1, mdf); //Mostra a tabela de diferencas difididas
	
	//Calculo do valor
	for(int i=0; i<num; i++){
		if(i==0){
			Px=mdf[0][i+1];
			//printf("\nPx = %lf", Px);
			continue;
		}
		x_x0*=(ponto-tabela[0][i-1]);
		//printf("\nx_x0 = %lf", x_x0);
		Px+=(x_x0*mdf[0][i+1]/(fat*(pow(h, i))));
		//printf("\nPx = %lf", Px);
		fat*=(fat+1);
	}
	return Px;
}
/***************************************************
			Coeficiente de Determinação 
***************************************************/
double CoefDeterminacao (int num, double tabela[2][maxpontos], double Y[maxpontos]){
	
}

/***************************************************
				Ajuste de Reta
***************************************************/
double AjusteReta (int num, double tabela[2][maxpontos], double a0, double *a1, double Y[maxpontos], double *cd){
	
}

/***************************************************
				Ajuste Polinomio 
***************************************************/
double AjustePolinomio (int num, int grau, double tabela[2][maxpontos], double A[maxgrau], double Y[maxpontos], double *cd){
	
}

/***************************************************
				Ajuste Exponencial 
***************************************************/
double AjusteExponencial (int num, double tabela[2][maxpontos], double *c1, double *c2, double Y[maxpontos], double *cf){
	
}

/***************************************************
				Menu e Interface 
***************************************************/
int menu (){
	
	int x; 
	do{
		system("cls"); 
		printf("\n\tMENU\n"); 
		printf("\n\t 1 - Newton"); 
		printf("\n\t 2 - Newton Gregory"); 
		printf("\n\t 3 - Ajuste de Reta"); 
		printf("\n\t 4 - Ajuste Polinomio"); 
		printf("\n\t 5 - Ajuste Exponencial");
		printf("\n\t 6 - Fechar Programa"); 
		printf("\n\n\tOpção: "); 
		scanf("%d",&x); 
	}while(x < 1 || x > 6); 
	
	return x; 
}
//--------------------------------------------------
int ColetaDados(int *pontos, double matriz[2][maxpontos], double *x, int opcao){
	system("cls");
	if(opcao>=1){ // coleta para newton e newton gregory
		printf("\n\tDigite o número de pontos:");
		scanf("%d", &*pontos);
		printf("\n\tValores de X:\n");
		for(int i=0; i<2; i++){
			for(int j=0; j<(*pontos); j++){
				if(i==0){ //valores de x
					printf("\tx%d = ", j);
					scanf("%lf", &matriz[i][j]);
				}
				else{ //valores de Y
					printf("\ty%d = ", j);
					scanf("%lf", &matriz[i][j]);
				}
			}
			if(i==0){
				if(opcao==2){ //verificacao de pontos igualmente espacados para newton gregory
					for(int i=1; i<(*pontos)-1; i++){
						if((matriz[0][i]-matriz[0][i-1])!=matriz[0][i+1]-matriz[0][i]){
							return 0;
						}
					}
				}
				printf("\n\tValores de Y:\n");
			}
		}
		printf("\n\tEm qual ponto deseja calcular a funcao?");
		printf("\n\tx = ");
		do{
			scanf("%lf", &*x);
			if((*x)<matriz[0][0] || (*x)>matriz[0][(*pontos)-1]){
				printf("\n\tO ponto deve ser maior que %lf e menor que %lf", matriz[0][0], matriz[0][(*pontos)-1]);
			}
		}while((*x)<matriz[0][0] || (*x)>matriz[0][(*pontos)-1]);
	}
}
//--------------------------------------------------

int main(){

	setlocale(LC_ALL,"Portuguese");
	int op, pontos;
	double tabela[2][maxpontos], x, Px;
	
	do{
		op = menu(); 
		switch(op){
			case 1: 	//NEWTON
				system("cls"); 
				printf("\n\tMétodo de Newton");
				ColetaDados(&pontos, tabela, &x, 1);
				Px=Newton(pontos, tabela, x);
				printf("\n\tP(%lf) = %lf\n\n\t",x , Px);
				system("pause");			
				break;
			case 2: 	//NEWTON GREGORY
				system("cls"); 
				printf("\n\tMétodo de Newton Gregory");
				if(!ColetaDados(&pontos, tabela, &x, 2)){
					printf("\n\tOs pontos nao sao igualmente espacados\n\n");
					system("pause");
					break;
				}
				Px=NewtonGregory (pontos, tabela, x);
				printf("\n\tP(%lf) = %lf\n\n\t",x , Px);
				system("pause");
			
				break; 
			case 3: 	//AJUSTE DE RETA
				system("cls"); 
				printf("\n\tAjuste de Reta");
				
				// cálculos
				
				printf("\n\t");
				system("pause");
			
				break; 
			case 4: 	//AJUSTE POLINOMIAL
				system("cls"); 
				printf("\n\tAjuste Polinomial");
				
				// cálculos
				
				printf("\n\t");
				system("pause");
			
				break; 
			case 5: 	//AJUSTE EXPONENCIAL
				system("cls"); 
				printf("\n\tAjuste Exponencial");
				
				// cálculos
				
				printf("\n\t");
				system("pause");
			
				break; 
		}		
	}while(op != 6); 
	
	printf("\n\tFim do Programa!"); 
}

