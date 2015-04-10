/* 
 * File:   PersonajeFactory.h
 * Author: Dani
 *
 * Created on 10 de abril de 2015, 15:45
 */

#ifndef PERSONAJEFACTORY_H
#define	PERSONAJEFACTORY_H
#include "Personaje.h"
#include "Protagonista.h"

class PersonajeFactory {
public:
    PersonajeFactory();
    PersonajeFactory(const PersonajeFactory& orig);
    virtual ~PersonajeFactory();
    
    Protagonista* crearProtagonista(Arma* a, sf::Vector2<float> p);
    /*
    Zombie crearZombieNormal(sf::Vector2 p);
    Zombie* crearZombieRapido(sf::Vector2 p);
    Zombie* crearZombieFuerte(sf::Vector2 p);
    Zombie* crearZombieBoss(int i);
    Zombie* crearZombieDistancia(sf::Vector2 p);
     */
private:
    bool protagonistaCreado;
    Protagonista* protagonista;
};

#endif	/* PERSONAJEFACTORY_H */

