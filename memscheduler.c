/**
 * Arquivo responsável por todos os métodos de auxílio
 * aos métodos principais.
 * 
 *  - Contém métodos como alloca_node que é responsável na criação de novos nós
 * da fila.
 *  - getProcessToRR que devolve o ultimo método da fila de prontos para o escalondor RR. Assim podendo trabalhar com 
 * TBs corretos.
*/

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
    process *newProcess, *aux, **begin;
    // newProcess = alloca_node();
    // aux = alloca_node();

    begin = fila;
    aux = *fila;
    newProcess = aux;
    // Percorre a fila
    while(aux->next != NULL){
        if(newProcess->tc > aux->next->tc)
            newProcess = aux->next;
        aux = aux->next;
    }

    fila = begin;
    return newProcess;
}

process * getProcessToRR(process **fila){
    process *newProcess, *aux, **begin;
    // newProcess = alloca_node();
    // aux = alloca_node();

    begin = fila;
    aux = *fila;
    // Percorre a fila e pega ultimo processo
    while(aux->next != NULL){
        aux = aux->next;
    }   

    if((*begin)->previous == NULL && (*begin)->next != NULL){
        aux->previous->next = NULL;
        (*begin)->previous = aux;
        aux->next = *begin;
        aux->previous = NULL;
        *begin = aux;
    }

    return aux;
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
    //aux = alloca_node();
    if(*fila != NULL){
        aux = *fila;

        while (id != aux->id && aux != NULL){
            aux = aux->next;
        }
    
        if(aux->id == id){
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
    newRegister->tp = tp;

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
int downMemory(int id){
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
        
        tmp.tmp += prox->tp;
        prox = NULL;
        free(prox);
        return 1;
    }
    else{
        return -1;
        //printf("Não existe programa mapeado na memória!\n");
    }

}

void upMemoryDisk(int tp, int id){
    memoryRecorder *newRegister;
    newRegister = (memoryRecorder *) malloc(sizeof(newRegister));
    newRegister->id = id;
    newRegister->tp = tp;

    if(hardDisk == NULL){
        newRegister->next = NULL;
        hardDisk = newRegister;
    }
    else{
        newRegister->next = hardDisk;
        hardDisk = newRegister;
    }

}

int downMemoryDisk(int id){
    memoryRecorder *ant, *prox, *begin;
    prox = (memoryRecorder *) malloc(sizeof(prox));
    
    ant = NULL;
    prox = hardDisk;
    begin = hardDisk;
    
    if(prox != NULL){
        
        while(prox->id != id && prox->next != NULL){
            ant = prox;
            prox = prox->next;
        }

        if(ant == NULL){
            if(prox->next != NULL){
                hardDisk = prox->next;
            }
            else{
                hardDisk = NULL;
            }

        }
        else{
            ant->next = prox->next;
            hardDisk = begin;
        }
        prox = NULL;
        free(prox);
        return 1;
    }
    else{
        return -1;
        //printf("Não existe programa mapeado na memória!\n");
    }

}

// Procura processo na memória ou no hd usando a variável local
// se local >= 1 procura na memória
// se local < 1 procura no hd
// retorna 1 se encontrar o objeto
int findProcess(int id, int local){
    memoryRecorder *ant, *prox, *begin;
    //prox = (memoryRecorder *) malloc(sizeof(prox));
    
    if(local > 0){
        prox = tmp.idProcess;
        begin = tmp.idProcess;
    }
    else{
        prox = hardDisk;
        begin = hardDisk;   
    }

    if(prox != NULL){
        while(prox->next != NULL && prox->id != id){
            prox = prox->next;
        }

        //Confirma se encontrou id na fila de processo
        if(prox->id == id){
            // retorna endereço para a cabeça
            if(local > 0)
                tmp.idProcess = begin;
            else
                hardDisk = begin;
            
            return 1;
        }
    }
    
    // processo id não localizado
    return -1;
}




// * Retorna quantidade de memória disponível no sistema
int getMemory(){
    return tmp.tmp;
}
