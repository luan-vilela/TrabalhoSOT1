//https://www.youtube.com/watch?v=8EckoXGfEV4

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "memscheduler.h"
// biblioteca sleep
#include <unistd.h>



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
    process *fcfs = NULL;
    
    pthread_t *p;

    scanf("%d", &n);
    _createProcess(n, &fcfs);
    
    printf("----------- SAIDA ------------\n");
    printf("---- ORDENADOS POR tc  < -----\n");
    while (fcfs){

        p = (pthread_t *) malloc(sizeof(* p));
        pthread_create(p, NULL, (void *) criadoProcesso, fcfs);
        pthread_join(*p, NULL);
        fcfs = fcfs->next;
    }

    return 0;
}


