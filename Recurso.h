/*
int bloqueante;
1 bloquea, 0 no
int danyo;
1 causa daño a enemigos, 0 no
int inventario;
1 se guarda en el inventario, 0 no
int recogida;
1 se recoge pulsando una tecla, 0 al pasar por encima
 */
#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef RECURSO_H
#define	RECURSO_H

class Recurso {
public:
    Recurso(sf::Sprite* s, sf::Texture* te, int bloq, int dan, int inv, int rec, int res, int tip);
    Recurso(const Recurso& orig);
    virtual ~Recurso();
    
    
    int getBloqueante();
    int getDanyo();
    int getInventario();
    int getRecogida();
    int getResistencia();
    int getTipo();
    int getExiste();
    sf::Vector2<float> getVectorActual();
    sf::FloatRect* getBoundingBox();
    sf::Sprite* getSprite();
    bool getEstaEnInventario();
    
    void setBloqueante(int bloq);
    void setResistencia(int res);
    void setDanyo(int dan);
    void setInventario(int inv);
    void setRecogida(int rec);
    void setTipo(int tip);
    void setSpriteRecurso(sf::Sprite s);
    void setExiste(int e);
    void pintarRecursos(sf::RenderWindow &window);
    void setVectorActual(sf::Vector2<float> v);
    void actualizarRecurso();
    void setEstaEnInventario(bool b);
    
    
protected:
    sf::Vector2<float> vectorActual;
    int bloqueante;
    int danyo;
    int inventario;
    int recogida;
    int resistencia;
    int tipo;
    int existe;
    bool estaEnInventario;
    sf::Clock reloj;
    sf::Time tiempo;
    sf::Sprite* spriteRecurso;
    sf::Texture* tex;       
    sf::FloatRect* boundingBox;
};

#endif	/* RECURSO_H */