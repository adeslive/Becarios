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
#include <time.h>
#include "edificio.h"
#include "tarea.h"

// Variables globales.

pthread_mutex_t mutexBecarios = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t tareasNuevas = PTHREAD_COND_INITIALIZER;

int numeroTareas = 0;
bool terminoJornada;

std::queue<tarea*> tareasPool;

class monitor
{
public:

    int maximoBecarios;
    int numeroEdificios;
    int numeroEntorpecedores;
    int r0 = 0;
    int r1 = 0;

    std::vector<edificio*> edificios;
    std::vector<pthread_t> hilosEdificios;

    monitor()
    {
        terminoJornada = false;
    }

    void crearEdificios(int ne, int mb)
    {
        this->numeroEdificios = ne;
        this->numeroEntorpecedores = ne;
        
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
        srand(time(NULL));
        int tareas = rand() % 10;
        for (int i = 0; i < tareas; i++) {
            tarea* tareaN = new tarea(numeroTareas + 1, 1 + rand() % 4, 1 + rand() % 5);
            srand(i + 2);
            tareaN->desc_print();
            tareasPool.push(tareaN);
            numeroTareas++;
        }
        std::cout << numeroTareas << " tareas creadas!" << std::endl;
    }

    void asignarTareas()
    {

        int viejoR0, viejoR1;

        while (numeroTareas > 0) {

            do {
                srand(time(NULL));
                r0 = rand() % numeroEdificios;
                r1 = rand() % maximoBecarios;
            }
            while (r0 > numeroEdificios || r1 > maximoBecarios || r0 == viejoR0);

            viejoR0 = r0;
            viejoR1 = r1;

            std::cout << "Becario: " << edificios[r0]->egrupo->becarios[r1]->id + 1 << " Grupo: " << edificios[r0]->egrupo->idg + 1 << " ID tarea asignada: " << tareasPool.front()->id << std::endl;
            edificios[r0]->egrupo->becarios[r1]->agregarTarea(tareasPool.front());
            tareasPool.pop();


            numeroTareas--;
        }
    }

    void entorpecedor()
    {
        sleep(5);
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
        if (b->habilitado) {
            
            pthread_mutex_lock(&mutexBecarios);
            
            if (b->tareaActual != nullptr) {
                
                
                b->trabajar();
            }
            
            pthread_mutex_unlock(&mutexBecarios);
        }
    }

    void reporte()
    {
        for (auto edificio : this->edificios) {
            for (auto becario : edificio->egrupo->becarios) {
                for (auto tarea : becario->tareasCompletadas) {
                    tarea->print();
                }
            }
        }
    }

};


#endif /* MONITOR_H */

