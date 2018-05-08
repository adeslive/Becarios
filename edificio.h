/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   edificio.h
 * Author: adesl
 *
 * Created on May 5, 2018, 1:16 PM
 */

#ifndef EDIFICIO_H
#define EDIFICIO_H

#include "grupo.h"

class edificio
{
public:
    int ide;
    grupo* egrupo;

    edificio(int ide, int mb)
    {
        this->ide = ide;
        this->egrupo = new grupo(ide, mb);
    }
};


#endif /* EDIFICIO_H */

