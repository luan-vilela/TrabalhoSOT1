//https://www.youtube.com/watch?v=8EckoXGfEV4

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "memscheduler.h"
// biblioteca sleep
#include <unistd.h>


/************************************************
 * DEBUG
************************************************/
void imprimeFila(process *L, char mensagem[120]){

    printf("%s\n", mensagem);
    while(L!= NULL){
        printf("processo id: %d criado. Detalhes: \t id | \t tp | \t tc | \t tb\n ", L->id);
        printf("\t\t\t\t\t %d \t %d \t %d \t %d\n", L->id, L->tp, L->tc, L->tb);
        //Aguarda 1 segundo
        //sleep(1);
        L = L->next;
    }
}
void imprimeMemoria(memoryRecorder *L, char mensagem[120]){
    printf("%s\n", mensagem);
    printf("-------------------------------------------------\n");
    printf("###    Quantidade de memória principal: %d    ###\n", tmp.tmp);
    printf("-------------------------------------------------\n");
    printf("--------   ID'S ALOCADOS NA MEMÓRIA   -----------\n");
    if(L != NULL)
        do{
            printf(" %d  ", L->id);
            L = L->next;
        }
        while (L != NULL);
    printf("\n-------------------------------------------------\n");
    
    //Aguarda 1 segundo
    //sleep(1);
}

/************************************************
 * FIM DEBUG
************************************************/



int main(){

    // tmp é um struct que contém quantidade de memória e os ids mapeados
    tmp.tmp = 0;
    tmp.idProcess = NULL;
    hardDisk = NULL;
    int i;
    // filas
    process *fila_entrada = NULL;
    process *fila_prontos = NULL;
    // hd apenas ids
    
    arguments *args;
    pthread_t *criador_de_processos;
    pthread_t *escalonador_FCFS;
    pthread_t *Timer;
    pthread_t *p;


    // ***********************************************
    //cria argumentos para enviar pelas threads
    args = (arguments *) malloc(sizeof(arguments));
    args->filaEntrada = &fila_entrada;
    args->filaProntos = &fila_prontos; 
    
    // Entrada de dados
    // Recebe tmp, n, tq
    scanf("%d %d %d", &tmp.tmp, &args->n, &args->tq);

    /**
     * CRIA THREAD CRIADOR DE PROCESSOS
    */
    criador_de_processos = (pthread_t *) malloc(sizeof(* criador_de_processos));
    pthread_create(criador_de_processos, NULL, (void *) _createProcess, (void *) args);
    pthread_join(*criador_de_processos, NULL);

    /**
     * CRIA THREAD Timer
    */
    Timer = (pthread_t *) malloc(sizeof(* Timer));
    pthread_create(Timer, NULL, (void *) updateTime, NULL);
    

    /**
     * CRIA THREAD FCFS
    */
    escalonador_FCFS = (pthread_t *) malloc(sizeof(* escalonador_FCFS));
    pthread_create(escalonador_FCFS, NULL, (void *) _fcfs, (void *) args);
    pthread_join(*escalonador_FCFS, NULL);
 




    //debug
    

    //imprime fila de entrada
    imprimeFila(fila_entrada, "\n----------- SAIDA ------------\n---- FILA DE ENTRDA -----");

    //imprime fila de prontos
    imprimeFila(fila_prontos, "\n----------- SAIDA ------------\n---- FILA DE PRONTOS  < -----");

    //imprime disco
    imprimeMemoria(hardDisk, "\n----------- SAIDA ------------\n---- REGISTROS DA DISCO RÍGIDO  < -----");
    
    //imprime memória principal
    imprimeMemoria(tmp.idProcess, "\n----------- SAIDA ------------\n---- REGISTROS DA MEMÓRIA PRINCIPAL  < -----");
    return 0;

    // NÃO PODE USAR JOIN NO THREAD TIMER
    //pthread_join(*Timer, NULL);
}


