/* 
 * File:   Granada.h
 * Author: Dani
 *
 * Created on 8 de abril de 2015, 19:56
 */
#include <SFML/Graphics.hpp>

#ifndef GRANADA_H
#define	GRANADA_H


class Granada {
public:
    Granada(sf::Vector2<int> s, sf::Vector2<int> m, int d, sf::Vector2<int> pos);
    Granada(const Granada& orig);
    virtual ~Granada();
    
    int getContador();
    sf::Vector2<int> getIteracionExplosion();
    sf::Sprite* getSprite();
    sf::Vector2<float> getMov();
    int getVelocidad();
    int getRango();
    int getDanyo();
    sf::Vector2<int> getPosAnterior();
    sf::Vector2<int> getPosActual();
    int getEstado();
            
    void setContador(int c);
    void setIteracionExplosion(sf::Vector2<int> v);
    void setSprite(sf::Sprite* s);
    void setRecorteSprite(int i, int j);
    void setMov(sf::Vector2<float> m);
    void setVelocidad(int vel);
    void setRango(int r);
    void setDanyo(int g);
    void setPosAnterior(sf::Vector2<int> v);
    void setPosActual(sf::Vector2<int> v);
    
    int updateGranada();
    void pintarGranada(sf::RenderWindow &window);
protected:    
    int contador;
    int velocidad;
    int rango;
    int danyo;
    int estado;
    
    sf::Vector2<int> iteracionExplosion;
    sf::Sprite* sprite;
    sf::Vector2<float> mov;
    
    sf::Vector2<int> posAnterior;
    sf::Vector2<int> posActual;
    sf::Vector2<int> posicionFinal;
    
private:

};

#endif	/* GRANADA_H */

