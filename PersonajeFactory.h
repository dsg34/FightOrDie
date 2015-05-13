#ifndef PERSONAJEFACTORY_H
#define	PERSONAJEFACTORY_H
#include "Personaje.h"
#include "Protagonista.h"
#include "Zombie.h"

class PersonajeFactory {
public:
    PersonajeFactory();
    PersonajeFactory(const PersonajeFactory& orig);
    virtual ~PersonajeFactory();
    
    Protagonista* crearProtagonista(sf::Vector2<float> p);
    Zombie* crearZombie(int tipoZombie, sf::Vector2<float> p);
    Zombie* crearZombieNormal(sf::Vector2<float> p);
    Zombie* crearZombieRapido(sf::Vector2<float> p);
    Zombie* crearZombieGordo(sf::Vector2<float> p);
    Zombie* crearBoss(sf::Vector2<float> p);
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
    Zombie* zombie;
    sf::Texture* texturaZombieNormal;
    sf::Texture* texturaZombieRapido;
    sf::Texture* texturaZombieFuerte;
    sf::Texture* texturaProtagonista;
    
};

#endif	/* PERSONAJEFACTORY_H */

