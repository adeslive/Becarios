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
pthread_mutex_t mutexEspera = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexTareas = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t tareasNuevas = PTHREAD_COND_INITIALIZER;

int numeroTareas = 0;
int maximoBecarios;
int numeroEdificios;
int numeroEntorpecedores;
bool terminoJornada;

std::queue<tarea*> tareasPool;

class monitor
{
public:

    int r0 = 0;
    int r1 = 0;

    std::vector<edificio*> edificios;

    monitor()
    {
        terminoJornada = false;
    }

    void crearEdificios(int ne, int mb)
    {
        numeroEdificios = ne;
        numeroEntorpecedores = ne;

        if (ne == 1) {
            maximoBecarios = mb + 1;
        }
        else {
            maximoBecarios = mb;
        }

        for (int j = 0; j < ne; j++) {
            edificio* nuevoEd = new edificio(j, mb);
            this->edificios.push_back(nuevoEd);
        }
        
        for (auto ed : this->edificios) {
            for (int i = 0; i < maximoBecarios; i++) {
                pthread_t nuevoHilo;
                int rc = pthread_create(&ed->egrupo->hilosBecarios[i], NULL, &monitor::entradaB, (void*) ed->egrupo->becarios[i]);
                ed->egrupo->hilosBecarios.push_back(nuevoHilo);
            }
        }
    }

    static void* crearTareas(void*)
    {
        std::cout << "\n--Creando tareas--\n\n";
        srand(time(NULL));
        int tareas = rand() % 10;
        for (int i = 0; i < 5; i++) {
            tarea* tareaN = new tarea(numeroTareas + 1, 1 + rand() % 4, 1 + rand() % 5);
            srand(i + 2);
            tareaN->desc_print();
            pthread_mutex_lock(&mutexTareas);
            tareasPool.push(tareaN);
            numeroTareas++;
            pthread_mutex_unlock(&mutexTareas);
        }
        std::cout << 5 << " tareas creadas!" << std::endl;
        pthread_exit(NULL);
    }

    void asignarTareas()
    {

        int viejoR0, viejoR1;

        while (numeroTareas > 0) {

            do {
                srand(time(NULL));
                this->r0 = rand() % numeroEdificios;
                this->r1 = rand() % maximoBecarios;
            }
            while (this->r0 > numeroEdificios || this->r1 > maximoBecarios || this->r0 == viejoR0);

            viejoR0 = r0;
            viejoR1 = r1;

            if (tareasPool.front()->prioridad < 5) {
                std::cout << "Becario: " << this->edificios[r0]->egrupo->becarios[r1]->id + 1 << " Grupo: " << this->edificios[r0]->egrupo->idg + 1 << " ID tarea asignada: " << tareasPool.front()->id << std::endl;
                this->edificios[r0]->egrupo->becarios[r1]->agregarTarea(tareasPool.front());
                tareasPool.pop();
            }
            else {

                for (auto edificio : edificios) {
                    for (auto becario : edificio->egrupo->becarios) {
                        becario->agregarTarea(tareasPool.front());
                    }
                }
            }

            numeroTareas--;
        }
    }

    static void* relojMain(void*)
    {
        int seg, min, hr;

        for (int i = 0; i < 28800; i++) {

            if (seg == 60) {
                min++;
                seg = 0;
                printf("1 MIN");
            }

            if (min == 60) {
                hr++;
                min = 0;
            }

            if (hr == 8) {
                pthread_cond_signal(&cond);
                terminoJornada = true;
            }

            if (hr == 4) {

            }
        }

    }

    void entorpecedor()
    {
        sleep(5);
    }

    void iniciarHB()
    {
        for (auto ed : this->edificios) {
            for (auto hilo : ed->egrupo->hilosBecarios) {
                pthread_join(hilo, NULL);
            }
        }

    }

    static void* entradaB(void* e)
    {
        srand(time(NULL));
        int probEntorpecedor = rand() % numeroEdificios;

        tarea* tareaA;
        pthread_mutex_lock(&mutexBecarios);
        becario* b = (becario*) e;
        pthread_mutex_unlock(&mutexBecarios);

        while (terminoJornada == false) {
            pthread_mutex_lock(&mutexBecarios);
            if (b->tareasIncompletas.empty() && b->habilitado) {
                
            }
            pthread_mutex_unlock(&mutexBecarios);

            pthread_mutex_lock(&mutexBecarios);
            for (int i = 0; i < b->tareasIncompletas.size(); i++) {

                tareaA = b->tareasIncompletas[i];

                if (terminoJornada == false && b->habilitado) {
                    if (probEntorpecedor >= numeroEdificios / 2) {
                        printf("El becario %d del grupo %d esta siendo molestado por un entorpecedor!\n", b->id + 1, b->idg + 1);
                        b->nMolestado++;
                        if (b->nMolestado >= 1) {
                            printf("El becario %d del grupo %d se ha retirado!\n", b->id + 1, b->idg + 1);
                            b->habilitado = false;
                        }
                    }
                    else {
                        for (int j = 0; i < tareaA->iterador; i++) {
                            if (tareaA->tiempo > 0) {
                                tareaA->tiempo--;
                            }
                        }
                        printf("Becario:  %d  ID Grupo:  %d   #Tareas :  %lu\n", b->id + 1, b->idg + 1, tareaA->id);
                    }
                }

                b->tareasCompletadas.push_back(tareaA);
                b->tareasIncompletas.pop_back();
            }
            pthread_mutex_unlock(&mutexBecarios);
        }
    }

    void reporte()
    {
        for (auto edificio : this->edificios) {
            for (auto becario : edificio->egrupo->becarios) {
                printf("Terminado:  ID Becario:  %d  ID Grupo:  %d   #Tareas Completadas:  %lu\n", becario->id + 1, becario->idg + 1, becario->tareasCompletadas.size());
                printf("--------------------------------¡Sin Tareas! \n\n");
            }
        }
    }

};


#endif /* MONITOR_H */

