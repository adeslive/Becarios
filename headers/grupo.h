/*
 * grupo.h
 *
 *  Created on: Apr 19, 2018
 *      Author: adesl
 */

#include <vector>
#include <pthread.h>
#include <iostream>
#include "becario.h"

#ifndef GRUPO_H_
#define GRUPO_H_

class Grupo {
    
private:
    std::vector<Becario*> becarios;
    std::vector<pthread_t> becariosHilos;
    int rc;
    int maxBecarios;
    bool habilitado;

   
public:
	int idg;

	Grupo(int idg, int maxBecarios){
            this->idg = idg;
            this->maxBecarios = maxBecarios;
            this->becarios.resize(maxBecarios);

            for (int i = 0; i < maxBecarios; i++) {
                becarios[i] = new Becario(i,idg);
            }
        }
        
	std::vector<Becario*> get_becarios(){
            return this->becarios;
        }
        
	void set_maxBecarios(int max){
            this->maxBecarios = max;
            this->becarios.resize(maxBecarios);
        }
        
        void manejarBecarios(){
            int i = 0;
            
            for(i = 0; i < maxBecarios ; i++){
                
                pthread_t nuevoHilo;
                rc = pthread_create(&nuevoHilo, NULL, &Becario::becarioMain, (void*) this->becarios[i]);
                becariosHilos.push_back(nuevoHilo);        
            }
            
            for(i = 0; i < maxBecarios ; i++){
                pthread_join(becariosHilos[i], NULL);
            }
        }
};
#endif /* GRUPO_H_ */
