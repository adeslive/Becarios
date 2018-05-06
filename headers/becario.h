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
        if (tareaActual == nullptr) {
            for (int i = 0; i < 5; i++) {
                std::cout << this->id << ": Trabajando IDG: " << this->idg << std::endl;
            }
        }
    }
    
    void setTarea(tarea* t)
    {
        if (!this->tareasIncompletas.empty()){
            this->tareaActual = this->tareasIncompletas.front();
            this->tareasIncompletas.pop();
        }
        
    }
};

#endif /* BECARIO_H */

