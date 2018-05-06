/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tarea.h
 * Author: adesl
 *
 * Created on May 5, 2018, 5:11 PM
 */

#ifndef TAREA_H
#define TAREA_H

class tarea
{
public:
    int tiempo;
    int prioridad;
    
    tarea(int t, int p){
        tiempo = t;
        prioridad = p;
    }
    
    void print(){
        printf(" Tiempo: %d  Prioridad: %d \n", this->tiempo, this->prioridad);
    }
    
};


#endif /* TAREA_H */

