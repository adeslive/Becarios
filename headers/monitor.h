/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   monitor.h
 * Author: adesl
 *
 * Created on May 4, 2018, 8:27 PM
 */

#ifndef MONITOR_H
#define MONITOR_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <pthread.h>
#include <unistd.h>
#include <queue>
#include "edificio.h"
#include "tarea.h"

// Variables globales.

int hr, min, seg;


pthread_mutex_t mutexBecarios = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t tareasNuevas = PTHREAD_COND_INITIALIZER;


int numeroTareas = 0;
bool ocupadoB;
bool terminoJornada;

std::queue<tarea*> tareasPool;

class monitor
{
public:

    int maximoBecarios;
    int numeroEdificios;


    std::vector<edificio*> edificios;
    std::vector<pthread_t> hilosEdificios;

    monitor()
    {
        ocupadoB = false;
        terminoJornada = false;
    }

    void crearEdificios(int ne, int mb)
    {
        this->numeroEdificios = ne;
        if (ne == 1) {
            this->maximoBecarios = mb + 1;
        }
        else {
            this->maximoBecarios = mb;
        }

        for (int j = 0; j < ne; j++) {
            edificio* nuevoEd = new edificio(j, mb);
            this->edificios.push_back(nuevoEd);
        }
    }

    void crearTareas()
    {
        for (int i = 0; i < 1; i++) {
            tarea* tareaN = new tarea(1 + rand() % 4, 1 + rand() % 4);
            srand(i + 2);
            //            tareaN->print();
            tareasPool.push(tareaN);
            numeroTareas++;
        }

    }

    // Aun no funciona
    void asignarTareas()
    {
        int r0, r1;
        while (numeroTareas > 0) {

            r0 = rand() % numeroEdificios + 1;
            r1 = rand() % maximoBecarios;

            std::cout << r0 << " " << r1 << std::endl;

            edificios[r0]->egrupo->becarios[r1]->setTarea(tareasPool.front());
            tareasPool.pop();

            srand(r0 + r1 + 10);

            numeroTareas--;
        }
    }

    void iniciarHB()
    {

        for (auto ed : this->edificios) {
            for (int i = 0; i < maximoBecarios; i++) {
                pthread_t nuevoHilo;
                int rc = pthread_create(&ed->egrupo->hilosBecarios[i], NULL, &monitor::entradaB, (void*) ed->egrupo->becarios[i]);
                ed->egrupo->hilosBecarios.push_back(nuevoHilo);
            }
        }

        for (auto ed : this->edificios) {
            for (auto hilo : ed->egrupo->hilosBecarios) {
                pthread_join(hilo, NULL);
            }
        }

    }

    static void* entradaB(void* b)
    {
        monitor m;
        m.monitorB((becario*) b);
    }

    void monitorB(becario* b)
    {

        pthread_mutex_lock(&mutexBecarios);

        //        while(b->tareaActual==nullptr){
        //            pthread_cond_wait(&tareasNuevas, &mutexBecarios);  
        //        }

        pthread_mutex_unlock(&mutexBecarios);

        b->trabajar();

    }


};


#endif /* MONITOR_H */

