/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: adesl
 *
 * Created on April 20, 2018, 1:44 PM
 */

#include <pthread.h>
#include <cstdio>
#include <time.h>
#include "./headers/grupo.h"

using namespace std;

pthread_mutex_t mutex;

struct timespec timeout;

int Temporizador(){
    clock_gettime(CLOCK_REALTIME, &timeout);
    timeout.tv_sec += 1;
            
    int temp = pthread_mutex_timedlock(&mutex,&timeout);
    
    if(temp != 0) {
        const char* errVal = NULL;
        switch(temp) {
        case EINVAL: errVal = "EINVAL"; break;
        case EAGAIN: errVal = "EAGAIN"; break;
        case ETIMEDOUT: errVal = "ETIMEDOUT"; break;
        case EDEADLK: errVal = "EDEADLK"; break;
        default: errVal = "unknown.."; break;
        }
        printf("Error taking lock in thread %lu: %s (%s)\n", pthread_self(), errVal , strerror(temp));
    }
    return temp == 0;
}


void* Becario::becarioMain(void* c){
    
    int count = 1;
    
    Temporizador();
    
    Becario* b = ((Becario*) c);
    
    if(!b->tareasIncompletas.empty()){
        b->tareaActual = b->tareasIncompletas.front();
        b->tareasIncompletas.pop();

        while(b->tareaActual->tiempoT > 0){ 
            b->tareaActual->tiempoT--;
            printf("%d : %d \n", b->getId(),count);
            count++;
        }
    }else{
        if(b->tareasIncompletas.empty()){
            pthread_cond_timedwait(&b->tPendiente, &mutex, &timeout);
        }
    }
    
    pthread_mutex_unlock (&mutex);
}


int main(int argc, char** argv) {
    
    
    int rc = pthread_mutex_init(&mutex, NULL);
    
    Grupo* grupo1 = new Grupo(1,2);
    //grupo1->get_becarios()[0]->setTarea(new Tarea(0,5,5));
    grupo1->get_becarios()[1]->setTarea(new Tarea(0,5,5));
    
    
    
    
    return 0;
}

