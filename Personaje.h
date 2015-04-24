/* 
 * File:   Personaje.h
 * Author: Dani
 *
 * Created on 6 de abril de 2015, 15:50
 */
#include <iostream>
#include <SFML/Graphics.hpp>

#ifndef PERSONAJE_H
#define	PERSONAJE_H

class Personaje {
public:
    Personaje(sf::Sprite* s, sf::Texture* t, sf::Vector2<float> p, int mV, int ve);
    Personaje(const Personaje& orig);
    virtual ~Personaje();
    //Se emplea virtual para que, si se crea una instancia de una clase hija de personaje, se llame a los métodos de dicha clase y no a los genericos
    void render(sf::RenderWindow &window);
    
    sf::Vector2<float> getPosAnterior();
    sf::Vector2<float> getPosActual();
    sf::Sprite* getSprite();
    sf::Texture* getTexture();
    int getVida();
    int getMaxVida();
    int getVelocidad();
    int getCont();//Contador de la posicion del sprite en la que se esta
    int getDirec();//Direccion del personaje
    bool getMuriendo();
    sf::FloatRect* getBoundingBox();
    //sf::FloatRect getBoundingBox();
    
    void setPosAnterior(sf::Vector2<float> v);
    void setPosActual(sf::Vector2<float> v);
    void setSprite(sf::Sprite* s);
    void setTexture(sf::Texture* t);
    void setVida(int v);
    void setMaxVida(int mV);
    void setVelocidad(int ve);
    void setCont(int c);//Contador de la posicion del sprite en la que se esta
    void setDirec(int d);//Direccion del personaje
    void setMuriendo(bool m);

protected:
    sf::Sprite* sprite;
    sf::Texture* tex;
    int vida;
    int maxVida;
    int velocidad;
    int cont;//Contador de la posicion del sprite en la que se esta
    int direc;//Direccion del personaje
    bool muriendo;//Booleano para determinar si el personaje esta en animacion de muerte
    sf::FloatRect* boundingBox;
    
    sf::Vector2<float> posAnterior;
    sf::Vector2<float> posActual;
};

#endif	/* PERSONAJE_H */

