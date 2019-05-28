/**
 *  Arquivo responsável por todos os métodos que cria processos
 * e coloca na fila de entrada.
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include "memscheduler.h"


/**
 * Cria processos dinamicamente na memória
 * Devolve um struct do tipo process ordenado
 * com base no tc informado
 * */
void *_createProcess(void *node){
    // Variáveis de controle 
    int i;
    // variáveis para criação do processo
    int id, tp, tc, tb;
    printf("----------- ENTRADAS ------------\n");
    printf("--------- %d PROCESSOS  ---------\n", ((arguments*)node)->n);
    for(i = 0; i < ((arguments*)node)->n; i++){
        scanf("%d %d %d %d", &id, &tp, &tc, &tb);
        createNode(id,tp,tc,tb,((arguments*)node)->filaEntrada);
        printf("Criador de processos criou o processo id:%d e colocou na fila de entrada.\n", id);

    }
    
}

/**
 * Aloca processos em uma fila
*/
void createNode(int id, int tp, int tc, int tb, process **node){
    process *newProcess;
    newProcess = alloca_node();
    
    newProcess->id = id;
    newProcess->tp = tp;
    newProcess->tc = tc;
    newProcess->tb = tb;

    if(*node == NULL){
        *node = newProcess;        
    }
    // sem ordenação apenas coloca fila de entrada
    else{
        newProcess->next = *node;
        (*node)->previous = newProcess;
        *node = newProcess;
    }
}