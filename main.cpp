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

int numeroBecarios;
int numEdificios;
int emergencia;
bool jornada = true;
monitor* m = new monitor();

pthread_t reloj;
pthread_t crear_tareas;
pthread_t asignar_tareas;




int main(int argc, char** argv) {
    srand(time(NULL));
    
    numeroBecarios = 1+rand() % 5;
    numEdificios = 1+rand() % 3;
    
    
//    if(numeroBecarios == 1){
//        cout << "Becarios insuficientes"<<endl;
//        jornada = false;
//    }else if(numeroEdificios == 1){
//        cout << "Grupos insuficientes"<<endl;
//        jornada = false;
//    }
    

    cout << "La jornada ha inciado\nNumero de Edificios: "<< 2 <<" Numero de Becarios por Grupo: "<< 2 <<endl;
    sleep(2);
    m->crearEdificios(2, 2);  

    cout << "\n--Creando tareas--\n\n";
    pthread_create(&crear_tareas, NULL, &monitor::crearTareas, NULL);
    pthread_join(crear_tareas, NULL);

    cout << "\n--Asignando tareas--\n\n";
    m->asignarTareas();
    sleep(2);

    cout << "\n--Trabajando--\n\n";
    m->iniciarHB();
    sleep(2);

    cout << "--Tareas completadas--\n";
    m->reporte();
    sleep(1);

    cout << "\n\n--La jornada ha terminado--"<<endl;
    sleep(2);
    jornada = false;  


    return 0;
}