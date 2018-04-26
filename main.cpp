/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: adesl
 *
 * Created on April 20, 2018, 1:44 PM
 */

#include <pthread.h>
#include <iostream>
#include "./headers/grupo.h"

using namespace std;
int main(int argc, char** argv) {
    
    Grupo* grupo1 = new Grupo(1,1);
    cout<<grupo1->get_becarios()[0];
    grupo1->manejarBecarios();
    
    
    return 0;
}

