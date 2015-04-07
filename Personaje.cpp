/* 
 * File:   Personaje.cpp
 * Author: Dani
 * 
 * Created on 6 de abril de 2015, 15:50
 */

#include "Personaje.h"

Personaje::Personaje() {
}

Personaje::Personaje(const Personaje& orig) {
}

Personaje::~Personaje() {
}

void Personaje::render(sf::RenderWindow &window){
    sf::Sprite aux = *sprite;
    window.draw(aux);
}