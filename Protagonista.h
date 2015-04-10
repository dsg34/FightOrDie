/* 
 * File:   Protagonista.h
 * Author: Dani
 *
 * Created on 6 de abril de 2015, 18:31
 */

#ifndef PROTAGONISTA_H
#define	PROTAGONISTA_H

#include "Arma.h"
#include "Personaje.h"

class Protagonista: public Personaje {
public:
    Protagonista(sf::Sprite* s, sf::Texture* t, Arma* a, sf::Vector2<float> p, int mV, int ve);
    Protagonista(const Protagonista& orig2);
    virtual ~Protagonista();
    
    Arma* getArma();
    //std::Vector<Recurso*> getInventario();
    
    void setArma(Arma* a);
    //void setInventario(std::Vector<Recurso*> i);
private:

    Arma* arma;
    //std::Vector<Recurso*> inventario;
    
};

#endif	/* PROTAGONISTA_H */

