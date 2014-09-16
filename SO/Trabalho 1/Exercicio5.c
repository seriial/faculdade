#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int tentativas, numeroUsuario, numeroSorteado;

int sortear(){
	int x;
	srand( (unsigned)time(NULL) );
	x = rand() %3;
	return x;
}

void welcome(){
	printf("%s%s", "<<--->>                 BEM VINDO AO JOGO DO ADVINHA!                <<--->>!", "\n");
	printf("%s%s", "<<-  ------------------------------------------------------------------- ->>!", "\n");
	printf("%s%s", "<<-             Neste jogo você tem que acertar o numero sorteado        ->>!", "\n");
	printf("%s%s", "<<-  Caso erre sua tentativa, diremos se foi maior ou menor ao sorteado! ->>!", "\n");
	printf("%s%s", "<<-                               BOA SORTE!                             ->>!", "\n");
	printf("%s%s", "<<--->> ------------------------------------------------------------ <<--->>!", "\n");
}

void perguntar_numero(){
    printf("%s", "<<--  Digite um numero: ");
	scanf("%d", &numeroUsuario);
}
 
int main(void){
    int ganhador = 0;
    welcome();
    numeroSorteado = sortear();
    
    do{
		perguntar_numero();    	
    	if(numeroUsuario == numeroSorteado){
    		printf("%s%d%s%s", "<<--->>           Párabens você acertou com ",tentativas, " tentativas!         <<--->>", "\n");
    		ganhador = 1;
    	}else{
    		if(numeroUsuario > numeroSorteado){
    			printf("%s%s",   "<<-         O numero que você digitou é maior que o numero sorteado!     ->>", "\n");
    		}else{
    		    printf("%s%s",   "<<-         O numero que você digitou é menor que o numero sorteado!     ->>", "\n");
    		}
    		tentativas +=1;
    	}  	
    }while(ganhador != 1); 	
}
