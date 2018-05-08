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
    int id;
    int iterador;
    int tiempo;
    int prioridad;
    int dificultad;
    int numeroBecarios;

    bool completada = false;

    tarea(int id, int d, int p)
    {
        this->id = id;
        if (p >= 5) {
            this->dificultad = 100;
        }else{
            this->dificultad = d;
        }
        this->numeroBecarios = 1;
        this->prioridad = p;
        iterador = tiempo = dificultad*p;
    }

    void desc_print()
    {
        printf("ID: %d  Dificultad: %d  Tiempo: %d  Prioridad: %d \n", this->id, this->dificultad, this->tiempo, this->prioridad);
    }

    void print()
    {
        printf("ID: %d \n", this->id);
    }

};


#endif /* TAREA_H */

