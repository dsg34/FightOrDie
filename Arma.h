/* 
 * File:   Arma.h
 * Author: Dani
 *
 * Created on 7 de abril de 2015, 13:08
 */

#include "Proyectil.h"

#ifndef ARMA_H
#define	ARMA_H

class Arma {
public:
    Arma(int t, int d, int v, int mB, int m, float c);
    Arma(const Arma& orig);
    virtual ~Arma();
    
    std::vector<Proyectil*> getCargador();
    int getDanyo();
    int getVelocidad();
    int getMunicion();
    int getMaxProyectiles();
    
    void setCargador(std::vector<Proyectil*> v);        
    void setDanyo(int d);
    void setVelocidad(int v);
    void setMunicion(int m);
    void setMaxProyectiles(int b);
    
    bool disparar(sf::Sprite spriteProyectil, sf::Vector2<float> s, sf::Vector2<float> m);
    void updateProyectiles();
    void pintarProyectiles(sf::RenderWindow &window);
    void eliminarProyectil(int i);
protected:
    std::vector<Proyectil*> cargador;
    int danyo;
    int velocidad;
    int maxProyectiles;
    int municion;
    float cadencia;
    int tipo;
    sf::Clock reloj;
    sf::Time tiempo;
};

#endif	/* ARMA_H */

