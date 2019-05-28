/**
 * # Membros do grupo:
 *      - LUAN VILELA LOPES
 *      - GIOVANNI PRATTO
 *      - ARTHUR LEAL
 * 
 *  # Todos o trabalho está em arquivo separado.
 *      - memscheduler.h é o cabeçalho e contém variáveis globais
 *      - Trabalho-T1-SO.c contém o arquivo main()
 *      - O restante são arquivos de métodos usados pela main
 * 
 * 
 *  # Para compilar entrar na pasta do trabalho e rodar
 *      - gcc *.c -o main -lpthread
 *  
 * 
 *  # Para executar.
 *      - ./main
*/
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
    pthread_t *escalonador_RR;
    pthread_t *Timer;
    pthread_t *p;

    sem_init(&S, 0, 0);
    sem_init(&S_despachante,0, 0);

    printf("Início da observação\n");
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
    
 
     /**
     * CRIA THREAD Round-Robin
    */
    escalonador_RR = (pthread_t *) malloc(sizeof(* escalonador_RR));
    pthread_create(escalonador_RR, NULL, (void *) _RR, (void *) args);

    pthread_join(*escalonador_FCFS, NULL);
    pthread_join(*escalonador_RR, NULL);

    printf("Término da observação\n");




    //#########################
    // debug
    
    // //imprime fila de entrada
    // imprimeFila(fila_entrada, "\n----------- SAIDA ------------\n---- FILA DE ENTRDA -----");

    // //imprime fila de prontos
    // imprimeFila(fila_prontos, "\n----------- SAIDA ------------\n---- FILA DE PRONTOS  < -----");

    // //imprime disco
    // imprimeMemoria(hardDisk, "\n----------- SAIDA ------------\n---- REGISTROS DA DISCO RÍGIDO  < -----");
    
    // //imprime memória principal
    // imprimeMemoria(tmp.idProcess, "\n----------- SAIDA ------------\n---- REGISTROS DA MEMÓRIA PRINCIPAL  < -----");
    return 0;

    // NÃO PODE USAR JOIN NO THREAD TIMER
    //pthread_join(*Timer, NULL);
}


