//https://www.youtube.com/watch?v=8EckoXGfEV4

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "memscheduler.h"
// biblioteca sleep
#include <unistd.h>


/************************************************
 * Variáveis globais
************************************************/


/* Quando um processo é criado ele chama uma função
Quando a função acaba ele é excluído da memória
Com isso cada STRUCT está em um processo
Como a struct está em um fila FCFS conseguimos
Alocar o desalocar a struct e finalizar o processo */
void criadoProcesso(process *L){
    printf("processo id: %d criado. Detalhes: \t id | \t tp | \t tc | \t tb\n ", L->id);
    printf("\t\t\t\t\t %d \t %d \t %d \t %d\n\n", L->id, L->tp, L->tc, L->tb);

    //Aguarda 1 segundo
    sleep(1);
}


int main(){
    //tmp = tamanho da memória principal
    // n = números de processos 
    // tq = time quantum
    int tmp, n, tq;
    int i;
    process *fila_entrada = NULL;
    process *hardDisk = NULL;
    process *fila_prontos = NULL;
    arguments *args;
    pthread_t *criador_de_processos;
    pthread_t *p;

    // ***********************************************
    //cria argumentos para enviar pelas threads
    args = (arguments *) malloc(sizeof(arguments));
    args->fila = &fila_entrada;
    
    // Recebe números de processos
    scanf("%d", &args->n);

    /**
     * CRIA THREAD CRIADOR DE PROCESSOS
    */
    criador_de_processos = (pthread_t *) malloc(sizeof(* criador_de_processos));
    pthread_create(criador_de_processos, NULL, (void *) _createProcess, (void *) args);
    pthread_join(*criador_de_processos, NULL);


    // puxa um processo da fila de entrada e coloca na fila de prontos
    _fcfs(&fila_entrada, &fila_prontos);


    printf("----------- SAIDA ------------\n");
    printf("---- ORDENADOS POR tc  < -----\n");
    int contador = 0;
    while (fila_entrada){

        p = (pthread_t *) malloc(sizeof(* p));
        pthread_create(p, NULL, (void *) criadoProcesso, fila_entrada);
        pthread_join(*p, NULL);
        fila_entrada = fila_entrada->next;
        contador++;
    }

    printf("--------- %d PROCESSOS  ---------\n", contador);
    return 0;
}


