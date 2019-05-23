#ifndef _MEMSCHEDULER_H_
#define _MEMSCHEDULER_H_

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
    process **fila;
}arguments;

//Registrador de memória
typedef struct reg{
    int id;
    struct reg *next;
}memoryRecorder;

// Memória primária do sistema
struct memory{
    int tmp;
    memoryRecorder *idProcess;
};

struct memory tmp;


/****************************************************************
 *   AQUI FICA O CABEÇALHO DE TODOS OS MÉTODOS
 ****************************************************************/
void *_createProcess(void *node);
void createNode(int id, int tp, int tc, int tb, process **node);
void _fcfs(process **filaEntrada, process **filaPronto);
void _removeProcess(int id, process **fila);
int _swapper(process *node);
process * alloca_node();
process * getProcess(process **fila);
int getMemory();

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
void _rr();
void _despachante();


// talvez faça um outra thread para ficar falando o que acontece
void _printer();


#endif