/*
 * grupo.h
 *
 *  Created on: Apr 19, 2018
 *      Author: adesl
 */

#include <vector>
#include "becario.h"

#ifndef GRUPO_H_
#define GRUPO_H_

class Grupo {
    
private:
    std::vector<Becario> becarios;
    int maxBecarios;
    
public:
	int idg;

	Grupo(int idg, int maxBecarios){
            this->idg = idg;
            this->maxBecarios = maxBecarios;
            this->becarios.resize(maxBecarios);

            for (int i = 0; i < this->maxBecarios; i++) {
                    this->becarios[i] = new Becario(i, this->idg);
            }
        }
        
	std::vector<Becario> get_becarios(){
            return this->becarios;
        }
        
	void set_maxBecarios(int max){
            this->maxBecarios = max;
            this->becarios.resize(maxBecarios);
        }

};
#endif /* GRUPO_H_ */
