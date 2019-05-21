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


/****************************************************************
 *   AQUI FICA O CABEÇALHO DE TODOS OS MÉTODOS
 ****************************************************************/
void _createNode(int id, int tp, int tc, int tb, process **node);
void _createProcess(int n, process **node);

#endif