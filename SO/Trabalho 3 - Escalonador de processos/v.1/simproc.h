#ifndef SIMPROC_H
#define SIMPROC_H

//Laço principal para iniciar o programa
int main(int argument_count, char *argument_value[]);
//Função para selecionar o método deacordo com o argumento passado
int select_method(char * metodo, char * parametros, char * parametros2, char * parametros3);
//Realiza a leitra do arquivo csv e atribui a struct de processos
int load_file(char * file);
//Inicializa as listas
int initialize_list();
int initialize_list_lotery();

//Métodos para manipular a fila
int order_by_arrival();
int order_by_load();
int order_by_priority();
int order_by_lotery();

//EXERCICIOS ABAIXO
int ex2();
int ex3();
int ex4(char * overhead);
int ex6(char * overhead);
int ex7(char * overhead, char * quantum);
int ex8(char * overhead);
int ex10(char * overhead);

#endif
