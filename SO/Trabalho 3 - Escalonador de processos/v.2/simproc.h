#ifndef SIMPROC_H
#define SIMPROC_H

struct process;

//Laço principal para iniciar o programa
int main(int argument_count, char *argument_value[]);
//Função para selecionar o método deacordo com o argumento passado
int select_method(char * metodo, char * parametros, char * parametros2, char * parametros3);

//Operações na lista (fila)
void insere(struct process **lista, struct process *novo, int pos);
void remover(struct process **lista, int pos);
int tamanho(struct process *lista);
struct process *getPosicao(struct process *lista, int pos);
struct process *geraProcesso();
void novoProcess(struct process *novo,int pid, int carga, int chegada, int prioridade);
void liberaMemoria(struct process *velho);

void insert_arrival(char * file);
void shortest_job(int overhead, char * file);

//Exercicios
int ex2();
int ex3(struct process *lista);
int ex4(struct process *lista);
int ex5(int overhead, struct process *lista);
int ex6(struct process *lista1, struct process *lista2);
int ex7(char * overhead, char * quantum);
int ex8(char * overhead, char * quantum);
int ex9(char * overhead, char * quantum);
int ex10(char * overhead, char * quantum);

#endif
