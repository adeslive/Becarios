/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: adesl
 *
 * Created on May 4, 2018, 8:26 PM
 */

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "monitor.h"

using namespace std;

void entorpecedor();

int numeroBecarios;
int numeroEdificios;

bool jornada = true;
monitor* m = new monitor();


int main(int argc, char** argv) {
    srand(time(NULL));
    
    numeroBecarios = 1+rand() % 5;
    numeroEdificios = 1+rand() % 3;
    
    while (jornada) {
        for (int i = 0; i < 5; i++) {
            
            if( i == 0){
                cout << "La jornada ha inciado;  Numero de Edificios: "<< numeroEdificios <<" Numero de Becarios: "<< numeroBecarios <<endl;
                m->crearEdificios(numeroEdificios, numeroBecarios);  
            }else if(i==4){
                cout << "La jornada ha terminado"<<endl;
                sleep(2);
                jornada = false;  
                break;
            }    
            
            m->crearTareas();
            
//            m->asignarTareas();
            
        }
    }

    return 0;
}

void entorpecedor(){
    sleep(5);
}