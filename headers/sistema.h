/*
 * Sistema.h
 *
 *  Created on: Apr 19, 2018
 *      Author: adesl
 */

#include <thread>
#include <vector>
#include "../headers/edificio.h"

#ifndef SISTEMA_H_
#define SISTEMA_H_

struct Sistema {
    virtual ~Sistema();
    std::vector<Edificio*> Edificios;
    
    void crear_Edificios(int numEdificios, int numBecarios){
        for(int i=0; i<numEdificios;i++){
            Edificios.emplace_back(new Edificio(i,numBecarios));
        }
    }

};


#endif /* SISTEMA_H_ */
