/* 
 * File:   PersonajeFactory.cpp
 * Author: Dani
 * 
 * Created on 10 de abril de 2015, 15:45
 */

#include "PersonajeFactory.h"

PersonajeFactory::PersonajeFactory() {
    protagonistaCreado=false;
}

PersonajeFactory::PersonajeFactory(const PersonajeFactory& orig) {
}

PersonajeFactory::~PersonajeFactory() {
}

Protagonista* PersonajeFactory::crearProtagonista(Arma* a, sf::Vector2<float> p){
    
    if(protagonistaCreado==false){
        sf::Texture tex;
        if (!tex.loadFromFile("resources/protagonista.png"))
        {
            std::cerr << "Error cargando la imagen sprites.png";
            exit(0);
        }
        sf::Sprite sprite(tex);

        //Este es el sprite que le pasaremos a disparar, para que las balas que se creen lo hagan con dicho sprite
        sprite.setOrigin(75/2,75/2);
        sprite.setTextureRect(sf::IntRect(0*75, 0*75, 75, 75));

        sf::Sprite* aux = new sf::Sprite(sprite);
        protagonista = new Protagonista(aux, tex, a, p, 30, 5);
    }
    return protagonista;
}