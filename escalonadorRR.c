/**
 *  Arquivo responsavél por todos os métodos do escalonador Round-Robin.
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include "memscheduler.h"

#include <unistd.h>

void _RR(process **filaPronto){
    process *newProcess;
    newProcess = alloca_node();
    
    int tq = 2;
    int auxTimer = getTime();
    while(*filaPronto != NULL && getTime()-auxTimer < tq){

        //pega o menor processo
        newProcess = getProcess(filaPronto);

        do{
            sleep(1);
            newProcess->tb -=1;
            
        }while(getTime()-auxTimer < tq && newProcess->tb > 1);
        
        printf("O processo id %d ficou %ds no Round-Robin. \n", newProcess->id, getTime()-auxTimer);

        // restarta auxiliar se não existir mais processos
        if((*filaPronto)->next == NULL && newProcess->tb > 0){
            auxTimer = getTime();
        }

    }
}