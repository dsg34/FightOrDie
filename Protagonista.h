/* 
 * File:   Protagonista.h
 * Author: Dani
 *
 * Created on 6 de abril de 2015, 18:31
 */

#ifndef PROTAGONISTA_H
#define	PROTAGONISTA_H

#include "Arma.h"
#include "Recurso.h"
#include "Personaje.h"
#include "Zombie.h"
#include "MapLoader.h"

class Protagonista: public Personaje {
public:
    Protagonista(sf::Sprite* s, sf::Texture* t, sf::Vector2<float> p, int mV, int ve);
    Protagonista(const Protagonista& orig2);
    virtual ~Protagonista();
    
    Arma* getArma();
    std::vector<Arma*> getArmas();
    
    void setArma(Arma* a);
    void siguienteArma();
    void anteriorArma();
    //void update(char direccion);
    void recibirRecurso(Recurso* r);
    void disparar(sf::Vector2<int> posicionCursor);
    void dispararSecundaria(sf::Vector2<int> posicionCursor);
    void movimientoCerebro(std::vector<Zombie*> enemigos);
    int Colision(std::vector<Zombie*> zombies, char direccion);
    void colisionConRecursos(std::vector<Recurso*> &recursos);
    void actualizaDireccion();
    void actualizaPerso(int teclaX, int teclaY, std::vector<Zombie*> enemigos, MapLoader* m);
    void update(sf::Vector2<int> pos, std::vector<Zombie*> enemigos, MapLoader* m,std::vector<Recurso*> recursos);
    void setPosMira(sf::Vector2<int>);
    void pintarProtagonista(sf::RenderWindow &w);
    std::vector<Recurso*> getInventario();
    void setInventario(std::vector<Recurso*> i);
    void recibirDanyo(float cant);
    //sf::RectangleShape* getRectangle();
private:

    Arma* arma;
    std::vector<Arma*> armas;
    sf::Vector2<int> posmira;
    sf::Clock relojCambioArma;
    int municionSecundaria;
    //sf::RectangleShape* rectangle;
    
    std::vector<Recurso*> inventario;
    
};

#endif	/* PROTAGONISTA_H */
