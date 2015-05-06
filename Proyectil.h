#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h> 
#include <vector>

#ifndef PROYECTIL_H
#define	PROYECTIL_H

class Proyectil {
public:
    Proyectil();
    Proyectil(sf::Sprite* spriteProyectil, sf::Texture* t, sf::Vector2<float> s, sf::Vector2<float> m, int d, int v, int r);
    Proyectil(const Proyectil& orig);
    virtual ~Proyectil();
    
    sf::Sprite* getSprite();
    int getContador();
    sf::Vector2<float> getMov();
    int getVelocidad();
    int getDanyo();
    int getRango();
    sf::Vector2<float> getPosAnterior();
    sf::Vector2<float> getPosActual();
    
    void setSprite(sf::Sprite s);
    void setContador(int i);
    void setMov(sf::Vector2<float> v);
    void setVelocidad(int i);
    void setDanyo(int d);
    void setRango(int r);
    void setPosAnterior(sf::Vector2<float> v);
    void setPosActual(sf::Vector2<float> v);
    
    bool updatePosition();
    void setPositionSprite(sf::Vector2<float> v);
    void mover(float x, float y);
private:

protected:
    sf::Sprite* sprite;     
    sf::Texture* tex;
    int contador;
    sf::Vector2<float> mov;
    
    int velocidad;
    int danyo;
    int rango;
    
    sf::Vector2<float> posAnterior;
    sf::Vector2<float> posActual;
};

#endif	/* PROYECTIL_H */
