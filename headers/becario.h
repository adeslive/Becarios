/*
 * becario.h
 *
 *  Created on: Apr 19, 2018
 *      Author: adesl
 */


#include <memory>
#include <thread>
#include <iostream>
#include "tarea.h"

#ifndef BECARIO_H_
#define BECARIO_H_

using namespace std;
/*
 * Estado 1 = Esta trabajando
 * Estado 0 = No esta trabajando
 */

class Becario{
public:
	Becario (int id, int idg);
        ~Becario();
        void empezar(){
            becarioHilo = new thread(&Becario::becarioMain, this);
            std::cout<<"Hilo creado!";
        }

private:
	int id;
	int idg;
	bool estado;
	Tarea tarea;
        thread* becarioHilo;
        void becarioMain(){
            empezar();
        }
};

Becario::Becario(int id, int idg){
    this->id = id;
    this->idg = idg;
    this->empezar();
}
#endif /* BECARIO_H_ */
