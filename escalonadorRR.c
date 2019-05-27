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

        while(getTime()-auxTimer < tq && newProcess->tb > 0){ 
            newProcess->tb -= 1;
            newProcess->tc += 1;
            espera();
            
        }
        
        printf("O processo id %d ficou %ds no Round-Robin com tb: %d\n", newProcess->id, getTime()-auxTimer, newProcess->tb);
        
        if(newProcess->tb <= 0){
            _removeProcess(newProcess->id, filaPronto);
            // Desconecta dos irmãos
            newProcess = disconnectBrothers(newProcess);
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