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
#include "edificio.h"
#include "monitor.h"

using namespace std;

/*
 * 
 */

monitor* m = new monitor();

int main(int argc, char** argv) {
    
    m->crearEdificios(1,2);
    m->iniciarHE();
    
    return 0;
}

