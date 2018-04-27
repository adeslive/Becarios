/*
 * becario.h
 *
 *  Created on: Apr 19, 2018
 *      Author: adesl
 */


#include <pthread.h>
#include <iostream>
#include <queue>
#include <unistd.h>
#include "tarea.h"

#ifndef BECARIO_H_
#define BECARIO_H_


/*
 * Estado 1 = Esta trabajando
 * Estado 0 = No esta trabajando
 */


class Becario {
    
private:
    int id;
    int idg;
    bool estado;
    bool habilitado;
    pthread_t becarioHilo;
    pthread_cond_t tPendiente = PTHREAD_COND_INITIALIZER;
    Tarea* tareaActual;
    std::queue<Tarea*> tareasIncompletas;
    std::queue<Tarea*> tareasCompletas;
    

    void seccionCritica(){
        
    }


public:

    Becario(int id, int idg) { //  Inicializador del becario
        this->id = id;
        this->idg = idg;
        this->estado = 0;
        this->habilitado = 1;
        
    }

    ~Becario();
    
    static void* becarioMain (void* c); //  Función principal del hilo del becario

    friend std::ostream &operator<<(std::ostream &os, const Becario *b) { //  Sobrecarga del operador de escritura
        os << "Id Grupo: " << b->idg << " Id Becario: " << b->id << std::endl;
        return os;
    }
    
    void setTarea(Tarea* tarea){
        this->tareasIncompletas.push(tarea);
        pthread_cond_signal(&tPendiente);
    }
    
    std::queue<Tarea*> getTareasIncompletas(){
        return this->tareasIncompletas;
    }
    
    std::queue<Tarea*> getTareasCompletas(){
        return this->tareasCompletas;
    }

    bool isHabilitado() const {
        return habilitado;
    }

    bool isEstado() const {
        return estado;
    }

    int getIdg() const {
        return idg;
    }

    int getId() const {
        return id;
    }
};
#endif /* BECARIO_H_ */
