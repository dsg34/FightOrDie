#include "Personaje.h"

Personaje::Personaje(sf::Sprite* s, sf::Texture* t, sf::Vector2<float> p, int mV, float ve){
    
    tex=t;
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

Personaje::~Personaje() 
{
    //delete sprite;
    //delete tex;
    delete boundingBox;
    
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

sf::FloatRect* Personaje::getBoundingBox(){
       return boundingBox;
}
sf::Sprite* Personaje::getSprite(){
    return sprite;
}
void Personaje::setSprite(sf::Sprite* s){
    sprite = s;
}

sf::Texture* Personaje::getTexture(){
    return tex;
}

void Personaje::setTexture(sf::Texture* t){
    tex=t;
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

float Personaje::getVelocidad(){
    return velocidad;
}
void Personaje::setVelocidad(float ve){
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
bool Personaje::Existe(){
    if(vida<=0)
        return false;
    else
        return true;
}

void Personaje::mover(float x, float y){
    sprite->move(x,y);
}








//Contador de la posicion del sprite en la que se esta
    //Direccion del personaje
