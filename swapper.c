/**
 *  Arquivo responsavél por todos os métodos swapper.
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include "memscheduler.h"

/**
 * Verifica se existe espaço na memória e coloca o
 * processo nela.
 * Retorna 1 para processos alocados
 * Retorna 0 para processos não alocados
*/
int _swapper(process *node, int local){
    
    //verica se cabe na memória
    if(node->tp <= tmp.tmp){
        upMemory(node->tp, node->id);
        return 1;
    }
    else{
        printf("tirando da memória principal e colocando no disco\n");
        swapon(local);
    }
    return 0;
}

// Tira o processo mais antigo da memória ou do hd
// >= 1 para tirar da memoria e colocar no hd 
// < 1 para tirar do hd e colocar na memória
int swapon(int local){
    memoryRecorder *ant, *prox, *begin;
    //prox = (memoryRecorder *) malloc(sizeof(prox));
    
    ant = NULL;
    if(local > 0){
        prox = tmp.idProcess;
        begin = tmp.idProcess;
    }
    else{
        prox = hardDisk;
        begin = hardDisk;   
    }

    if(prox != NULL){
        while(prox->next != NULL){
            ant = prox;
            prox = prox->next;
        }

        if(local > 0){
            upMemoryDisk(prox->tp, prox->id);
            downMemory(prox->id);
        }
        else{
            upMemory(prox->tp, prox->id);
            downMemoryDisk(prox->id);
        }
        return 1;
    }
    else{
        return -1;
        //printf("Não existe programa mapeado na memória!\n");
    }
}