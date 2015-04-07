/* 
 * File:   Protagonista.h
 * Author: Dani
 *
 * Created on 6 de abril de 2015, 18:31
 */

#ifndef PROTAGONISTA_H
#define	PROTAGONISTA_H

#include "Arma.h"
#include "Personaje.h"

class Protagonista: public Personaje {
public:
    Protagonista(sf::Sprite* p, Arma* a);
    Protagonista(const Protagonista& orig);
    virtual ~Protagonista();
private:
    int prueba;
    Arma* arma;
    Arma* armaSec;
};

#endif	/* PROTAGONISTA_H */

