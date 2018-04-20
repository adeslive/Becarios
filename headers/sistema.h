/*
 * Sistema.h
 *
 *  Created on: Apr 19, 2018
 *      Author: adesl
 */

#include <thread>
#include <vector>
#include "edificio.h"

#ifndef SISTEMA_H_
#define SISTEMA_H_

class Sistema {
public:
	Sistema(int edificios);
	virtual ~Sistema();
	std::vector<Edificio> Edificios;

};

Sistema::Sistema(int edificios){
	for (int i=0; i<edificios; i++){
		Edificio edificioN = new Edificio(i);
		this->Edificios.push_back(edificioN);
	}
}

#endif /* SISTEMA_H_ */
