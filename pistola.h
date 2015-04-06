#include <vector>
#include "bala.h"
#ifndef PISTOLA_H
#define	PISTOLA_H

class pistola {
public:
    pistola();
    pistola(const pistola& orig);
    virtual ~pistola();
    
    std::vector<bala*> getCargador();
    int getDanyo();
    int getVelocidad();
    int getMunicion();
    int getMaxBalas();
    
    void setCargador(std::vector<bala*> v);        
    void setDanyo(int d);
    void setVelocidad(int v);
    void setMunicion(int m);
    void setMaxBalas(int b);
    
    void disparar(sf::Sprite spriteBala, sf::Vector2<float> s, sf::Vector2<float> m);
    void updateBalas();
    void pintarBalas(sf::RenderWindow &window);
    void eliminarBala(int i);
protected:
    std::vector<bala*> cargador;
    int danyo;
    int velocidad;
    int maxBalas;
    int municion;
};

#endif	/* PISTOLA_H */

