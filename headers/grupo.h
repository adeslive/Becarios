/*
 * grupo.h
 *
 *  Created on: Apr 19, 2018
 *      Author: adesl
 */

#include <vector>
#include <pthread.h>
#include "becario.h"

#ifndef GRUPO_H_
#define GRUPO_H_

class Grupo {
    
private:
    std::vector<Becario*> becarios;
    std::vector<pthread_t> becariosHilos;
    int maxBecarios;
    bool habilitado;

   
public:
	int idg;

	Grupo(int idg, int maxBecarios){
            this->idg = idg;
            this->maxBecarios = maxBecarios;
            this->becarios.resize(maxBecarios);

            for (int i = 0; i < maxBecarios; i++) {
                becarios.emplace_back(new Becario(i,this->idg));
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
            
            while(habilitado){
                
                mtx.lock();
                
                becarios[i]->empezar();
                
                i++;
                if (i >= this->maxBecarios-1){
                    i=0;
                }
                mtx.unlock();
                    
            }
        }
};
#endif /* GRUPO_H_ */
