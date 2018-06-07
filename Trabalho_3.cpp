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
#include<limits.h>

#define maxpontos 15
#define maxgrau 10
#define max 15
double Determinante (int ordem, double matriz[][max]);
/***************************************************
			Resolução de Sistema Linear
***************************************************/
/*************************************
		Cálculo dos Determinantes
**************************************/
void MenorPrincipal (double matriz[max][max],double Menor[max][max], int linha, int coluna, int ordem){
	int aux_l = 0, aux_c = 0; 
	for (int i=0; i<ordem; i++){
		if(i == linha){
			continue; 
		}
		for (int j=0; j<ordem; j++){
			if(j == coluna)	{
				continue; 
			}
			Menor[aux_l][aux_c++] = matriz[i][j]; 			
		}
		aux_c = 0; 
		aux_l++; 
	}	
}
//-----------------------------------------------------------
void MelhorCaminho (double matriz[max][max],int ordem, int *lin_col, int *n){
	int cont_i, cont_j, melh_i, melh_j, lin[ordem], col[ordem]; 
	cont_i = cont_j = melh_i = melh_j = (*lin_col) = 0;	 
	for (int i=0; i<ordem; i++){
		for(int j=0; j<ordem; j++){
			if(matriz[i][j] == 0) {
				cont_i++; 
			}
		}
		lin[i] = cont_i; 
		cont_i = 0; 
	}
	for(int i=0; i<ordem; i++){
		for(int j=0; j<ordem; j++){
			if(matriz[j][i] == 0){
				cont_j++;
			}
		}
		col[i] = cont_j; 
		cont_j = 0; 
	}
	for(int i=0; i<ordem; i++){
		if(lin[i] != 0){
			if(lin[melh_i] < lin[i]){
				melh_i = i; 
			}
		}
	}
	
	for(int i=0; i<ordem; i++){
		if(col[i] != 0){
			if(col[melh_j] < col[i]){
				melh_j = i; 
			}
		}
	}
	if(lin[melh_i] >= col[melh_j]){
		(*lin_col) = 0; 
		(*n) = melh_i; 
	}
	else{
		(*lin_col) = 1; 
		(*n) = melh_j; 
	}	
}
//-----------------------------------------------------------
double Cofator (int ordem, int i, int j, double matriz[][max]){
	return pow((-1),i+j) * Determinante(ordem-1,matriz);  
}
//-----------------------------------------------------------
double Determinante (int ordem, double matriz[][max]){
	int i, j, lin_col, num, soma=0;
	double maux [max][max]; 
	if(ordem == 2){ 
		return (matriz[0][0] * matriz[1][1] - matriz[0][1]*matriz[1][0]);		
	}
	if(ordem == 1) {
		return matriz[0][0];
	}
	MelhorCaminho(matriz,ordem,&lin_col,&num);
	switch(lin_col){
		case 0: 	
			i = num; 
			for(j=0; j<ordem; j++){
				MenorPrincipal (matriz,maux,i,j,ordem); 
				soma += matriz[i][j] * Cofator (ordem,i,j,maux);
			}
			break; 
		case 1:
			j = num; 
			for(i=0; i<ordem; i++){
				MenorPrincipal (matriz,maux,i,j,ordem); 
				soma += matriz[i][j] * Cofator (ordem,i,j,maux);
			}
			break; 	
		}
	return soma; 
}
/*************************************
		Sistemas Triangulares
**************************************/
void SistemaTriangularSuperior(int ordem, double matriz[][max], double b[], double x[]){ //okay, funciona!!
	double somatorio;  
	for(int i=0; i<ordem; i++){
		somatorio = 0; 
		for (int j=0; j<i; j++){
			somatorio += x[ordem-1-j] * matriz[ordem-1-i][ordem-1-j]; 
		}
		x[ordem-1-i] = (b[ordem-1-i] - somatorio) / matriz[ordem-1-i][ordem-1-i]; 
	}
}
//----------------------------------------------------------
void SistemaTriangularInferior(int ordem, double matriz[][max], double b[], double x[]){
	double somatorio; 
	for(int i=0; i<ordem; i++){
		somatorio = 0; 
		for(int j=0; j<i; j++){
			somatorio += (x[j] * matriz[i][j]); 
		}
		x[i] = (b[i] - somatorio) / matriz[i][i];
	}
}
/*************************************
		Decomposicao LU
**************************************/
void Uij(int linha, int coluna, double matriz[][max], double U[][max], double L[][max]){
	double somatorio=0;
	int k;
	for(k=0;k<=linha-1;k++){
		somatorio += (L[linha][k]*U[k][coluna]);
	}
	U[linha][coluna] = matriz[linha][coluna] - somatorio;
	return;
}
//-----------------------------------------------------------
void Lij(int linha, int coluna, double matriz[][max], double U[][max], double L[][max]){
	double somatorio=0;
	int k;
	for(k=0;k<=coluna-1;k++){
		somatorio += (L[linha][k]*U[k][coluna]);
	}
	L[linha][coluna]=(matriz[linha][coluna] - somatorio)/U[coluna][coluna];
	return;
}
//-----------------------------------------------------------
void ZeraMatriz(double matriz[max][max], int ordem){
	for(int i=0; i<ordem; i++){
		for(int j=0; j<ordem; j++){
			matriz[i][j]=0;
		}
	}
}
//-----------------------------------------------------------
void DecomposicaoLU(int ordem, double matriz[][max], double b[], double x[]){
	int i,j;
	double L[max][max], U[max][max],y[max]; //L = inferior ; U = superior
	ZeraMatriz(L, ordem);
	ZeraMatriz(U, ordem);
	for(i=0;i<ordem;i++){ //testar convergencia det(Ak)!= 0 ,  0 <= k < ordem
		if((Determinante(i+1,matriz)) == 0){
			printf("\nNao converge!");
			return;
		}
	}
	for(i=0;i<ordem;i++){ // variacao de linha
		for(j=0;j<ordem;j++){ //variacao de coluna
			if(i<=j){
				Uij(i,j,matriz,U,L);
				if(i==j){
					L[i][j]=1;
				}
			}
			else{
				Lij(i,j,matriz,U,L);
			}
		}
	}
	//printf("\nMatriz U:");
	//MostraMatriz(U,ordem);
	//printf("\nMatriz L:");
	//MostraMatriz(L,ordem);
	SistemaTriangularInferior(ordem,L,b,y);
	SistemaTriangularSuperior(ordem,U,y,x);
}

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
//------------------
double Newton(int num, double tabela[2][maxpontos], double ponto){
	double x_x0=1, Px=0, mdd[maxpontos][maxpontos]; //mdd = Matriz de Diferencas Divididas
	ZeraMatriz(mdd, num+1);
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
	MostraMatriz(num, num+1, mdd); //Mostra a tabela de diferencas difididas
	
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
	ZeraMatriz(mdf, num+1);
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
	MostraMatriz(num, num+1, mdf); //Mostra a tabela de diferencas difididas
	
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
	double somaY2=0, somaY=0, somaErro2=0;
	for(int i=0; i<num; i++){
		somaErro2+=(pow(tabela[1][i]-Y[i], 2));
		somaY2+=(pow(tabela[1][i], 2));
		somaY+=tabela[1][i];
	}
	//printf("\nerro2 = %lf \ny2 = %lf\ny = %lf", somaErro2, somaY2, somaY);
	//system("pause");
	return 1-((num*somaErro2)/((num*somaY2)-(pow(somaY, 2))));
}

/***************************************************
				Ajuste de Reta
***************************************************/
void AjusteReta (int num, double tabela[2][maxpontos], double *a0, double *a1, double Y[maxpontos], double *cd){
	double somaX=0, somaY=0, somaX2=0, somaXY=0;
	for(int j=0; j<num; j++){
		somaX+=tabela[0][j];
		somaY+=tabela[1][j];
		somaXY+=(tabela[0][j]*tabela[1][j]);
		somaX2+=(pow(tabela[0][j], 2));
	}
	(*a1)=((num*somaXY)-(somaX*somaY))/((num*somaX2)-(pow(somaX, 2)));
	(*a0)=(somaY-((*a1)*somaX))/num;
	for(int i=0; i<num; i++){
		Y[i]=(*a0)+((*a1)*tabela[0][i]);
	}
	(*cd)=CoefDeterminacao(num, tabela, Y);
}

/***************************************************
				Ajuste Polinomio 
***************************************************/
void AjustePolinomio (int num, int grau, double tabela[2][maxpontos], double A[maxgrau], double Y[maxpontos], double *cd){
	double somatorios[maxgrau*2], matriz[max][max], termosIndep[grau+1];
	for(int i=0; i<grau*2; i++){
		for(int j=0; j<num; j++){
			somatorios[i]+=(pow(tabela[0][j], i+1));
		}
		//printf("\n%lf", somatorios[i]);
		//system("pause");
	}
	for(int i=0; i<grau+1; i++){
		for(int j=0; j<num; j++){
			termosIndep[i]+=((pow(tabela[0][j], i))*tabela[1][j]);
		}
		//printf("\n%lf", termosIndep[i]);
		//system("pause");
	}
	for(int i=0; i<grau+1; i++){
		for(int j=0; j<grau+1; j++){
			if(i==0 && j==0){
				matriz[i][j]=num;
				printf("\t%lf", matriz[i][j]);
				continue;
			}
			matriz[i][j]=somatorios[i+j-1];
			printf("\t%lf", matriz[i][j]);
		}
		printf("\n");
	}
	system("pause");
	DecomposicaoLU(grau+1, matriz, termosIndep, A);
	for(int i=0; i<num; i++){
		for(int j=0; j<grau+1; j++){
			Y[i]+=(A[j]*(pow(tabela[0][i], j)));
		}
	}
	(*cd)=CoefDeterminacao(num, tabela, Y);
}

/***************************************************
				Ajuste Exponencial 
***************************************************/
void AjusteExponencial (int num, double tabela[2][maxpontos], double *a, double *b, double Y[maxpontos], double *cd){
	double somaX=0, somalnY=0, somaX2=0, somaXlnY=0, a1, a0;
	for(int j=0; j<num; j++){
		tabela[1][j]=log(tabela[1][j]);
	}
	for(int j=0; j<num; j++){
		somaX+=tabela[0][j];
		somalnY+=tabela[1][j];
		somaXlnY+=(tabela[0][j]*(tabela[1][j]));
		somaX2+=(pow(tabela[0][j], 2));
	}
	
	a1=((num*somaXlnY)-(somaX*somalnY))/((num*somaX2)-(pow(somaX, 2)));
	a0=(somalnY-a1*somaX)/num;
	(*a)=exp(a0);
	(*b)=exp(a1);
	
	for(int i=0; i<num; i++){
		Y[i]=(a0+a1*tabela[0][i]);
	}
	(*cd)=CoefDeterminacao(num, tabela, Y);
}

/***************************************************
				Menu e Interface 
***************************************************/
void MostraVetor(double Y[maxpontos], int num){
	for(int i=0; i<num; i++){
		printf("\t%lf", Y[i]);
	}
}
//--------------------------
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
int ColetaDados(int *pontos, double matriz[2][maxpontos], double *x, int *grau, int opcao){
	double maior=LONG_MIN, menor=LONG_MAX;
	system("cls");
	if(opcao>=1){ // coleta numero de pontos e os pontos tabelados
		printf("\n\tDigite o número de pontos:");
		scanf("%d", &*pontos);
		printf("\n\tValores de X:\n");
		for(int i=0; i<2; i++){
			for(int j=0; j<(*pontos); j++){
				if(i==0){ //valores de x
					printf("\tx%d = ", j);
					scanf("%lf", &matriz[i][j]);
					if(matriz[i][j]>maior){
						maior=matriz[i][j];
					}
					if(matriz[i][j]<menor){
						menor=matriz[i][j];
					}
				}
				else{ //valores de Y
					printf("\ty%d = ", j);
					scanf("%lf", &matriz[i][j]);
				}
			}
			if(i==0){
				if(opcao==2){ //verificacao de pontos igualmente espacados para newton gregory
					for(int i=1; i<(*pontos)-2; i++){
						if((matriz[0][i]-matriz[0][i-1])!=(matriz[0][i+1]-matriz[0][i])){
							return 0;
						}
					}
				}
				printf("\n\tValores de Y:\n");
			}
		}
		if(opcao<=2){// para newton e newton gregory
			printf("\n\tEm qual ponto deseja calcular a funcao?");
			printf("\n\tx = ");
			do{
				scanf("%lf", &*x);
				if((*x)<menor || (*x)>maior){
					printf("\n\tO ponto deve ser maior que %lf e menor que %lf\n\tRedigite: ", menor, maior);
				}
			}while((*x)<menor || (*x)>maior);
		}
		if(opcao==4){ //coleda grau para ajuste polinomial
			printf("\n\tDigite o grau do polinômio: ");
			scanf("%d", &*grau);
		}
	}
}
//--------------------------------------------------

int main(){

	setlocale(LC_ALL,"Portuguese");
	int op, pontos, grau;
	double tabela[2][maxpontos], x, Px, a0, a1, Y[maxpontos], cd, A[maxgrau];
	
	do{
		op = menu(); 
		switch(op){
			case 1: 	//NEWTON
				system("cls"); 
				printf("\n\tMétodo de Newton");
				ColetaDados(&pontos, tabela, &x, &grau, 1);
				Px=Newton(pontos, tabela, x);
				printf("\n\tP(%lf) = %lf\n\n\t",x , Px);
				system("pause");			
				break;
			case 2: 	//NEWTON GREGORY
				system("cls"); 
				printf("\n\tMétodo de Newton Gregory");
				if(!ColetaDados(&pontos, tabela, &x, &grau, 2)){
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
				ColetaDados(&pontos, tabela, &x, &grau, 3);
				AjusteReta(pontos, tabela, &a0, &a1, Y, &cd);
				printf("\n\ta0 = %lf \n\ta1 = %lf", a0, a1);
				printf("\n\tVetor Y ajustado:\n");
				MostraVetor(Y, pontos);
				printf("\n\tCoeficiente de determinacao = %lf\n\t", cd);
				system("pause");
			
				break; 
			case 4: 	//AJUSTE POLINOMIAL
				system("cls"); 
				printf("\n\tAjuste Polinomial");
				ColetaDados(&pontos, tabela, &x, &grau, 4);
				AjustePolinomio(pontos, grau, tabela, A, Y, &cd);
				printf("\n\tVetor A:\n");
				MostraVetor(A, grau+1);
				printf("\n\tVetor Ajustado:\n");
				MostraVetor(Y, pontos);
				printf("\n\tCoeficiente de determinacao = %lf\n\t", cd);
				system("pause");
			
				break; 
			case 5: 	//AJUSTE EXPONENCIAL
				system("cls"); 
				printf("\n\tAjuste Exponencial");
				ColetaDados(&pontos, tabela, &x, &grau, 3);
				AjusteExponencial(pontos, tabela, &a0, &a1, Y, &cd);
				printf("\n\ta = %lf \n\tb = %lf", a0, a1);
				printf("\n\tVetor Y ajustado:\n");
				MostraVetor(Y, pontos);
				printf("\n\tCoeficiente de determinacao = %lf\n\t", cd);
				system("pause");
			
				break; 
		}		
	}while(op != 6); 
	
	printf("\n\tFim do Programa!"); 
}

