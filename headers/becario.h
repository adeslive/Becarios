/*
 * becario.h
 *
 *  Created on: Apr 19, 2018
 *      Author: adesl
 */


#include <pthread.h>
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
private:
	int id;
	int idg;
	bool estado;
	Tarea tarea;
        pthread_t becarioHilo;
        static void* entradaEs(void* c);
        
        void becarioMain(){
            cout<<"Becario creado!";
            while(true){
                cout<<"hello";
            }
        }
public:
	Becario(int id, int idg) : becarioHilo(){
            this->id = id;
            this->idg = idg;
            this->estado = 0;
        }
        ~Becario();
        void empezar(){
            pthread_create(&becarioHilo, NULL, Becario::entradaEs, this);
        }
        friend ostream &operator<<(ostream &os, const Becario *b){
            os << "Id Grupo: " << b->idg<<" Id Becario: "<<b->id<<endl;
            return os;
        }  

};

void* Becario::entradaEs(void *c){
    ((Becario *) c)->becarioMain();
    return NULL;
}
#endif /* BECARIO_H_ */
