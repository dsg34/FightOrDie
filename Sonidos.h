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
    sf::Music nivel1;
    sf::Music nivel2;
    sf::Music nivel3;
    sf::Music pistola;
    sf::Music risaBoss;
    sf::Music ataqueZombie;
    sf::Music zombie1;
    sf::Music zombie2;
    
    Sonidos &operator = (const Sonidos & );
    
private:

    static Sonidos* pinstance;
};

#endif	/* SONIDOS_H */

