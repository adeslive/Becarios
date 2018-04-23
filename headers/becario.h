/*
 * becario.h
 *
 *  Created on: Apr 19, 2018
 *      Author: adesl
 */


#include <pthread.h>
#include <iostream>
#include <chrono>
#include "tarea.h"

#ifndef BECARIO_H_
#define BECARIO_H_

using namespace std;

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
    Tarea* tarea;
    
    pthread_t becarioHilo;

    static void* entradaBecario(void* c) { //  Función principal del hilo del becario
        ((Becario*) c)->becarioMain();
        return NULL;
    }

    void* becarioMain() { //  Función principal del hilo del becario
        cout<<"Tarea no null!\n";
    }


public:

    Becario(int id, int idg) : becarioHilo() { //  Inicializador del becario
        this->id = id;
        this->idg = idg;
        this->estado = 0;
        this->habilitado = 1;
        this->tarea = NULL;
    }

    ~Becario();
    
    void empezar(){
         pthread_create(&becarioHilo, NULL, Becario::entradaBecario, this);
         pthread_join(becarioHilo, NULL);
    }

    friend ostream &operator<<(ostream &os, const Becario *b) { //  Sobrecarga del operador de escritura
        os << "Id Grupo: " << b->idg << " Id Becario: " << b->id << endl;
        return os;
    }
    
    void setTarea(Tarea* tarea){
        this->tarea = tarea;
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
