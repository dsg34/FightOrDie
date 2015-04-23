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
#include "NivelFactory.h"
#define kVel 5

#ifndef MUNDO_H
#define	MUNDO_H

class Mundo {
public:
    Mundo(sf::RenderWindow &w);
    Mundo(const Mundo& orig);
    virtual ~Mundo();
    
    sf::Vector2<int> posicionCursor(sf::RenderWindow &window);
    void ejecutarMundo();
    
    void pintarMundo();
private:
    sf::RenderWindow* window;    
    
    Protagonista* protagonista;
    PersonajeFactory* fabricaPersonaje;
    
    Nivel* nivel;
    NivelFactory* fabricaNivel;
    
    sf::Vector2<int> tamPantalla;  
    sf::Clock* reloj;
    sf::Time* frecuencia;
    
    sf::Texture* tex;
    sf::Sprite* apuntar;
};

#endif	/* MUNDO_H */

