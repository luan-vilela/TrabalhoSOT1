/**
 *  Arquivo responsável por todos os métodos que o escalonador
 * FCFS vai usar para manipular os processos.
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include "memscheduler.h"


void * _fcfs(void *node){
    process **filaEntrada, **filaPronto;
    filaEntrada = ((arguments*)node)->filaEntrada;
    filaPronto = ((arguments*)node)->filaProntos;
    process *newProcess;
    
    // Testa se fila tem processos
    while(*filaEntrada != NULL){
        newProcess = alloca_node();

        //pega o menor processo
        newProcess = getProcess(filaEntrada);

        // Verifica se o processo deve ser colocado
        // na fila de prontos.
        while(newProcess->tc >= getTime());
        printf("Escalonador FCFS de longo prazo escolheu e retirou o processo id:%d da fila de entrada.\n", newProcess->id);
        printf("Escalonador FCFS de longo prazo solicitou que Swapper traga id:%d á memória.\n", newProcess->id);

        // Se tiver espaço na memória aloca processo na fila de prontos
        if(_swapper(newProcess, 1)){
            // remove o processo da fila entrada
            _removeProcess(newProcess->id, filaEntrada);
            
            // Desconecta dos irmãos
            newProcess = disconnectBrothers(newProcess);
            
            // aloca no início
            if (*filaPronto == NULL){
                *filaPronto = newProcess;
            }
            // aloca no início
            else{
                (*filaPronto)->previous = newProcess;
                newProcess->next = *filaPronto;
                *filaPronto = newProcess;
            }
            printf("Escalonador FCFS de longo prazo colocou id:%d na fila de prontos.\n", newProcess->id);
            sem_post(&S);

        }
        
    }
}