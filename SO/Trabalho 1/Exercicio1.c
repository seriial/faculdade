#include <stdio.h>

int main (){
	int contador = 0;
	double v1 = 0, retorno =0 ;
	printf( "Digite três valores!\n");
	while(contador < 3){
		scanf("%lf", &v1);
		retorno += v1;		
		contador= contador+ 1;
	}
	retorno = retorno/3;
			printf("%s%lf\n","Média dos 3 numeros: ", retorno);
	
	return 0;
}
