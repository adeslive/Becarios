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

#include <stdlib.h>
#include <time.h>
#include "monitor.h"

#define NJORNADAS 1

using namespace std;

monitor* m = new monitor();

pthread_t reloj;
pthread_t crear_tareas;

int main(int argc, char** argv) {
    srand(time(NULL));

    int numeroBecarios = 1 + rand() % 5;
    int numEdificios = 1 + rand() % 4;


//    if(numeroBecarios < 2 ){
//        cout << "Becarios insuficientes"<<endl;
//        return 0;
//    }else if(numeroEdificios < 2){
//        cout << "Grupos insuficientes"<<endl;
//        return 0;
//    }
    
    cout << "La jornada ha inciado\nNumero de Edificios: " << numeroBecarios << " Numero de Becarios por Grupo: " << numEdificios << endl;
    sleep(2);
    m->crearEdificios(5, 5);


    for (int i = 0; i < 2; i++) {

        pthread_create(&crear_tareas, NULL, &monitor::crearTareas, NULL);
        pthread_join(crear_tareas, NULL);


        m->asignarTareas();

        cout << "\n--Trabajando--\n\n";
        m->iniciarHB();

    }

    cout << "--Tareas completadas--\n";
    m->reporte();
    sleep(2);

    cout << "\n\n--La jornada ha terminado--" << endl;
    sleep(2);


    return 0;
}