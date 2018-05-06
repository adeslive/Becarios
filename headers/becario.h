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
    bool ocupado;
    tarea* tareaActual;
    std::queue<tarea*> tareasIncompletas;

    becario(int idg, int id)
    {
        this->idg = idg;
        this->id = id;
        this->tareaActual = nullptr;
        this->habilitado = true;
        this->ocupado = true;
    }

    void trabajar()
    {
        if (tareaActual == nullptr) {
            for (int i = 0; i < 10; i++) {
                std::cout << this->id << ": Trabajando IDG: " << this->idg << std::endl;
            }
        }
    }
};

#endif /* BECARIO_H */

