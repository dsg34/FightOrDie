#include "bala.h"

bala::bala(sf::Sprite spriteBala, sf::Vector2<float> s, sf::Vector2<float> m, int d, int v) {
    
    spriteBala.setOrigin(75/2,75/2);
    spriteBala.setTextureRect(sf::IntRect(0*75, 4*75, 75, 75));
    spriteBala.setPosition(s);
    sprite=sf::Sprite(spriteBala);
    danyo=d;
    velocidad=v;    
    
    setMov(m);    
    rango=60;
    
    contador=0;

}

bala::bala(const bala& orig) {
}

bala::~bala() {
}

/********************************METODOS GET Y SET*******************************************************/
sf::Sprite bala::getSprite(){
    return sprite;
}

void bala::setSprite(sf::Sprite s){
    sprite=sf::Sprite(s);
}

int bala::getContador(){
    return contador;
}

void bala::setContador(int i){
    contador=i;
}

int bala::getRango(){
    return rango;
}

void bala::setRango(int r){
    rango=r;
}
 
sf::Vector2<float> bala::getMov(){
    return mov;
}

void bala::setMov(sf::Vector2<float> v){
    mov=sf::Vector2<float>(v);
}

int bala::getVelocidad(){
    return velocidad;
}
        
void bala::setVelocidad(int i){
    velocidad=i;
}

int bala::getDanyo(){
    return danyo;
}
        
void bala::setDanyo(int i){
    danyo=i;
}

/********************************METODOS CUSTOM*******************************************************/

//Actualiza la posicion de la bala en funcion del vector mov de la propia bala, que almacena el incremento en x e y que debe realizar la bala en cada iteracion
bool bala::updatePosition(){
    bool devuelve = false;    

    if(contador<rango){        
        sprite.move(2*velocidad*mov.x, 2*velocidad*mov.y);
        contador++;
    }else{
        devuelve=true;
    }
    
    return devuelve;
}

void bala::setPositionSprite(sf::Vector2<float> v){
    sprite.setPosition(v.x, v.y);
}

