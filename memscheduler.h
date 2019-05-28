/**
 * # Membros do grupo:
 *      - LUAN VILELA LOPES
 *      - GIOVANNI PRATTO
 *      - ARTHUR LEAL
 * 
 *  # Todos o trabalho está em arquivo separado.
 *      - memscheduler.h é o cabeçalho e contém variáveis globais
 *      - Trabalho-T1-SO.c contém o arquivo main()
 *      - O restante são arquivos de métodos usados pela main
 * 
 * 
 *  # Para compilar entrar na pasta do trabalho e rodar
 *      - gcc *.c -o main -lpthread
 *  
 * 
 *  # Para executar.
 *      - ./main
*/

#ifndef _MEMSCHEDULER_H_
#define _MEMSCHEDULER_H_

#include <semaphore.h>

typedef struct processId{
    int id;
    int tp;
    int tc;
    int tb;
    struct processId *next;
    struct processId *previous;
}process;

//argumentos passos no pthreads
typedef struct arg_struct {
    int n;
    int tmp;
    int tb;
    int tq;
    process **filaEntrada;
    process **filaProntos;
}arguments;

//Registrador de memória
typedef struct reg{
    int id;
    int tp;
    struct reg *next;
}memoryRecorder;

// Memória primária do sistema
struct memory{
    int tmp;
    memoryRecorder *idProcess;
};

memoryRecorder *hardDisk;
struct memory tmp;
int myTime;

//declarando um semáforo
sem_t S, S_despachante;


/****************************************************************
 *   AQUI FICA O CABEÇALHO DE TODOS OS MÉTODOS
 ****************************************************************/
void *_createProcess(void *node);
void * _fcfs(void *node);
void * _RR(void *node);
void createNode(int id, int tp, int tc, int tb, process **node);
void _removeProcess(int id, process **fila);
process * alloca_node();
process * getProcess(process **fila);
void * disconnectBrothers(process *node);
int getMemory();
void upMemory(int tp, int id);
int downMemory(int id);
int _swapper(process *node, int local);
int getTime();
void restartTime();
void updateTime();
void espera();
int downMemoryDisk(int id);
void upMemoryDisk(int tp, int id);
int downMemoryDisk(int id);
int swapon(int local);
int findProcess(int id, int local);
process * getProcessToRR(process **fila);
void _despachante(process *fila);

/****************************************************************
 *   MÉTODOS QUE PRECISÃO SER IMPLEMENTADOS
 * 
 * Esses são os métodos que devem ser implementados...
 * Aqui são os métodos principais, vocês podem fazer submétodos
 * igual o que fiz, createNode. Onde o _createProcess é o principal
 * e createNode é usado por ele.
 * Os tipos de retorno não estão definidos, ou seja, pode ser alterado
 * como desajar.
 ****************************************************************/

void _timered();



// talvez faça um outra thread para ficar falando o que acontece
void _printer();


#endif