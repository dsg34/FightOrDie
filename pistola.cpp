#include "pistola.h"

pistola::pistola() {
    danyo=1;    
    velocidad=5;
    maxBalas=150;
    municion=200;
    cargador = std::vector<bala*>();
}

pistola::pistola(const pistola& orig) {
}

pistola::~pistola() {
}
/***********************************METODOS GET Y SET************************************************/
int pistola::getDanyo(){
    return danyo;
}
void pistola::setDanyo(int d){
    danyo=d;
}

int pistola::getVelocidad(){
    return velocidad;
}

void pistola::setVelocidad(int v){
    velocidad=v;
}

int pistola::getMunicion(){
    return municion;
}
void pistola::setMunicion(int m){
    municion=m;
}  

std::vector<bala*> pistola::getCargador(){
    return cargador;
}
void pistola::setCargador(std::vector<bala*> v){
    cargador=v;
}        

int pistola::getMaxBalas(){
    return maxBalas;
}
void pistola::setMaxBalas(int m){
    maxBalas=m;
}  
/**************************************METODOS CUSTOM***********************************************************/

//El metodo disparar crea una nueva bala de las disparadas por la pistola a no ser que se haya alcanzado el maximo de balas simultaneas disponible
void pistola::disparar(sf::Sprite spriteBala, sf::Vector2<float> s, sf::Vector2<float> m){

    bala* auxBala;
    if(cargador.size()<maxBalas){ 
        auxBala = new bala(spriteBala, s, m, danyo, velocidad);
        cargador.push_back(auxBala);
    }

}

//Actualiza la posicion de cada bala llamando al metodo update de la propia bala
void pistola::updateBalas(){
    
    for(int i=0;i<cargador.size(); i++){
        if(cargador[i]->updatePosition()==true){//Si la actualizacion de posicion devuelve true, se elimina la bala del cargador
            cargador.erase(cargador.begin()+i);
        }
    }
}

//Pinta cada bala
void pistola::pintarBalas(sf::RenderWindow &window){
    for(int i=0; i<cargador.size(); i++){
        window.draw(cargador[i]->getSprite());
    }
}

//Elimina una bala de forma manual. Metodo necesario para cuando una bala colisione con un objeto
void pistola::eliminarBala(int i){
    if(i>=0 && i<cargador.size())
        cargador.erase(cargador.begin()+i);
}
