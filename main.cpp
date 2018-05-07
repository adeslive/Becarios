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

#define NJORNADAS 1


using namespace std;

int numeroBecarios;
int numeroEdificios;
bool jornada = true;
monitor* m = new monitor();


int main(int argc, char** argv) {
    srand(time(NULL));
    
    numeroBecarios = 1+rand() % 5;
    numeroEdificios = 1+rand() % 3;
    
    
    if(numeroBecarios == 1){
        cout << "Becarios insuficientes"<<endl;
        jornada = false;
    }else if(numeroEdificios == 1){
        cout << "Grupos insuficientes"<<endl;
        jornada = false;
    }
    
    while (jornada) {
        for (int i = 0; i < NJORNADAS+1; i++) {
            
            if( i == 0){
                cout << "La jornada ha inciado\nNumero de Edificios: "<< numeroEdificios <<" Numero de Becarios: "<< numeroBecarios <<endl;
                sleep(2);
                m->crearEdificios(numeroEdificios, numeroBecarios);  
            }else if(i == NJORNADAS){
                cout << "\n\n--La jornada ha terminado--"<<endl;
                sleep(2);
                jornada = false;  
                break;
            }    
            cout << "--Creando tareas--\n";
            m->crearTareas();
            sleep(1);
            
            cout << "--Asignando tareas--\n";
            m->asignarTareas();
            sleep(1);
            
            cout << "--Listos para trabajar--\n";
            m->iniciarHB();
            sleep(1);
            
            cout << "--Tareas completadas--\n";
            m->reporte();
            sleep(1);
        }
    }

    return 0;
}