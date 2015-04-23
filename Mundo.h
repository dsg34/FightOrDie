/* 
 * File:   Mundo.h
 * Author: Dani
 *
 * Created on 23 de abril de 2015, 18:21
 */

#include <math.h> 
#include <vector>
#include "Protagonista.h"
#include "HUD.h"
#include "ArmaFactory.h"
#include "Nivel.h"
#define kVel 5

#ifndef MUNDO_H
#define	MUNDO_H

class Mundo {
public:
    Mundo();
    Mundo(const Mundo& orig);
    virtual ~Mundo();
    
    sf::Vector2<int> posicionCursor(sf::RenderWindow &window);
    void ejecutarMundo();
private:

};

#endif	/* MUNDO_H */

