/* 
 * File:   Proyectil.cpp
 * Author: Dani
 * 
 * Created on 7 de abril de 2015, 16:46
 */


#include "Proyectil.h"

Proyectil::Proyectil(sf::Sprite* spriteProyectil, sf::Texture* t, sf::Vector2<float> s, sf::Vector2<float> m, int d, int v, int r) {
    
    spriteProyectil->setPosition(s);
    sprite= new sf::Sprite(*spriteProyectil);
    tex=t;
    
    sprite->setTexture(*t);
    danyo=d;
    velocidad=v;    
    
    setMov(m);    
    rango=r;
    
    contador=0;

}

Proyectil::Proyectil(const Proyectil& orig) {
}

Proyectil::~Proyectil() {
}

/********************************METODOS GET Y SET*******************************************************/
sf::Sprite* Proyectil::getSprite(){
    return sprite;
}

void Proyectil::setSprite(sf::Sprite s){
    sprite= new sf::Sprite(s);
}

int Proyectil::getContador(){
    return contador;
}

void Proyectil::setContador(int i){
    contador=i;
}

int Proyectil::getRango(){
    return rango;
}

void Proyectil::setRango(int r){
    rango=r;
}
 
sf::Vector2<float> Proyectil::getMov(){
    return mov;
}

void Proyectil::setMov(sf::Vector2<float> v){
    mov=sf::Vector2<float>(v);
}

int Proyectil::getVelocidad(){
    return velocidad;
}
        
void Proyectil::setVelocidad(int i){
    velocidad=i;
}

int Proyectil::getDanyo(){
    return danyo;
}
        
void Proyectil::setDanyo(int i){
    danyo=i;
}

/********************************METODOS CUSTOM*******************************************************/

//Actualiza la posicion de la Proyectil en funcion del vector mov de la propia Proyectil, que almacena el incremento en x e y que debe realizar la Proyectil en cada iteracion
bool Proyectil::updatePosition(){
    bool devuelve = false;    

    if(contador<rango){        
        sprite->move(2*velocidad*mov.x, 2*velocidad*mov.y);
        contador++;
    }else{
        devuelve=true;
    }
    
    return devuelve;
}

void Proyectil::setPositionSprite(sf::Vector2<float> v){
    sprite->setPosition(v.x, v.y);
}