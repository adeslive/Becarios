/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   becario.h
 * Author: adesl
 *
 * Created on May 4, 2018, 9:28 PM
 */

#ifndef BECARIO_H
#define BECARIO_H

#include <iostream>
#include <queue>
#include "tarea.h"

class becario
{
public:
    int id;
    int idg;
    bool habilitado;
    bool sinTarea;
    tarea* tareaActual;
    std::queue<tarea*> tareasIncompletas;
    std::vector<tarea*> tareasCompletadas;

    becario(int idg, int id)
    {
        this->idg = idg;
        this->id = id;
        this->tareaActual = nullptr;
        this->habilitado = true;
        this->sinTarea = true;
        
    }

    void trabajar()
    {
        if (tareaActual != nullptr) {
                
            for (int i = 0; i < this->tareaActual->tiempo; i++) {
                printf("ID Becario:  %d  ID Grupo:  %d  ID Tarea:  %d\n", this->id+1, this->idg+1, this->tareaActual->id);
                this->tareaActual->tiempo--;
            }
            this->tareasCompletadas.push_back(tareaActual);
            
            if(this->tareasIncompletas.empty()){
                this->tareaActual == nullptr;
            }else{
                this->siguienteTarea();
            }
        }
    }
    
    void siguienteTarea(){
        this->tareaActual = this->tareasIncompletas.front();
        this->tareasIncompletas.pop();
    }
    
    void agregarTarea(tarea* t)
    {
        if (!this->tareasIncompletas.empty()){
            this->tareasIncompletas.push(t);
        }else{
            this->tareaActual = t;
        }
        
    }
    
    
};

#endif /* BECARIO_H */

