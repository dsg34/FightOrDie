/* 
 * File:   Arma.h
 * Author: Dani
 *
 * Created on 7 de abril de 2015, 13:08
 */

#include "Proyectil.h"
#include "Granada.h"
/**COMEME LOS HUEVOS***/
#ifndef ARMA_H
#define	ARMA_H

class Arma {
public:
    Arma(sf::Sprite* s, sf::Texture* te, int t, int d, int v, int mB, int m, float c, int r);
    Arma(const Arma& orig);
    virtual ~Arma();
    
    std::vector<Proyectil*> getCargador();
    std::vector<Granada*> getSecundaria();
    int getDanyo();
    int getDanyoSecundaria();
    int getVelocidad();
    int getMunicion();
    int getMaxProyectiles();
    int getTipo();
    
    void setCargador(std::vector<Proyectil*> v); 
    void setSecundaria(std::vector<Granada*> g);
    void setDanyo(int d);
    void setVelocidad(int v);
    void setMunicion(int m);
    void setMaxProyectiles(int b);
    void setMunicionSecundaria(int i);
    void setDanyoSecundaria(int ds);
    void setTipo(int i);
    
    void aumentarDanyo();
    void aumentarMunicion();
    
    sf::Vector2<float> vectorDisparo(sf::Vector2<float> puntoPersonaje, sf::Vector2<int> puntoCursor);
    bool disparar(sf::Vector2<float> s, sf::Vector2<int> pos);
    void dispararSecundaria(sf::Vector2<float> s, sf::Vector2<int> pos);
    void updateProyectiles();
    void pintarProyectiles(sf::RenderWindow &window);
    void eliminarProyectil(int i);    
protected:
    std::vector<Proyectil*> cargador;
    std::vector<Granada*> secundaria;
    int danyo;
    int danyoSecundaria;
    int velocidad;
    int maxProyectiles;
    int municion;
    int municionSecundaria;
    int rango;
    float cadencia;
    int tipo;
    sf::Clock reloj;
    sf::Time tiempo;
    sf::Sprite* spriteProyectil;
    sf::Texture* tex;       
};

#endif	/* ARMA_H */

