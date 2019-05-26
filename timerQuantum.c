/**
 *  Arquivo responsavél por todos os métodos Timer.
 *  Esse é o thread que não pode usar join
 * 
*/
#include <stdio.h>
#include "memscheduler.h"
// biblioteca sleep
#include <unistd.h>

// acada segundo ele incrementa o tempo
void updateTime(){

    restartTime();
    while (1){
        myTime++;
        sleep(1);
    }
}

// retorna tempo atual
int getTime(){
    return myTime;
}

// Zera tempo
void restartTime(){
    myTime = 0;
}

// espera 1 segundo
void espera(){
    sleep(1);
}