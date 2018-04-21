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
        
        static void* becarioMain(void* ){
            cout<<"Becario creado!"; 
            while(true){
                cout<<"hello";
            }
            pthread_exit(NULL);
        }
        
public:
	Becario(int id, int idg) : becarioHilo(){
            this->id = id;
            this->idg = idg;
            this->estado = 0;
            this->empezar();
        }
        
        ~Becario();
        
        void empezar(){
            pthread_create(&(this->becarioHilo), NULL, Becario::becarioMain, this);
            (void) pthread_join(this->becarioHilo, NULL);
        }
        
        friend ostream &operator<<(ostream &os, const Becario *b){
            os << "Id Grupo: " << b->idg<<" Id Becario: "<<b->id<<endl;
            return os;
        }  

};
#endif /* BECARIO_H_ */
