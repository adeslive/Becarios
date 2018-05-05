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
#include <vector>
#include <pthread.h>
#include <unistd.h>
#include "binsem.h"
#include "edificio.h"

class monitor
{
public:
    int maximoBecarios;

    pthread_barrier_t barrera0;
    pthread_barrier_t barrera1;
    
    pthread_mutex_t mutexBecarios = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t mutexEdificios = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

    std::vector<edificio*> edificios;
    std::vector<pthread_t> hilosEdificios;  

    
    monitor()
    {
        binsem(1);

    }

    
    void crearEdificios(int ne, int mb)
    {
        edificios.resize(ne);
        this->maximoBecarios = mb;

        pthread_barrier_init(&barrera0, NULL, ne);
        pthread_barrier_init(&barrera1, NULL, ne*mb);
        
        for (int i = 0; i < ne; i++) {
            this->edificios[i] = new edificio(i, mb);
        }

        for (int i = 0; i < ne; i++) {
            pthread_t nuevoHilo;
            int rc = pthread_create(&hilosEdificios[i], NULL, &monitor::entradaE, (void*) edificios[i]);
            hilosEdificios.push_back(nuevoHilo);
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

    
    void iniciarHE()
    {
        for (auto hilo : this->hilosEdificios) {
            pthread_join(hilo, NULL);
        }

        iniciarHB();
    }

    
    static void* entradaE(void* e)
    {
        monitor m;
        m.monitorE((edificio*) e);
    }


    static void* entradaB(void* b)
    {
        monitor m;
        m.monitorB((becario*) b);
    }
    
    // No ingresa a los valores del monitor, pero si puede ingresar a los propios
    void monitorE(edificio* e)
    {
        pthread_mutex_lock(&mutexEdificios);
        
        pthread_mutex_unlock(&mutexEdificios);
    }

    
    void monitorB(becario* b)
    {
        pthread_mutex_lock(&mutexBecarios);
        
        pthread_mutex_unlock(&mutexBecarios);
    }
    
    
};


#endif /* MONITOR_H */

