/* 
 * File:   HUD.h
 * Author: Dani
 *
 * Created on 15 de abril de 2015, 20:05
 */

#include "Protagonista.h"
#include "Arma.h"
#include "RecursoHUD.h"
#include <sstream>
#ifndef HUD_H
#define	HUD_H

class HUD {
public:
    HUD(Personaje* p, sf::Vector2<int> tam);
    HUD(const HUD& orig);
    virtual ~HUD();    
    
    sf::Texture* getTextura();
    sf::Sprite* getVida();
    sf::Sprite* getMunicion();
    sf::Font* getFuente();
    sf::Text* getPuntuacion();
    bool getBoss();
    float getOpacidadVida();
    float getOpacidadMunicion();
    float getOpacidadPuntuacion();
    float getOpacidadVidaBoss();
    
    void setTextura(sf::Texture* t);
    void setVida(sf::Sprite* v);
    void setMunicion(sf::Sprite* m);
    void setFuente(sf::Font* f);
    void setPuntuacion(int p);
    void setBoss(bool b);
    void setOpacidadVida(float f);
    void setOpacidadMunicion(float f);
    void setOpacidadPuntuacion(float f);
    void setOpacidadVidaBoss(float f);
    
    void cargarSpriteVida();
    void cargarSpriteVidaBoss(int i);
    
    void reducirVida();
    void aumentarVida();
    
    void reducirBalas();
    void aumentarBalas();
    
    void actualizarArmasHUD();
    void actualizarHUD(Protagonista* p);
    std::string intAString(int p);
    
    void anyadirArma(Arma* a);
    void eliminarArma(Arma* a);
    
    /*void anyadirRecurso(Recurso r);
    void eliminarRecurso(Recurso r);*/
    
    void cambiarOpacidad(sf::Vector2<float> v);
    
    void pintarHUD(sf::RenderWindow &window);
private:
    sf::Texture* textura;
    sf::Font* fuente;
    
    sf::Sprite* spriteVida;
    sf::Sprite* spriteVidaBoss;
    sf::Sprite* municion;
    std::vector<RecursoHUD*> armas;
    std::vector<RecursoHUD*> recursos;

    sf::Text* puntuacion;
    sf::Text* balas;
    
    sf::Vector2<int>* tamPantalla;
    
    int vida;
    int tipoPrincipal;
    bool boss;
    float opacidadVida;
    float opacidadMunicion;
    float opacidadPuntuacion;
    float opacidadVidaBoss;
};

#endif	/* HUD_H */

