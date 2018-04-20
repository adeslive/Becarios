/*
 * tarea.h
 *
 *  Created on: Apr 19, 2018
 *      Author: adesl
 */

#ifndef TAREA_H_
#define TAREA_H_

/*
 * Estado -1 = No se completo
 * Estado 0 = Se esta trabajando la tarea
 * Estado 1 = Se completo la tarea
 */

class Tarea {
public:
	void setPrioridad(int prioridad);
	void setEstado(int estado);
	void setDificultad(unsigned int dif);
	int getPrioridad();
	int getEstado();
	int getDificultad();

private:
	unsigned int dificultad;
	int prioridad;
	int estado;
};

void Tarea::setPrioridad(int prioridad) {
	this->prioridad = prioridad;
}

void Tarea::setEstado(int estado) {
	this->estado = estado;
}

void Tarea::setDificultad(unsigned int dif) {
	this->dificultad = dif;
}

int Tarea::getPrioridad() {
	return this->prioridad;
}

int Tarea::getEstado() {
	return this->estado;
}

int Tarea::getDificultad() {
	return this->dificultad;
}
#endif /* TAREA_H_ */
