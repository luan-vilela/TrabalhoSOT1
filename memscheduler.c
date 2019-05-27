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

// Pega o processo de menor tc da fila
// e retorna ele.
process * getProcess(process **fila){
    process *newProcess, *aux;
    // newProcess = alloca_node();
    // aux = alloca_node();

    aux = *fila;
    newProcess = aux;
    // Percorre a fila
    while(aux->next != NULL){
        if(newProcess->tc > aux->next->tc)
            newProcess = aux->next;
        aux = aux->next;
    }

    return newProcess;
}

// Desconecta irmãos do processo
void * disconnectBrothers(process *node){
    node->next = NULL;
    node->previous = NULL;
    return node;
}

// Remove 1 processo da fila.
// Não da free
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
        if(aux->previous == NULL && aux->next == NULL){
            *fila = NULL;
        }
        // testa se é o início da fila
        else if(aux->previous == NULL){
            aux->next->previous = NULL;
            *fila = aux->next;

        }
        // testa se é o final da fila
        else if(aux->next == NULL){
            aux->previous->next = NULL;
            fila = begin;
        }
        // testa se é meio da fila
        else{
            aux->previous->next = aux->next;
            aux->next->previous = aux->previous;
            fila = begin;            
        }

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
 * Retorna 1 se conseguiu tirar o processo da memória
 * Retorna -1 se não conseguiu tirar da memória
 * 
*/
int downMemory(int tp, int id){
    memoryRecorder *ant, *prox, *begin;
    prox = (memoryRecorder *) malloc(sizeof(prox));
    
    ant = NULL;
    prox = tmp.idProcess;
    begin = tmp.idProcess;
    
    if(prox != NULL){
        while(prox->id != id && prox->next != NULL){
            ant = prox;
            prox = prox->next;
        }

        if(ant == NULL){
            if(prox->next != NULL){
                tmp.idProcess = prox->next;
            }
            else{
                tmp.idProcess = NULL;
            }

        }
        else{
            ant->next = prox->next;
            tmp.idProcess = begin;
        }
        prox->id = 999999;
        prox = NULL;
        tmp.tmp += tp;
        free(prox);
        return 1;
    }
    else{
        return -1;
        //printf("Não existe programa mapeado na memória!\n");
    }

}

// * Retorna quantidade de memória disponível no sistema
int getMemory(){
    return tmp.tmp;
}
