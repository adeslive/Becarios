/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tarea.h
 * Author: adesl
 *
 * Created on April 26, 2018, 3:08 PM
 */

#include <vector>

#ifndef TAREA_H
#define TAREA_H

class Tarea{
    
private:  
    bool tipo;
    int dificultad;
    int prioridad;
    
    
public:
    
    bool estado;
    int tiempo;
    int nBecarios;
    int tiempoT;
    std::vector<int> tiempoPorBecario;
    
};


#endif /* TAREA_H */

