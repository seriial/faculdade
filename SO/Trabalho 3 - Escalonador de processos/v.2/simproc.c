#include "simproc.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define tam 255

struct process{
    int pid;
    int carga;
    int chegada;
    int prioridade;
    struct process *prox;
};

struct process *laprocess = NULL;

int main(int argument_count, char *argument_value[]){
    select_method(argument_value[1], argument_value[2], argument_value[3], argument_value[4]);
    return 0;
}

int select_method(char * metodo, char * parametros, char * parametros2, char * parametros3){
    int cod_error = 0;

    if(strcmp(metodo, "ex2") == 0) {
        insert_arrival(parametros);
	    cod_error = ex2(laprocess); 
    }else if(strcmp(metodo, "ex3") == 0) {
        insert_arrival(parametros);
		cod_error = ex3(laprocess);
	}else if(strcmp(metodo, "ex4") == 0) {
        insert_arrival(parametros);
		cod_error = ex4(laprocess);
	}else if(strcmp(metodo, "ex5") == 0) {
        insert_arrival(parametros);
        int overhead = atoi(parametros2);
		cod_error = ex5(overhead, laprocess);
	}else if(strcmp(metodo, "ex6") == 0) {
        int overhead = atoi(parametros2);
        shortest_job(overhead, parametros);
		//cod_error = ex6(laprocess);
    }else if(strcmp(metodo, "ex7") == 0) {
		cod_error = ex7(parametros2, parametros3);
	}else if(strcmp(metodo, "ex8") == 0) {
		cod_error = ex8(parametros2, parametros3);
	}else if(strcmp(metodo, "ex9") == 0) {
		cod_error = ex9(parametros2, parametros3);
	}else if(strcmp(metodo, "ex10") == 0) {
		cod_error = ex10(parametros2, parametros3);
	}
    return 1;
}
void insere(struct process **lista, struct process *novo, int pos){
     struct process *anterior;//
     //teste se a posicao eh valida
        
     if(pos < 1 || pos > tamanho(*lista) + 1) return;
     if(pos == 1){
         novo->prox = *lista;
         //printf("\n%d",*lista);
         *lista = novo;
         //printf("\n%d",novo->cod);
         //getch();
     }else{
         anterior = getPosicao(*lista, pos-1);
         novo->prox = anterior->prox;
         anterior->prox = novo;

     }
}

void remover(struct process **lista, int pos){
    struct process *anterior, *atual;
    
    //trata se a posicao eh valida
    if (pos < 1 || pos > tamanho(*lista)) return;//quebra a posicao
    
    if(pos==1){
        atual = *lista;//valor de lista
        //printf("\nValor de atual: %d", *atual);
        *lista = atual->prox;//com isso perdi a referencia de atual
    }else{
        anterior = getPosicao(*lista, pos-1);
        //printf("\nanterior %d - ",*anterior);
        atual = anterior->prox;
        anterior->prox = atual->prox;
    }
}

void liberaMemoria(struct process *velho){
    free(velho);
}

int tamanho(struct process *lista){
    int i = 0;
    while(lista != NULL){
        i++;
        lista = lista->prox;
    }
    return i;    
}

struct process *getPosicao(struct process *lista, int pos){
    int i;
    if(pos < 1 || pos > tamanho(lista)) return NULL;
    for(i = 1; i < pos; i++){
        lista = lista->prox;
        //printf("\t\n\n\n lista %d -",*lista);
    }

    return lista;//lista eh o endereco de memoria da 1Ş posicao
}

struct process *geraProcesso(){
    struct process *novo;
    if((novo = malloc(sizeof(struct process))) == NULL){
        printf("Falha na alocaçao de memoria");
        return NULL;
    }
      // printf("%d",novo);
    return novo;
    //registra um espaco e retorna o endereco
    //ou apenas return malloc(sizeof(struct aluno));
}

void novoProcess(struct process *novo,int pid, int carga, int chegada, int prioridade){
    novo->pid = pid;
    novo->carga = carga;
    novo->chegada = chegada;
    novo->prioridade = prioridade;
}

void shortest_job(int overhead, char * file){
    insert_arrival(file);
    struct process *aux1 = laprocess;//posicao
    struct process *fila1 = NULL;
    struct process *fila2 = NULL;
    struct process *no = NULL;      
    
    while(aux1->prox != NULL){
        if(aux1->chegada < 3){
            no = geraProcesso();
            novoProcess(no, aux1->pid, aux1->carga, aux1->chegada, aux1->prioridade);
            insere(&fila1, no, tamanho(fila1)+1);
        }else{
            no = geraProcesso();
            novoProcess(no, aux1->pid, aux1->carga, aux1->chegada, aux1->prioridade);
            insere(&fila2, no, tamanho(fila2)+1);
        }
        aux1 = aux1->prox;
    }

    ex6(fila1, fila2);
  
    double total, soma = 0, cpu, throughput;
    struct process *aux = laprocess;  

    while(aux != NULL){
        soma = soma + aux->carga;
        aux = aux->prox;
    }
    
    total = soma + ((tamanho(laprocess)-1)*overhead);
    cpu = soma/total;
    throughput = tamanho(laprocess)/total;

    printf("\nTotal: %f\n", total);
    printf("CPU: %f %%\n", cpu*100);
    printf("Throughput %f\n", throughput);

    double n =0, turnaroud= 0, anterior=0;

    aux = laprocess;
    while(aux != NULL){
        n = anterior + aux->carga + overhead;
        anterior = n;
        turnaroud += n;
        aux = aux->prox;
    }

    double a = turnaroud/tamanho(laprocess);
    printf("Turnaround: %f\n", a);    
    printf("Execução completa.\n");
    
    
}

void insert_arrival(char * file){  
    struct process *aux;//posicao
    FILE *fp;
    char ch[tam];
    int pid, carga, chegada, prioridade;
    fp = fopen(file, "r");    
    if(fp == NULL) {
        printf("O arquivo não pode ser aberto!");    
    }else{
        fgets(ch, tam, fp);
        while(!feof(fp)){  
            char* tok = strtok(ch, ";");
            pid = atoi(tok); // atribui PID a struct   
            tok = strtok(NULL, ";");    
            carga = atoi(tok); //atribui CARGA a struct
            tok = strtok(NULL, ";");     
            chegada = atoi(tok); // atribui CHEGADA a struct
            tok = strtok(NULL, ";");    
            prioridade = atoi(tok); // atribui prioridade a struct  
            aux = geraProcesso();
            novoProcess(aux, pid, carga, chegada, prioridade);
            insere(&laprocess, aux, tamanho(laprocess)+1);
            fgets(ch, tam, fp);    
        }
        fclose(fp); 
    }
}


int ex2(struct process *lista){
    if(lista == NULL){
        printf("\nFILA DE PROCESSOS VAZIA ######!");
    }else{
        lista = lista->prox;         
        while(lista != NULL){            
            printf("pid %d", lista->pid); 
            printf(" com carga %d", lista->carga);
            printf(", chegada em %d", lista->chegada);
            printf(" e prioridade %d\n", lista->prioridade);
            lista = lista->prox;
        }
    }
    printf("Execução completa.\n");
    return 1;
}

int ex3(struct process *lista){
    if(lista == NULL){
        printf("\nFILA DE PROCESSOS VAZIA ######!");
    }else{         
        while(lista != NULL){            
            printf("%d;", lista->pid); 
            lista = lista->prox;
        }
    }     
    printf("\nExecução completa.\n");    
    return 1;
}

int ex4(struct process *lista){
    if(lista == NULL){
        printf("\nFILA DE PROCESSOS VAZIA ######!");
    }else{   
        struct process *fila = lista->prox;
        printf("Execução: Nenhum Escolhido: %d", lista->pid);
        printf(" Prontos: "); 
        while(fila != NULL){            
            printf("%d:", fila->pid);
            fila = fila->prox;
        }
        printf("\n");
        while(lista != NULL){   
            fila = lista->prox;      
            //Tratando em execução
            printf("Execução: ");
            if(lista->pid == 0){
                printf("nenhum");
            }else{
                printf("%d", lista->pid);
            }
            //  Tratando escolhido
            printf(" Escolhido: ");
            if(lista->prox == NULL){
                printf("nenhum");
            }else{
                printf("%d", lista->prox->pid);
            }
            // Tratando fila de prontos
            printf(" Prontos: "); 
            while(fila != NULL){
                
                printf("%d:", fila->pid);
                fila = fila->prox;
            }
            if(lista->prox == NULL){
                printf("Vazia");    
            }

            printf("\n");  
            lista = lista->prox;    
        }
    }    
    printf("Execução completa.\n");
    return 1;
}

int ex5(int overhead, struct process *lista){

    if(lista == NULL){
        printf("\nFILA DE PROCESSOS VAZIA ######!");
    }else{   
        struct process *fila = lista->prox;
        printf("Execução: Nenhum Escolhido: %d", lista->pid);
        printf(" Prontos: "); 
        while(fila != NULL){            
            printf("%d:", fila->pid);
            fila = fila->prox;
        }
        printf("\n");
        while(lista != NULL){   
            fila = lista->prox;      

            //Tratando em execução
            printf("Execução: ");
            if(lista->pid == 0){
                printf("nenhum");
            }else{
                printf("%d", lista->pid);
            }
            //  Tratando escolhido
            printf(" Escolhido: ");
            if(lista->prox == NULL){
                printf("nenhum");
            }else{
                printf("%d", lista->prox->pid);
            }
            // Tratando fila de prontos
            printf(" Prontos: "); 
            while(fila != NULL){
                
                printf("%d:", fila->pid);
                fila = fila->prox;
            }
            if(lista->prox == NULL){
                printf("Vazia");    
            }

            printf("\n");  
            lista = lista->prox;    
        }

        double total, soma = 0, cpu, throughput;

        
        struct process *aux = laprocess;  

        while(aux != NULL){
            soma = soma + aux->carga;
            aux = aux->prox;
        }
        
        total = soma + ((tamanho(laprocess)-1)*overhead);
        cpu = soma/total;
        throughput = tamanho(laprocess)/total;

        printf("\nTotal: %f\n", total);
        printf("CPU: %f %%\n", cpu*100);
        printf("Throughput %f\n", throughput);

        double n =0, turnaroud= 0, anterior=0;

        aux = laprocess;
        while(aux != NULL){
            n = anterior + aux->carga + overhead;
            anterior = n;
            turnaroud += n;
            aux = aux->prox;
        }

        double a = turnaroud/tamanho(laprocess);
        printf("Turnaround: %f\n", a);    
        printf("Execução completa.\n");
    } 
    return 1;
}

int ex6(struct process *lista1, struct process *lista2){
    
    if(lista1 == NULL){
        printf("\nFILA DE PROCESSOS VAZIA ######!");
    }else{   
        struct process *fila1 = lista1->prox;
        struct process *fila2 = lista2->prox;

        printf("Execução: Nenhum Escolhido: %d", lista1->pid);
        printf(" Prontos: "); 
        while(fila1 != NULL){            
            printf("%d:", fila1->pid);
            fila1 = fila1->prox;
        }
        printf("\n");

        while(lista1 != NULL){   
            fila1 = lista1->prox; 
            fila2 = lista2; 

            //Tratando em execução
            printf("Execução: ");
            if(lista1->pid == 0){
                printf("nenhum");
            }else{
                printf("%d", lista1->pid);
            }
            //  Tratando escolhido
            printf(" Escolhido: ");
            if(lista1->prox == NULL){
                printf("%d", fila2->pid);
            }else{
                printf("%d", lista1->prox->pid);
            }
            // Tratando fila de prontos
            printf(" Prontos: "); 
            while(fila1 != NULL){                
                printf("%d:", fila1->pid);
                fila1 = fila1->prox;
            }
            if(lista1->prox == NULL){
                while(fila2 != NULL){                
                    printf("%d:", fila2->pid);
                    fila2 = fila2->prox;
                }
            }

            printf("\n"); 
            lista1 = lista1->prox;   
        }

        while(lista2 != NULL){   
            fila2 = lista2->prox;      

            //Tratando em execução
            printf("Execução: ");
            if(lista2->pid == 0){
                printf("nenhum");
            }else{
                printf("%d", lista2->pid);
            }
            //  Tratando escolhido
            printf(" Escolhido: ");
            if(lista2->prox == NULL){
                printf("nenhum");
            }else{
                printf("%d", lista2->prox->pid);
            }
            // Tratando fila de prontos
            printf(" Prontos: "); 
            while(fila2 != NULL){                
                printf("%d:", fila2->pid);
                fila2 = fila2->prox;
            }
            if(lista2->prox == NULL){
                printf("Vazia");
            }

            printf("\n"); 
            lista2 = lista2->prox;   
        }
    }   
    return 1;
}

int ex7(char * overhead, char * quantum){
    printf("Exercicio7 %s", overhead);
    return 1;
}

int ex8(char * overhead, char * quantum){
    printf("Exercicio8 %s", overhead);
    return 1;
}

int ex9(char * overhead, char * quantum){
    printf("Exercicio9 %s", overhead);
    return 1;
}

int ex10(char * overhead, char * quantum){
    printf("Exercicio10 %s", overhead);
    return 1;
}
