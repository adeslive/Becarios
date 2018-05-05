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
#include "binsem.h"
#include "edificio.h"

class monitor
{
public:

    class tarea;
    
    std::vector<edificio*> edificios;
    std::vector<pthread_t> hilosEdificios;

    binsem semBecarios;
    binsem semGrupo;
    binsem semEdificio;

    monitor()
    {
        binsem(1);

    }
    
    void crearEdificios(int ne, int mb){
        edificios.resize(ne);
        for(int i = 0; i < ne; i++){
            this->edificios[i] = new edificio(i,mb);
        }
        
        for(int i = 0; i < ne; i++){
            pthread_t nuevoHilo;
            int rc = pthread_create(&hilosEdificios[i],NULL, &monitor::entradaE, (void*) edificios[i]);
            hilosEdificios.push_back(nuevoHilo);
        }
    }
    
    
    void iniciarHB();
    
    void iniciarHE(){
        for(auto hilo : this->hilosEdificios){
            pthread_join(hilo, NULL);
        }
    }

    static void* entradaE(void* e){
        
        edificio* Edi = (edificio*) e;
        std::cout<<"EDIFICIO CREADO Y \n";
    }

    static void* entradaG(void* g);

    static void* entradaB(void* b);



};

class monitor::tarea
{
public:
    int tiempo;
};



#endif /* MONITOR_H */

