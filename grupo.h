/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   grupo.h
 * Author: adesl
 *
 * Created on May 4, 2018, 9:29 PM
 */

#ifndef GRUPO_H
#define GRUPO_H

#include <vector>
#include <list>
#include <pthread.h>
#include "becario.h"

class grupo
{
public:
    int idg;
    int maxbecarios;
    std::vector<becario*> becarios;
    std::vector<pthread_t> hilosBecarios;

    grupo(int idg, int mb)
    {
        this->idg = idg;
        this->maxbecarios = mb;

        for (int i = 0; i < mb; i++) {
            becario* nuevoBe = new becario(this->idg, i);
            this->becarios.push_back(nuevoBe);
        }
    }
};


#endif /* GRUPO_H */

