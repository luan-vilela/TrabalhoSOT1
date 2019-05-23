#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
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
        createNode(id,tp,tc,tb,((arguments*)node)->fila);
        printf("%d %d %d %d\n", id, tp, tc, tb);

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

void _fcfs(process **filaEntrada, process **filaPronto){
    printf("ok");
    process *newProcess;

    // Testa se fila tem processos
    if(*filaEntrada != NULL){
        printf("ok");
        newProcess = alloca_node();

        //pega o menor processo
        newProcess = getProcess(filaEntrada);
        

        if (*filaPronto == NULL){
            *filaPronto = newProcess;
        }
        else{

        }

        printf("id: %d - tc: %d", newProcess->id, newProcess->tc );

        // remove processo da fila entrada
        _removeProcess(newProcess->id, filaEntrada);
    }



    // ordena do menor tc para o maior
    // else{
    //     aux = *node;
    //     begin = node;
    //     while(aux->next != NULL && tc > aux->tc){
    //         aux = aux->next;
    //     }
    //     //fim 
    //     if(tc >= aux->tc){
    //         aux->next = newProcess;
    //         newProcess->previous = aux;
    //         node = begin;
    //     }
    //     // início
    //     else if(tc < (*node)->tc ){
    //         (*node)->previous = newProcess;
    //         newProcess->next = (*node);
    //         *node = newProcess;
    //     }
    //     // meio
    //     else{
    //         newProcess->next = aux;
    //         newProcess->previous = aux->previous;
    //         aux->previous->next = newProcess;
    //         aux->previous = newProcess;
    //     }

    // }
}

//Pega o processo de menor tc da fila
process * getProcess(process **fila){
    process *newProcess, *aux;
    newProcess = alloca_node();
    aux = alloca_node();

    aux = *fila;
    newProcess = aux;
    // Percorre a fila
    while(aux->next != NULL){
        if(newProcess->tc > aux->tc)
            newProcess = aux;

        aux = aux->next;
    }
    free(aux);
    return newProcess;
}

// aloca um processo e devolve ele
process *alloca_node(){
    process *newProcess;
    newProcess = (process *)malloc(sizeof(process));
    newProcess->previous = NULL;
    newProcess->next = NULL;
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

        aux->previous->next = aux->next;
        aux->next->previous = aux->previous;
        free(aux);
        fila = begin;

    }
    else{
        printf("Não existe processo para ser removido!\n");
    }




    
}