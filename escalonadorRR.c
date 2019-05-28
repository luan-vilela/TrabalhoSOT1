/**
 *  Arquivo responsavél por todos os métodos do escalonador Round-Robin.
 * 
*/
#include <stdio.h>
#include <stdlib.h>
#include "memscheduler.h"

#include <unistd.h>

//void * _fcfs(void *node){
void * _RR(void *node){

    
    sem_wait(&S);

    process **filaPronto;
    filaPronto = ((arguments*)node)->filaProntos;
    process *newProcess;
    int tq = ((arguments*)node)->tq;
    int auxTimer = getTime();
    while(*filaPronto != NULL && getTime()-auxTimer < tq){
        

        //pega o menor processo
        newProcess = getProcessToRR(filaPronto);
        printf("Timer informa ao Escalonador Round-Robin de CPU que porcesso id:%d atualmente em execução precisa ser retirado da CPU.\n", newProcess->id);
        printf("Escalonador Round-Robin de CPU escolheu o processo id:%d, retirou-o da fila de prontos e o encaminhou ad Despachente.\n"), newProcess->id;
        //_despachante
        _despachante(newProcess);
        sem_wait(&S);
        auxTimer = getTime();
        
        while(getTime()-auxTimer < tq && newProcess->tb > 0){ 
            newProcess->tb -= 1;
            newProcess->tc += 1;
            espera();
        }

        
        //void downMemory(int tp, int id);
        if(newProcess->tb <= 0){
            printf("Processo id:%d terminou sua execução.\n", newProcess->id);
            _removeProcess(newProcess->id, filaPronto);
            // Desconecta dos irmãos
            newProcess = disconnectBrothers(newProcess);
            downMemory(newProcess->id);
            
        }
        // restarta auxiliar se não existir mais processos
        if((*filaPronto) == NULL){
            free(newProcess);
            break;
        }
        else{
            auxTimer = getTime();
           
        }
    }
}