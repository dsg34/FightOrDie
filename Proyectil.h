/* 
 * File:   Proyectil.h
 * Author: Dani
 *
 * Created on 7 de abril de 2015, 16:46
 */

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h> 
#include <vector>

#ifndef PROYECTIL_H
#define	PROYECTIL_H

class Proyectil {
public:
    Proyectil();
    Proyectil(sf::Sprite* spriteProyectil, sf::Vector2<float> s, sf::Vector2<float> m, int d, int v, int r);
    Proyectil(const Proyectil& orig);
    virtual ~Proyectil();
    
    sf::Sprite* getSprite();
    int getContador();
    sf::Vector2<float> getMov();
    int getVelocidad();
    int getDanyo();
    int getRango();
    
    void setSprite(sf::Sprite s);
    void setContador(int i);
    void setMov(sf::Vector2<float> v);
    void setVelocidad(int i);
    void setDanyo(int d);
    void setRango(int r);
    
    bool updatePosition();
    void setPositionSprite(sf::Vector2<float> v);
private:

protected:
    sf::Sprite* sprite;        
    int contador;
    sf::Vector2<float> mov;
    
    int velocidad;
    int danyo;
    int rango;
};

#endif	/* PROYECTIL_H */