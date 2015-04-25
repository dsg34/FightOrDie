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
#include "Zombie.h"

class Protagonista: public Personaje {
public:
    Protagonista(sf::Sprite* s, sf::Texture* t, sf::Vector2<float> p, int mV, int ve, Arma* a);
    Protagonista(const Protagonista& orig2);
    virtual ~Protagonista();
    
    Arma* getArma();
    //std::Vector<Recurso*> getInventario();
    
    void setArma(Arma* a);
    //void update(char direccion);
    void disparar(sf::Vector2<int> posicionCursor);
    void dispararSecundaria(sf::Vector2<int> posicionCursor);
    void movimientoCerebro(std::vector<Zombie*> enemigos);
    int Colision(std::vector<Zombie*> zombies, char direccion);
    void actualizaDireccion();
    void actualizaPerso(int teclaX, int teclaY, std::vector<Zombie*> enemigos);
    void update(sf::Vector2<int> pos, std::vector<Zombie*> enemigos);
    //void setInventario(std::Vector<Recurso*> i);
    //sf::RectangleShape* getRectangle();
private:

    Arma* arma;
    sf::Vector2<int> posmira;
    //sf::RectangleShape* rectangle;
    
    //std::Vector<Recurso*> inventario;
    
};

#endif	/* PROTAGONISTA_H */

