/* 
 * File:   Sonidos.h
 * Author: Xisco
 *
 * Created on 14 de mayo de 2015, 21:23
 */

#ifndef SONIDOS_H
#define	SONIDOS_H
#include <SFML/Audio.hpp>

class Sonidos {
public:
    
    static Sonidos *Instance()
    {
        if(!pinstance)
            pinstance = new Sonidos();
        return pinstance;
    }
    
    
    Sonidos();
    Sonidos(const Sonidos& orig);
    virtual ~Sonidos();
    sf::Music inicio;
    sf::Music nivel1;
    sf::Music nivel2;
    sf::Music nivel3;
    sf::Music pistola;
    sf::Music escopeta;
    sf::Music metralleta;
    sf::Music risaBoss;
    sf::Music ataqueZombie;
    sf::Music zombie1;
    sf::Music zombie2;
    sf::Music zombie3;
    sf::Music zombie4;
    sf::Music zombie5;
    sf::Music zombie6;
    sf::Music zombie7;
    sf::Music zombie8;
    
    Sonidos &operator = (const Sonidos & );
    
private:

    static Sonidos* pinstance;
};

#endif	/* SONIDOS_H */

