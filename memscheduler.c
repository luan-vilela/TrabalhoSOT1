#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "memscheduler.h"

/**
 * Cria processos dinamicamente na memória
 * Devolve um struct do tipo process ordenado
 * com base no tc informado
 * */
void _createProcess(int n, process **node){
    // Variáveis de controle 
    int i;
    // variáveis para criação do processo
    int id, tp, tc, tb;
    printf("----------- ENTRADAS ------------\n");
    printf("--------- %d PROCESSOS  ---------\n", n);
    for(i = 0; i < n; i++){
        scanf("%d %d %d %d", &id, &tp, &tc, &tb);
        _createNode(id,tp,tc,tb,node);
        printf("%d %d %d %d\n", id, tp, tc, tb);

    }
    
}

void _createNode(int id, int tp, int tc, int tb, process **node){
    process *newProcess, *aux, **begin;
    newProcess = (process *)malloc(sizeof(process));
    
    newProcess->id = id;
    newProcess->tp = tp;
    newProcess->tc = tc;
    newProcess->tb = tb;
    newProcess->next = NULL;
    newProcess->previous = NULL;


    if(*node == NULL){
        *node = newProcess;        
    }
    // Ordena do menor TC para o maior TC
    else{
        aux = *node;
        begin = node;
        while(aux->next != NULL && tc > aux->tc){
            aux = aux->next;
        }
        //fim 
        if(tc >= aux->tc){
            aux->next = newProcess;
            newProcess->previous = aux;
            node = begin;
        }
        // início
        else if(tc < (*node)->tc ){
            (*node)->previous = newProcess;
            newProcess->next = (*node);
            *node = newProcess;
        }
        // meio
        else{
            newProcess->next = aux;
            newProcess->previous = aux->previous;
            aux->previous->next = newProcess;
            aux->previous = newProcess;
        }

    }

}