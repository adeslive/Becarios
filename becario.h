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
#include <string>
#include "tarea.h"

class becario
{
public:
    int id;
    int idg;
    bool habilitado;
    bool sinTarea;
    tarea* tareaActual;
    std::vector<tarea*> tareasIncompletas;
    std::vector<tarea*> tareasCompletadas;

    becario(int idg, int id)
    {
        this->idg = idg;
        this->id = id;
        this->tareaActual = nullptr;
        this->habilitado = true;
        this->sinTarea = true;   
    }
    
    void siguienteTarea(){
        this->tareaActual = this->tareasIncompletas.front();
        this->tareasIncompletas.pop_back();
    }
    
    void agregarTarea(tarea* t)
    {
        this->tareasIncompletas.push_back(t);       
    }
    
    
};

#endif /* BECARIO_H */

