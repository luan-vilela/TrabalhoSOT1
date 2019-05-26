/**
 *  Arquivo responsável por todos os métodos que o escalonador
 * FCFS vai usar para manipular os processos.
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include "memscheduler.h"


void _fcfs(process **filaEntrada, process **filaPronto){
    process *newProcess;
    // Testa se fila tem processos
    if(*filaEntrada != NULL){
        newProcess = alloca_node();

        //pega o menor processo
        newProcess = getProcess(filaEntrada);
        
        // Verifica se o processo deve ser colocado
        // na fila de prontos.
        while(newProcess->tc >= getTime());

        // Se tiver espaço na memória aloca processo na fila de prontos
        if(_swapper(newProcess)){
            // remove o processo da fila entrada
            _removeProcess(newProcess->id, filaEntrada);

            // aloca no início
            if (*filaPronto == NULL){
                newProcess->next =NULL;
                newProcess->previous = NULL;
                *filaPronto = newProcess;

            }
            // aloca no final
            else{
                (*filaPronto)->previous = newProcess;
                newProcess->next = *filaPronto;
                *filaPronto = newProcess;
            }
            
            
            
        }
        else{
            printf("\n\n*** Não tem memória para alocação do processo. ***\n");
            printf(" ** Chamar swapper **.\n\n");
        }
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