/* 
 * File:   NivelFactory.h
 * Author: Dani
 *
 * Created on 23 de abril de 2015, 21:49
 */

#include "Nivel.h"
#include "Protagonista.h"
#ifndef NIVELFACTORY_H
#define	NIVELFACTORY_H

class NivelFactory {
public:
    NivelFactory();
    NivelFactory(const NivelFactory& orig);
    virtual ~NivelFactory();
    
    Nivel* crearNivel(int i, Protagonista* p, sf::Vector2<int> t);
    
    Nivel* crearNivel1(Protagonista* p, sf::Vector2<int> t);
    Nivel* crearNivel2(Protagonista* p, sf::Vector2<int> t);
    Nivel* crearNivel3(Protagonista* p, sf::Vector2<int> t);
private:

};

#endif	/* NIVELFACTORY_H */

