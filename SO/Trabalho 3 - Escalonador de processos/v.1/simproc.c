#include "simproc.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define tam 255

struct processos{
    int pid;
    int carga;
    int chegada;
    int prioridade;
};

struct processos_lotery{
    int pid;
    int carga;
    int chegada;
    int prioridade;
    int bilhete;
};

struct fila_processos{
    struct processos p_new[8];
};

struct fila_processos_loteria{
    struct processos_lotery p_new[8];
};

struct processos p[8];
struct fila_processos fila;
struct fila_processos_loteria filal;

int main(int argument_count, char *argument_value[]){
    select_method(argument_value[1], argument_value[2], argument_value[3], argument_value[3]);
    return 0;
}

int select_method(char * metodo, char * parametros, char * parametros2, char * parametros3){
    int cod_error = 0;
    load_file(parametros);

    if(strcmp(metodo, "ex2") == 0) {
	    cod_error = ex2(); 
    }else if(strcmp(metodo, "ex3") == 0) {
		cod_error = ex3();
	}else if(strcmp(metodo, "ex4") == 0) {
		cod_error = ex4(parametros2);
	}else if(strcmp(metodo, "ex5") == 0) {
		cod_error = ex6(parametros2);
	}else if(strcmp(metodo, "ex7") == 0) {
		cod_error = ex7(parametros2, parametros3);
	}else if(strcmp(metodo, "ex8") == 0) {
		cod_error = ex8(parametros2);
	}else if(strcmp(metodo, "ex10") == 0) {
		cod_error = ex10(parametros2);
	}
    return 1;
}

int initialize_list(){ 
    //realizar a inicialização de todos os processos (com ordem de entrada) na struct da fila para ordena-los após
    for(int j = 0; j < (sizeof(fila.p_new) / sizeof(fila.p_new[0])); j++){
         fila.p_new[j].pid = p[j].pid;
         fila.p_new[j].carga = p[j].carga;
         fila.p_new[j].chegada = p[j].chegada;
         fila.p_new[j].prioridade = p[j].prioridade;
    }
    return 1;
}

int initialize_list_lotery(){ 
    srand(time(NULL));
    //realizar a inicialização de todos os processos (com ordem de entrada) na struct da fila para ordena-los após
    for(int j = 0; j < (sizeof(filal.p_new) / sizeof(filal.p_new[0])); j++){
         filal.p_new[j].bilhete = (rand() % 100);
         filal.p_new[j].pid = p[j].pid;
         filal.p_new[j].carga = p[j].carga;
         filal.p_new[j].chegada = p[j].chegada;
         filal.p_new[j].prioridade = p[j].prioridade;
    }
    return 1;
}

int load_file(char * file){
    FILE *fp;
    char ch[tam];

    fp = fopen(file,"r");    
    if(fp == NULL)   {
        printf("O arquivo não pode ser aberto!");    
    }else{
        int count = 0;
        fgets(ch, tam, fp);
        while(!feof(fp)){  
            char* tok = strtok(ch, ";");
            p[count].pid = atoi(tok); // atribui PID a struct   
            tok = strtok(NULL, ";");    
            p[count].carga = atoi(tok); //atribui CARGA a struct
            tok = strtok(NULL, ";");     
            p[count].chegada = atoi(tok); // atribui CHEGADA a struct
            tok = strtok(NULL, ";");    
            p[count].prioridade = atoi(tok); // atribui prioridade a struct  
            count = count + 1; 
            fgets(ch, tam, fp);    
        }
        fclose(fp); 
    }
    return 1; 
}

int order_by_arrival(){
    initialize_list(); //inicializo a struct da fila para depois ordena-la
    if(sizeof(p) > 0){
        int menor = p[0].chegada;
        struct processos aux;
        int i,j;
        for(i = 0; i < (sizeof(fila.p_new) / sizeof(fila.p_new[0])); i++){
            menor = i;
            for(j = i; j < (sizeof(fila.p_new) / sizeof(fila.p_new[0])); j++){
                if(fila.p_new[menor].chegada > fila.p_new[j].chegada){
                    menor = j;
                    }            
            }
            aux = fila.p_new[menor];
            fila.p_new[menor] = fila.p_new[i];
            fila.p_new[i] = aux;
        }    
    }   
    return 1;
}

int order_by_load(){
    initialize_list(); //inicializo a struct da fila para depois ordena-la
    if(sizeof(p) > 0){
        int i,j, tamanho, menor = p[0].carga;
        struct processos aux;
        tamanho = sizeof(fila.p_new) / sizeof(fila.p_new[0]);
        for(i = 0; i < tamanho; i++){
            menor = i;
            for(j = i; j < (sizeof(fila.p_new) / sizeof(fila.p_new[0])); j++){
                if(fila.p_new[menor].carga > fila.p_new[j].carga){
                    menor = j;
                    }            
            }
            aux = fila.p_new[menor];
            fila.p_new[menor] = fila.p_new[i];
            fila.p_new[i] = aux;
        }    
    }  
    return 1;
}

int order_by_priority(){
    initialize_list(); //inicializo a struct da fila para depois ordena-la
    if(sizeof(p) > 0){
        int i,j, tamanho, menor = p[0].prioridade;
        struct processos aux;
        tamanho = sizeof(fila.p_new) / sizeof(fila.p_new[0]);
        for(i = 0; i < tamanho; i++){
            menor = i;
            for(j = i; j < (sizeof(fila.p_new) / sizeof(fila.p_new[0])); j++){
                if(fila.p_new[menor].prioridade < fila.p_new[j].prioridade){
                    menor = j;
                    }            
            }
            aux = fila.p_new[menor];
            fila.p_new[menor] = fila.p_new[i];
            fila.p_new[i] = aux;
        }    
    }  
    return 1;
}

int order_by_lotery(){
    initialize_list_lotery(); //inicializo a struct da fila para depois ordena-la
    if(sizeof(p) > 0){
        int i,j, tamanho, menor = filal.p_new[0].bilhete;
        struct processos_lotery aux;
        tamanho = sizeof(filal.p_new) / sizeof(filal.p_new[0]);
        for(i = 0; i < tamanho; i++){
            menor = i;
            for(j = i; j < (sizeof(filal.p_new) / sizeof(filal.p_new[0])); j++){
                if(filal.p_new[menor].bilhete < filal.p_new[j].bilhete){
                    menor = j;
                    }            
            }
            aux = filal.p_new[menor];
            filal.p_new[menor] = filal.p_new[i];
            filal.p_new[i] = aux;
        }    
    }  
    return 1;
}

int ex2(){        
    //Exibir os processos armazenados no array da struct
    for(int count = 0; count < 8; count++){
        printf("pid %d", p[count].pid); 
        printf(" com carga %d", p[count].carga);
        printf(", chegada em %d", p[count].chegada);
        printf(" e prioridade %d\n", p[count].prioridade);
    }        
    printf("Execução completa.\n");
    return 1;
}

int ex3(){  
    order_by_arrival();
    for(int count = 0; count < 8; count++){
        printf("%d;", fila.p_new[count].pid); 
    }        
    printf("\nExecução completa.\n");    
    return 1;
}

int ex4(char * overhead){
    order_by_arrival();
    int count1, count2 ;
    float througput, turnaround, total, over, over_val;
    
    over_val = atof(overhead);
    total = througput = turnaround = 0;
    for(count1 = -1; count1 < 8; count1++){
        if(count1 != -1){
            total = total + fila.p_new[count1].carga;
            over = over + over_val;
            turnaround = turnaround + total;
        }
        //Tratando em execução
        printf("Execução: ");
        if(count1 == -1){
            printf("nenhum");
        }else{
            printf("%d", fila.p_new[count1].pid);
        }
        //  Tratando escolhido
        printf(" Escolhido: ");
        if(count1 >= 7){
            printf("nenhum");
        }else{ 
            printf("%d", fila.p_new[count1+1].pid);
        }
        // Tratando fila de prontos
        printf(" Prontos: "); 
        count2 = count1+1;
        if(count2 >= 7){
            count2 = 10;
        }
        for(count2 = count2 + 1; count2 < 8; count2++){
            printf("%d:", fila.p_new[count2].pid);
        }
        if(count2 > 8){ 
            printf("Vazia");
        }   
        printf("\n");      
    }
    througput = count1/(total+(over-1));
    turnaround = turnaround/count1;

    printf("Total: %.0f \n", (total+(over-1)));
    //printf("CPU: 91,7% \n");
    printf("Throughput: %f \n",througput);
    printf("Turnaround: %f \n", turnaround);
    printf("Execução completa.\n");
    return 1;
}

int ex6(char * overhead){
    order_by_load();
    int count1, count2 ;
    float througput, turnaround, total, over, over_val;
    
    over_val = atof(overhead);
    total = througput = turnaround = 0;
    for(count1 = -1; count1 < 8; count1++){
        if(count1 != -1){
            total = total + fila.p_new[count1].carga;
            over = over + over_val; //troca de contexto, over + 1
            turnaround = turnaround + total;
        }
        //Tratando em execução
        printf("Execução: ");
        if(count1 == -1){
            printf("nenhum");
        }else{
            printf("%d - %d", fila.p_new[count1].pid, fila.p_new[count1].carga);
        }
        //  Tratando escolhido
        printf(" Escolhido: ");
        if(count1 >= 7){
            printf("nenhum");
        }else{ 
            printf("%d", fila.p_new[count1+1].pid);
        }
        // Tratando fila de prontos
        printf(" Prontos: "); 
        count2 = count1+1;
        if(count2 >= 7){
            count2 = 10;
        }
        for(count2 = count2 + 1; count2 < 8; count2++){
            printf("%d:", fila.p_new[count2].pid);
        }
        if(count2 > 8){ 
            printf("Vazia");
        }   
        printf("\n");      
    }
    througput = count1/(total+(over-1));
    turnaround = turnaround/count1;

    printf("Total: %.0f \n", (total+(over-1)));
    //printf("CPU: 91,7% ");
    printf("\nThroughput: %f \n",througput);
    printf("Turnaround: %f \n", turnaround);
    printf("Execução completa.\n");
    return 1;
}

int ex7(char * overhead, char * quantum){
    order_by_priority();
    int count1, count2 ;
    float througput, turnaround, total, over, over_val, quantum_val;
    
    over_val = atof(overhead);
    quantum_val = atof(quantum);
    total = througput = turnaround = 0;
    for(count1 = -1; count1 < 8; count1++){
        if(count1 != -1){
            total = total + fila.p_new[count1].carga;
            over = over + over_val;
            turnaround = turnaround + total;
        }
        //Tratando em execução
        printf("Execução: ");
        if(count1 == -1){
            printf("nenhum");
        }else{
            printf("%d(%d)", fila.p_new[count1].pid, fila.p_new[count1].prioridade);
        }
        //  Tratando escolhido
        printf(" Escolhido: ");
        if(count1 >= 7){
            printf("nenhum");
        }else{ 
            printf("%d(%d)", fila.p_new[count1+1].pid, fila.p_new[count1+1].prioridade);
        }
        // Tratando fila de prontos
        printf(" Prontos: "); 
        count2 = count1+1;
        if(count2 >= 7){
            count2 = 10;
        }
        for(count2 = count2 + 1; count2 < 8; count2++){
            printf("%d(%d):", fila.p_new[count2].pid, fila.p_new[count2].prioridade);
        }
        if(count2 > 8){ 
            printf("Vazia");
        }   
        printf("\n");      
    }
    througput = count1/(total+(over-1));
    turnaround = turnaround/count1;

    printf("Total: %.0f \n", (total+(over-1)));
    printf("CPU: \n");
    printf("Tempo de resposta: %f \n", (total/count1));
    printf("Execução completa.\n");
    return 1;
}

int ex8(char * overhead){
    order_by_priority();
    int count1, count2 ;
    float througput, turnaround, total, over, over_val;
    
    over_val = atof(overhead);
    total = througput = turnaround = 0;
    for(count1 = -1; count1 < 8; count1++){
        if(count1 != -1){
            total = total + fila.p_new[count1].carga;
            over = over + over_val;
            turnaround = turnaround + total;
        }
        //Tratando em execução
        printf("Execução: ");
        if(count1 == -1){
            printf("nenhum");
        }else{
            printf("%d(%d)", fila.p_new[count1].pid, fila.p_new[count1].prioridade);
        }
        //  Tratando escolhido
        printf(" Escolhido: ");
        if(count1 >= 7){
            printf("nenhum");
        }else{ 
            printf("%d(%d)", fila.p_new[count1+1].pid, fila.p_new[count1+1].prioridade);
        }
        // Tratando fila de prontos
        printf(" Prontos: "); 
        count2 = count1+1;
        if(count2 >= 7){
            count2 = 10;
        }
        for(count2 = count2 + 1; count2 < 8; count2++){
            printf("%d(%d):", fila.p_new[count2].pid, fila.p_new[count2].prioridade);
        }
        if(count2 > 8){ 
            printf("Vazia");
        }   
        printf("\n");      
    }
    througput = count1/(total+(over-1));
    turnaround = turnaround/count1;

    printf("Total: %.0f \n", (total+(over-1)));
    printf("CPU: \n");
    printf("Tempo de resposta: %f \n", (total/count1));
    printf("Execução completa.\n");
    return 1;
}

int ex10(char * overhead){
    order_by_lotery();
    int count1, count2 ;
    
    for(count1 = -1; count1 < 8; count1++){
        //Tratando em execução
        printf("Execução: ");
        if(count1 == -1){
            printf("nenhum");
        }else{
            printf("%d(Bilhete: %d)", filal.p_new[count1].pid, filal.p_new[count1].bilhete);
        }
        //  Tratando escolhido
        printf(" Escolhido: ");
        if(count1 >= 7){
            printf("nenhum");
        }else{ 
            printf("%d(Bilhete: %d)", filal.p_new[count1+1].pid, filal.p_new[count1+1].bilhete);
        }
        // Tratando fila de prontos
        printf(" Prontos: "); 
        count2 = count1+1;
        if(count2 >= 7){
            count2 = 10;
        }
        for(count2 = count2 + 1; count2 < 8; count2++){
            printf("%d(Bilhete: %d):", filal.p_new[count2].pid, filal.p_new[count2].bilhete);
        }
        if(count2 > 8){ 
            printf("Vazia");
        }   
        printf("\n");      
    }

    printf("Execução completa.\n");
    return 1;
}
