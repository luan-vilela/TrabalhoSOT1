/**
 *  Arquivo responsavél por todos os métodos do despachante.
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include "memscheduler.h"

void _despachante(process *fila){

    if(findProcess(fila->id, 1) > 0){
        //Se tiver na memória Trabalha e sai
        printf("Despachante percebe que processo id:%d está na memória.\n", fila->id);
    }
    else{
        // procurar no hd
        if(findProcess(fila->id, -1) > 0){
            printf("Despachante percebe que processo id:%d está no disco e solicita que Swapper traga id:%d á memória.\n", fila->id);
            swapon(-1);
            printf("Despachante é avisado pelo Swapper que o processo id:%d esa na memória\n", fila->id);
            
        }
        else{
            // não existe processo com esse id alocado
            // colocar então na memória
            _swapper(fila, 1);
            printf("Despachante percebe que processo id:%d não existia na memória.\n", fila->id);
        }
    }


    printf("Despachante reiniciou o Timer com tq e liberou a CPU ao processo id:%d\n.", fila->id);
    sem_post(&S);
    
}