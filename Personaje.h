/* 
 * File:   Personaje.h
 * Author: Dani
 *
 * Created on 6 de abril de 2015, 15:50
 */


#ifndef PERSONAJE_H
#define	PERSONAJE_H

class Personaje {
public:
    Personaje();
    Personaje(const Personaje& orig);
    virtual ~Personaje();
    virtual void update()=0; //Se emplea virtual para que, si se crea una instancia de una clase hija de personaje, se llame a los métodos de dicha clase y no a los genericos
    virtual void render(sf::RenderWindow &window)=0;

protected:
    sf::Sprite* sprite;
    int vida;
    int maxVida;
    int velocidad;
    int cont;//Contador de la posicion del sprite en la que se esta
    int direc;//Direccion del personaje
    bool muriendo;//Booleano para determinar si el personaje esta en animacion de muerte
};

#endif	/* PERSONAJE_H */

