#include <stdio.h>

int main (){
	char operacao;
	int v1,v2, resultado;
	printf("Digite a operação!\n");
	scanf("%s", &operacao);
	printf("Digite dois valores!\n");
	scanf("%d", &v1);
	scanf("%d", &v2);
	switch(operacao){
		case '+':
			resultado = v1 + v2;
			break;
		case '-':
			resultado = v1 - v2;
			break;
		case '*':
			resultado = v1 * v2;
			break;
		case '/':
			resultado = v1 / v2;
			break;			
	}	
	printf("%s%d%s","Resultado da operação:" , resultado, "\n");
	return 0;
}
