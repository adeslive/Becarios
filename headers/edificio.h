/*
 * edificio.h
 *
 *  Created on: Apr 19, 2018
 *      Author: adesl
 */

#include <thread>
#include <list>
#include "grupo.h"

#ifndef EDIFICIO_H_
#define EDIFICIO_H_

class Edificio{
    
private:
    Grupo grupo;
    
    void edificioMain(){
        
    }
    
public:
	int ide;
        Grupo* grupo;
        pthread_t hiloEdificio;
        
	Edificio(int ide, int numBecarios) : hiloEdificio(){
            this->ide = ide;
            grupo = new Grupo(ide, numBecarios);
        }

        void comenzar(){
            int r;
            r = pthread_create(&hiloEdificio, NULL, (void*)edificioMain,NULL);
            if (r){
                
            }
        }
};
#endif /* EDIFICIO_H_ */
