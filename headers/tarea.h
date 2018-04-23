/*
 * tarea.h
 *
 *  Created on: Apr 19, 2018
 *      Author: adesl
 */

#ifndef TAREA_H_
#define TAREA_H_

/*
 * Estado -1 = Incompleta
 * Estado 0 = Lista para trabajarse
 * Estado 1 = Se completo la tarea
 */

class Tarea {
private:
    bool tareaLogica;
    int prioridad;
    int estado;
    int numeroBecarios;
    unsigned int dificultad;


public:
    int tiempo;

    Tarea(bool tareaLogica, int prioridad, unsigned int dificultad) {
        this->tareaLogica = tareaLogica;
        this->prioridad = prioridad;
        this->dificultad = dificultad;
        this->estado = 0;
        this->numeroBecarios++;

        tiempo = dificultad * prioridad - numeroBecarios * (tareaLogica + 1);
    }

    ~Tarea();

    void setPrioridad(int prioridad) {
        this->prioridad = prioridad;
    }

    void setEstado(int estado) {
        this->estado = estado;
    }

    void setDificultad(unsigned int dif) {
        this->dificultad = dif;
    }

    int getPrioridad() {
        return this->prioridad;
    }

    int getEstado() {
        return this->estado;
    }

    int getDificultad() {
        return this->dificultad;
    }

};
#endif /* TAREA_H_ */
