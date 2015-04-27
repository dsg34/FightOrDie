/* 
 * File:   Zombie.h
 * Author: USUARIO
 *
 * Created on 22 de abril de 2015, 16:56
 */

#ifndef ZOMBIE_H
#define	ZOMBIE_H

#include "Personaje.h"
#include "Arma.h"

//#include "Protagonista.h"

class Zombie: public Personaje {
public:
    Zombie(sf::Sprite* s, sf::Texture* t, sf::Vector2<float> p, int mV, int ve);
    Zombie(const Zombie& orig);
    virtual ~Zombie();
    
    void update(sf::Sprite protagonista, std::vector<Zombie*> zombies, std::vector<Arma*> armas);
    bool colisionConProta(sf::Sprite protagonista, char direccion);
    bool colisionConZombies(std::vector<Zombie*> zombies, char direccion);
    bool colisionConBalas(std::vector<Arma*> armas);
    bool colisionConGranadas(Arma* armaActual);
    void recibirDanyo(int danyo);
    void muere();
    void actualizaMuerte();
    
    //bool Colision(Protagonista player);
private:
    
};

#endif	/* ZOMBIE_H */

