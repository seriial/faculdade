#include <stdio.h>
#include <string.h>

void verificaF(char frase[]){
	char fraseInvertida[100];
	int i,j=0;
	for(i=strlen(frase)-1; i>=0; i--){
		fraseInvertida[j] = frase[i];
		j++;
	}
	
	printf("%s%s", "### VERIFICAÇÃO 01 (FUNÇÃO CRIADA NO EX. 3) ###", "\n");
	if(strcmp(fraseInvertida,frase) == 0){
		printf("%s%s%s","A frase: '",frase,  "' É PALINDROMO!");
	}else{
		printf("%s%s%s","A frase: '",frase,  "' NÃO É PALINDROMO!");
	}
	printf("%s", "\n");
}
void verificaC(char frase[]){
	int contadorInverso = 0, i,igual =0;
	for(i=strlen(frase)-1; i>=0; i--){
		if(frase[contadorInverso] == frase[i] ){
			igual = 1;
		}else{
			igual = 0;
		}
		contadorInverso++;
	}
	
	printf("%s%s", "### VERIFICAÇÃO 02 (CARACTERE POR CARACTERE) ###", "\n");
	if(igual == 1){
		printf("%s%s%s","A frase: '",frase,  "' É PALINDROMO!");
	}else{
		printf("%s%s%s","A frase: '",frase,  "' NÃO É PALINDROMO!");
	}
	printf("%s", "\n");
}

int main (){
	char frase[100], fraseInvertida[100];
	
	printf("Digite a frase!:");
	scanf("%[^\n]", frase);
	__fpurge(stdin);
	
	verificaF(frase);	
	verificaC(frase);
	return 0;
}

