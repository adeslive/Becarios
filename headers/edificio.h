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
public:
	int ide;
	Edificio(int ide);

private:
	Grupo grupo;
};

Edificio::Edificio(int ide){
	this->ide = ide;

}

#endif /* EDIFICIO_H_ */
