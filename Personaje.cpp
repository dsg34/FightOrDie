/* 
 * File:   Personaje.cpp
 * Author: Dani
 * 
 * Created on 6 de abril de 2015, 15:50
 */

#include "Personaje.h"

Personaje::Personaje(sf::Sprite* s, sf::Vector2<float> p, int mV, int ve){
    
    sprite=new sf::Sprite(*s);
    sprite->setPosition(p);
    
    posActual=p;
    posAnterior=p;
    maxVida=mV;
    velocidad=ve;    
    
    vida=maxVida;
    cont = 0;    
    direc=0;
    muriendo=false;
}

Personaje::Personaje(const Personaje& orig) {
}

Personaje::~Personaje() {
}

void Personaje::render(sf::RenderWindow &window){
    sf::Sprite aux = *sprite;
    window.draw(aux);
}

/********************************METODOS GET Y SET*******************************************************/

sf::Vector2<float> Personaje::getPosAnterior(){
    return posAnterior;
}

void Personaje::setPosAnterior(sf::Vector2<float> v){
    posAnterior= v;
}

sf::Vector2<float> Personaje::getPosActual(){
    return posActual;
}

void Personaje::setPosActual(sf::Vector2<float> v){
    posActual = v;
}

sf::Sprite* Personaje::getSprite(){
    return sprite;
}
void Personaje::setSprite(sf::Sprite* s){
    sprite = s;
}

int Personaje::getVida(){
    return vida;
}
void Personaje::setVida(int v){
    vida=v;
}

int Personaje::getMaxVida(){
    return maxVida;
}
void Personaje::setMaxVida(int mV){
    maxVida=mV;
}

int Personaje::getVelocidad(){
    return velocidad;
}
void Personaje::setVelocidad(int ve){
    velocidad=ve;
}

int Personaje::getCont(){
    return cont;
}
void Personaje::setCont(int c){
    cont=c;
}

int Personaje::getDirec(){
    return direc;
}
void Personaje::setDirec(int d){
    direc=d;
}

bool Personaje::getMuriendo(){
    return muriendo;
}
void Personaje::setMuriendo(bool m){
    muriendo=m;
}










//Contador de la posicion del sprite en la que se esta
    //Direccion del personaje
    