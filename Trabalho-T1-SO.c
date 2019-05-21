//https://www.youtube.com/watch?v=8EckoXGfEV4

#include <stdio.h>
#include "memscheduler.h"





int main(){
    //tmp = tamanho da memória principal
    // n = números de processos 
    // tq = time quantum
    int tmp, n, tq;
    int i;
    process *processo = NULL;
    scanf("%d", &n);
    _createProcess(n, &processo);
    
    printf("----------- SAIDA ------------\n");
    printf("---- ORDENADOS POR tc  < -----\n");
    while (processo){
       printf("%d %d %d %d\n", processo->id, processo->tp, processo->tc, processo->tb);
       processo = processo->next;
    }

    return 0;
}


