#include <iostream>
#include "Granada.h"
#include "Arma.h"

Granada::Granada(sf::Vector2<float> s, sf::Vector2<float> m, int d, sf::Vector2<int> pos) {
    
    sf::Texture tex;
    if (!tex.loadFromFile("resources/sprite_general.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    sf::Sprite spriteGranada(tex);
    spriteGranada.setOrigin(75/2,75/2);
    //Cojo el sprite que me interesa por defecto del sheet
    spriteGranada.setTextureRect(sf::IntRect(1*75, 0*75, 75, 75));
    spriteGranada.setPosition(s);
    
    sprite=new sf::Sprite(spriteGranada);

    iteracionExplosion.x=2;
    iteracionExplosion.y=0;
    
    contador=0;
    rango=60;
    velocidad=8;
    danyo=d;
    
    mov=m;
    
    posicionFinal=pos;
    estado=0;
    posActual = s;
    posAnterior = s;
    haExplotadoYa = false;
    
}

Granada::Granada(const Granada& orig) {
}

Granada::~Granada() 
{
    //delete sprite;
}

/**********************************************MÉTODOS GET Y SET**********************************************************************/
int Granada::getContador(){
    return contador;
}

void Granada::setContador(int c){
    contador=c;
}

int Granada::getVelocidad(){
    return velocidad;
}

void Granada::setVelocidad(int vel){
    velocidad=vel;
}

int Granada::getRango(){
    return rango;
}

void Granada::setRango(int r){
    rango=r;
}

sf::Vector2<int> Granada::getIteracionExplosion(){
    return iteracionExplosion;
}

void Granada::setIteracionExplosion(sf::Vector2<int> v){
    iteracionExplosion=v;
}

sf::Sprite* Granada::getSprite(){
    return sprite;
}

void Granada::setSprite(sf::Sprite* s){
    sprite=s;
}

sf::Vector2<float> Granada::getMov(){
    return mov;
}

void Granada::setMov(sf::Vector2<float> m){
    mov=m;
}

int Granada::getDanyo(){
    return danyo;
}

void Granada::setDanyo(int d){
    danyo=d;
}

sf::Vector2<float> Granada::getPosAnterior(){
    return posAnterior;
}

void Granada::setPosAnterior(sf::Vector2<float> v){
    posAnterior= v;
}

sf::Vector2<float> Granada::getPosActual(){
    return posActual;
}

void Granada::setPosActual(sf::Vector2<float> v){
    posActual = v;
}

int Granada::getEstado(){
    return estado;
}

/**********************************************MÉTODOS CUSTOM**********************************************************************/
//Facilita el cambio de recorte del sprite
void Granada::setRecorteSprite(int i, int j){
    sprite->setTextureRect(sf::IntRect(i*75, j*75, 75, 75));
}
  
//Actualiza la posicion de la Granada y devuelve 0 en caso de estar en movimiento sin explotar, 1 en caso de estar explotando (debe causar daño) y 2 si ha acabado su ciclo
int Granada::updateGranada(){
    int devuelve = 0;
    //Posicion inicial de las imagenes de explosion
    double cont = 1.0;   
            
    sf::Vector2<int> pos = (sf::Vector2<int>)sprite->getPosition() ;
    posAnterior = sprite->getPosition();
    if(abs(posicionFinal.x-pos.x)<10 && abs(posicionFinal.y-pos.y)<10){ //&& posicionFinal.y=pos.y)
        contador=rango-20;
        haExplotadoYa = true;
    }
    if(contador==0)
        sprite->setScale(0.6,0.6);
    if(contador<rango-20){                  
        sprite->move(velocidad*mov.x,velocidad*mov.y); 
        sprite->rotate(10);
    }else if(contador<rango){//Cuando termino el rango de movimiento empiezo la animacion de explosion
        //Dependiendo si la explosion esta empezando o acabando, la aumentamos o reducimos
        if(contador<rango-10)
            cont=sprite->getScale().x+0.1;
        else
            cont=sprite->getScale().x-0.1;   
        
        //hasta que se acaben las filas
        if(iteracionExplosion.y<5){                
            if(iteracionExplosion.x<5){
                iteracionExplosion.x++;
            }
            else{
                iteracionExplosion.x=2;
                iteracionExplosion.y++;
            }
            //std::cout << cont << std::endl;
        }

        setRecorteSprite(iteracionExplosion.x,iteracionExplosion.y);
        sprite->setScale(cont,cont);   
        devuelve = 1;
    }else{//Cuando se acaba el movimiento y la explosion, se devuelve 2 para eliminar la Granada
        devuelve = 2;
        setRecorteSprite(1,0);
    }
    contador++;
    estado = devuelve;
    posActual = sprite->getPosition();
    return devuelve;
}

//Pinta la Granada en la ventana que recibe
void Granada::pintarGranada(sf::RenderWindow &window){
    window.draw(*sprite);
}

void Granada::mover(float x, float y){
    sprite->move(x,y);
}

bool Granada::estaExplotando(){
    if(estado== 1)
        return true;
    else
        return false;
}