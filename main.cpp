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

#include <cstdlib>
#include "headers/becario.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    Becario* becario = new Becario(1,1);
    
    std::cout<<endl<<becario;

    return 0;
}

