/* 
 * File:   Protagonista.h
 * Author: Dani
 *
 * Created on 6 de abril de 2015, 18:31
 */

#ifndef PROTAGONISTA_H
#define	PROTAGONISTA_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h> 
#include <vector>
#include "Personaje.h"

class Protagonista: public Personaje {
public:
    Protagonista();
    Protagonista(const Protagonista& orig);
    virtual ~Protagonista();
private:

};

#endif	/* PROTAGONISTA_H */

