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
#include "NivelFactory.h"
#include "ArmaFactory.h"
#define kVel 5

#ifndef MUNDO_H
#define	MUNDO_H

class Mundo {
public:
    Mundo(sf::RenderWindow &w, int niv);
    Mundo(const Mundo& orig);
    virtual ~Mundo();
    
    sf::Vector2<int> posicionCursor();
    bool capturarCierre();
    bool capturarPausa();
    
    int ejecutarMundo();
    
    void interpolarMundo();
    void pintarMundo();
private:
    sf::RenderWindow* window;    
    
    Protagonista* protagonista;
    PersonajeFactory* fabricaPersonaje;
    
    Nivel* nivel;
    NivelFactory* fabricaNivel;
    
    sf::Vector2<int> tamPantalla;  
    
    sf::Texture* tex;
    sf::Sprite* apuntar;
    
    sf::Clock relojUpdate;
    sf::Clock relojRender;
    
    float frecuencia;
    int contInterpolacion;
};

#endif	/* MUNDO_H */

