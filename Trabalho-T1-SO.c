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
void imprimeMemoria(char mensagem[120]){
    printf("%s\n", mensagem);
    printf("-------------------------------------------------\n");
    printf("###    Quantidade de memória principal: %d    ###\n", tmp.tmp);
    printf("-------------------------------------------------\n");
    printf("--------   ID'S ALOCADOS NA MEMÓRIA   -----------\n");
    if(tmp.idProcess != NULL)
        do{
            printf(" %d  ", tmp.idProcess->id);
            tmp.idProcess = tmp.idProcess->next;
        }
        while (tmp.idProcess != NULL);
    printf("\n-------------------------------------------------\n");
    
    //Aguarda 1 segundo
    //sleep(1);
}

/************************************************
 * FIM DEBUG
************************************************/



int main(){
    //tmp = tamanho da memória principal
    // n = números de processos 
    // tq = time quantum
    tmp.tmp = 0;
    tmp.idProcess = NULL;
    int i;
    process *fila_entrada = NULL;
    process *hardDisk = NULL;
    process *fila_prontos = NULL;
    arguments *args;
    pthread_t *criador_de_processos;
    pthread_t *Timer;
    pthread_t *p;


    // ***********************************************
    //cria argumentos para enviar pelas threads
    args = (arguments *) malloc(sizeof(arguments));
    args->fila = &fila_entrada;
    
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
    

    // puxa um processo da fila de entrada e coloca na fila de prontos
    _fcfs(&fila_entrada, &fila_prontos);  //puxa 1 processo e coloca na fila de pronto
    _fcfs(&fila_entrada, &fila_prontos);  //puxa 1 processo e coloca na fila de pronto
    _RR(&fila_prontos);

    // puxa um processo da fila de entrada e coloca na fila de prontos
    _fcfs(&fila_entrada, &fila_prontos);  //puxa 1 processo e coloca na fila de pronto
    _fcfs(&fila_entrada, &fila_prontos);  //puxa 1 processo e coloca na fila de pronto
    _RR(&fila_prontos);

    _fcfs(&fila_entrada, &fila_prontos);  //puxa 1 processo e coloca na fila de pronto
    _fcfs(&fila_entrada, &fila_prontos);  //puxa 1 processo e coloca na fila de pronto


    //debug

    //imprime fila de entrada
    imprimeFila(fila_entrada, "\n----------- SAIDA ------------\n---- FILA DE ENTRDA -----");

    //imprime fila de prontos
    imprimeFila(fila_prontos, "\n----------- SAIDA ------------\n---- FILA DE PRONTOS  < -----");

    imprimeMemoria("\n----------- SAIDA ------------\n---- REGISTROS DA MEMÓRIA PRINCIPAL  < -----");
    return 0;

    // NÃO PODE USAR JOIN NO THREAD TIMER
    //pthread_join(*Timer, NULL);
}


