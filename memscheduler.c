#include <stdio.h>
#include <stdlib.h>
#include "memscheduler.h"

// aloca um processo e devolve ele
process * alloca_node(){
    process *newProcess;
    newProcess = (process *)malloc(sizeof(process));
    newProcess->previous = NULL;
    newProcess->next = NULL;
    return newProcess;
}

//Pega o processo de menor tc da fila
process * getProcess(process **fila){
    process *newProcess, *aux;
    // newProcess = alloca_node();
    // aux = alloca_node();

    aux = *fila;
    newProcess = aux;
    // Percorre a fila
    while(aux->next != NULL){
        if(newProcess->tc > aux->tc)
            newProcess = aux;
        aux = aux->next;
    }

    return newProcess;
}

void _removeProcess(int id, process **fila){
    process *aux, **begin;
    
    begin = fila;
    aux = alloca_node();
    if(fila != NULL){
        aux = *fila;
        while (id != aux->id && aux != NULL){
            aux = aux->next;
        }
    
        // testa se é o ultimo processo na fila
        if(aux->next != NULL){
            aux->previous->next = aux->next;
            aux->next->previous = aux->previous;
            fila = begin;
        }
        else{
            *fila = NULL;
        }
        //free(aux);
        

    }
    else{
        printf("Não existe processo para ser removido!\n");
    }

}

/**
 * Adiciona processo na memória
 * Recebe um (int)tmp = quantidade de memória
 * Recebe 1 processo;
 * 
*/
void upMemory(int tp, int id){
    memoryRecorder *newRegister;
    newRegister = (memoryRecorder *) malloc(sizeof(newRegister));
    tmp.tmp -= tp;
    newRegister->id = id;

    if(tmp.idProcess == NULL){
        newRegister->next = NULL;
        tmp.idProcess = newRegister;
    }
    else{
        newRegister->next = tmp.idProcess;
        tmp.idProcess = newRegister;
    }

}
/**
 * Remove 1 processo na memória
 * Recebe um (int)tmp = quantidade de memória
 * Recebe 1 processo;
 * 
*/
void downMemory(int tmp, process node){

}

// * Retorna quantidade de memória disponível no sistema
int getMemory(){
    return tmp.tmp;
}
