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

#include <queue>
#include "tarea.h"

class becario
{
public:
    int id;
    int idg;
    tarea* tareaActual;
    std::queue<tarea*> tareasIncompletas;
    
    becario(int idg, int id)
    {
        this->idg = idg;
        this->id = id;
    }
};

#endif /* BECARIO_H */

