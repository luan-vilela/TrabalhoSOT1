/**
 *  Arquivo responsavél por todos os métodos swapper.
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include "memscheduler.h"

/**
 * Verifica se existe espaço na memória e coloca o
 * processo nela.
 * Retorna 1 para processos alocados
 * Retorna 0 para processos não alocados
*/
int _swapper(process *node){
    
    //verica se cabe na memória
    if(node->tp <= tmp.tmp){
        upMemory(node->tp, node->id);
        return 1;
    }
    else{

    }
    return 0;

}