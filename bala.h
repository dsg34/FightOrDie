#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h> 
#include <vector>

#ifndef BALA_H
#define	BALA_H

class bala {
public:
    bala();
    bala(sf::Sprite spriteBala, sf::Vector2<float> s, sf::Vector2<float> m, int d, int v);
    bala(const bala& orig);
    virtual ~bala();
    
    sf::Sprite getSprite();
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
    sf::Sprite sprite;        
    int contador;
    sf::Vector2<float> mov;
    
    int velocidad;
    int danyo;
    int rango;
};

#endif	/* BALA_H */

