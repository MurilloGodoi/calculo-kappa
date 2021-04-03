#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <conio.h>
#include <math.h>
#include <locale.h>

float concordancia_observada(int total_perguntas, char observador_1[][2], char observador_2[][2]) {
	int total_concordancias = 0;
	for(int i=0; i<total_perguntas; i++) {
		char resposta_observador_1[2];
		strcpy(resposta_observador_1, observador_1[i]);
		char resposta_observador_2[2];
		strcpy(resposta_observador_2, observador_2[i]);
			
		if(strcmp(resposta_observador_1, resposta_observador_2) == 0) {
			total_concordancias+=1;
		}
	}
	
	float resultado_func_concordancia_observada = total_concordancias / float(total_perguntas);
	return resultado_func_concordancia_observada;
}

float concordancia_esperada(int total_perguntas, char observador_1[][2], char observador_2[][2]) {
	int A = 0, B = 0, C = 0, D = 0, A1 = 0, A2 = 0, B1 = 0, B2 = 0, total = 0;
	float resultado_func_concordancia_esperada = 0;
	
	for(int i=0; i<total_perguntas; i++) {	
		char resposta_observador_1[2];
		strcpy(resposta_observador_1, observador_1[i]);
		char resposta_observador_2[2];
		strcpy(resposta_observador_2, observador_2[i]);
		
		char SIM[2] = "S";
		char NAO[2] = "N";
		
		if(strcmp(resposta_observador_2,SIM) == 0 and strcmp(resposta_observador_1,SIM) == 0) {
			A+=1;	
		}
		else if(strcmp(resposta_observador_2,NAO) == 0 and strcmp(resposta_observador_1,SIM) == 0) {
			C+=1;
		}
		else if(strcmp(resposta_observador_2,SIM) == 0 and strcmp(resposta_observador_1,NAO) == 0) {
			B+=1;
		}
		else if(strcmp(resposta_observador_2,NAO) == 0 and strcmp(resposta_observador_1,NAO) == 0) {
			D+=1;
		}
	}
	
	A1 = A + B;
	A2 = C + D;
	B1 = A + C;
	B2 = B + D;
	total = B1 + B2;
	resultado_func_concordancia_esperada = ((A1 * B1) + (A2 * B2)) / pow(total,2);
	
	return resultado_func_concordancia_esperada;
}

float concordancia_kappa(float resultado_concordancia_observada,float resultado_concordancia_esperada) {
	if(resultado_concordancia_esperada == 1) {
		return NULL;
	}
	else {
		float resultado_func_concordancia_kappa = (resultado_concordancia_observada - resultado_concordancia_esperada) / (1 - resultado_concordancia_esperada);
		
		return resultado_func_concordancia_kappa;
	}
}

const char* classificacao_kappa(float resultado_concordancia_kappa){
	if(resultado_concordancia_kappa == NULL){
		return "Não foi possível calcular a classificação";
	}
	else if(resultado_concordancia_kappa == 0) {
  		return "Pobre";
	}
	else if(resultado_concordancia_kappa > 0 and resultado_concordancia_kappa <= 0.20) {
  		return "Ligeira";
	}
	else if(resultado_concordancia_kappa >= 0.21 and resultado_concordancia_kappa <= 0.40) {
  		return "Considerável";
	}
	else if(resultado_concordancia_kappa >= 0.41 and resultado_concordancia_kappa <= 0.60) {
  		return "Moderada";
	}
	else if(resultado_concordancia_kappa >= 0.61 and resultado_concordancia_kappa <= 0.80) {
  		return "Substancial";
	}
	else if(resultado_concordancia_kappa >= 0.81 and resultado_concordancia_kappa <= 1) {
  		return "Excelente";
	}
}

main()
{	
	setlocale(LC_ALL, "Portuguese");
	
	const int total_perguntas = 10;
	char observador_1[total_perguntas][2];
	char observador_2[total_perguntas][2];

	printf("Observador 1\n");
	for(int i=0; i<total_perguntas; i++) {
		printf("\nInsira o %d resultado: ", i+1);
		scanf("%s", &observador_1[i]);
	}
	system("cls");
	
	printf("Observador 2\n");
	for(int j=0; j<total_perguntas; j++) {
		printf("\nInsira o %d resultado: ", j+1);
		scanf("%s", &observador_2[j]);
	}
	system("cls");
	
	float resultado_concordancia_observada = concordancia_observada(total_perguntas,observador_1, observador_2);
	float resultado_concordancia_esperada = concordancia_esperada(total_perguntas,observador_1, observador_2);
	float resultado_concordancia_kappa = concordancia_kappa(resultado_concordancia_observada,resultado_concordancia_esperada);
	
	printf("O valor da Concordância observada é: %.2f", resultado_concordancia_observada);
	printf("\n\nO valor da Concordância esperada é: %.2f", resultado_concordancia_esperada);
	printf("\n\no valor da Concordância Kappa é: %.6f", resultado_concordancia_kappa);
	printf("\n\nA classificação da Concordância Kappa é: %s", classificacao_kappa(resultado_concordancia_kappa));
	
}
	

