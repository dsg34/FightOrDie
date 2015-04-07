/* 
 * File:   Arma.h
 * Author: Dani
 *
 * Created on 7 de abril de 2015, 13:08
 */

#include "Bala.h"

#ifndef ARMA_H
#define	ARMA_H

class Arma {
public:
    Arma(int t, int d, int v, int mB, int m, float c);
    Arma(const Arma& orig);
    virtual ~Arma();
    
    std::vector<Bala*> getCargador();
    int getDanyo();
    int getVelocidad();
    int getMunicion();
    int getMaxBalas();
    
    void setCargador(std::vector<Bala*> v);        
    void setDanyo(int d);
    void setVelocidad(int v);
    void setMunicion(int m);
    void setMaxBalas(int b);
    
    bool disparar(sf::Sprite spriteBala, sf::Vector2<float> s, sf::Vector2<float> m);
    void updateBalas();
    void pintarBalas(sf::RenderWindow &window);
    void eliminarBala(int i);
protected:
    std::vector<Bala*> cargador;
    int danyo;
    int velocidad;
    int maxBalas;
    int municion;
    float cadencia;
    int tipo;
    sf::Clock reloj;
    sf::Time tiempo;
};

#endif	/* ARMA_H */

