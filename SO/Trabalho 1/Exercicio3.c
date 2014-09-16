#include <stdio.h>
#include <string.h>

void inverter(char frase[]){
	char fraseInvertida[100];
	int i,j=0;
	for(i=strlen(frase)-1; i>=0; i--){
		fraseInvertida[j] = frase[i];
		j++;
	}

	printf("%s%s","Frase invertida:", "\n");
	printf("%s", fraseInvertida);
	printf("%s", "\n");
}

int main (){
	char frase[100], fraseInvertida[100];
	
	printf("Digite a frase!:");
	scanf("%[^\n]", frase);
	__fpurge(stdin);
	
	inverter(frase);	
	return 0;
}


