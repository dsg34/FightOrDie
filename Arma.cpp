/* 
 * File:   Arma.cpp
 * Author: Dani
 * 
 * Created on 7 de abril de 2015, 13:08
 */

#include "Arma.h"

Arma::Arma(int t, int d, int v, int mB, int m, float c) {
    tipo=t;
    danyo=d;    
    velocidad=v;
    maxBalas=mB;
    municion=m;
    cadencia=c;
    
    cargador = std::vector<Bala*>();   
    reloj.restart();
    tiempo=reloj.getElapsedTime();
}

Arma::Arma(const Arma& orig) {
    
}

Arma::~Arma() {
}
/***********************************METODOS GET Y SET************************************************/
int Arma::getDanyo(){
    return danyo;
    
}
void Arma::setDanyo(int d){
    danyo=d;
}

int Arma::getVelocidad(){
    return velocidad;
}

void Arma::setVelocidad(int v){
    velocidad=v;
}

int Arma::getMunicion(){
    return municion;
}
void Arma::setMunicion(int m){
    municion=m;
}  

std::vector<Bala*> Arma::getCargador(){
    return cargador;
}
void Arma::setCargador(std::vector<Bala*> v){
    cargador=v;
}        

int Arma::getMaxBalas(){
    return maxBalas;
}
void Arma::setMaxBalas(int m){
    maxBalas=m;
}  
/**************************************METODOS CUSTOM***********************************************************/

//El metodo disparar crea una nueva Bala de las disparadas por la Arma a no ser que se haya alcanzado el maximo de Balas simultaneas disponible
bool Arma::disparar(sf::Sprite spriteBala, sf::Vector2<float> s, sf::Vector2<float> m){
    bool agotadas=false;
    
    Bala* auxBala;
    tiempo=reloj.getElapsedTime();
    std::cout<<tiempo.asSeconds()<<std::endl;
    if(municion>0){
        if(tiempo.asSeconds()>cadencia){//Control de cadencia
            if(cargador.size()<maxBalas){ //Controlamos que no se exceda un numero maximo de balas para que el programa no tenga problemas
                auxBala = new Bala(spriteBala, s, m, danyo, velocidad);//Control de velocidad y danyo
                cargador.push_back(auxBala);
                municion--;
                reloj.restart();
            }
        }
    }
    else{
        agotadas=true;
    }
    
    return agotadas;
}

//Actualiza la posicion de cada Bala llamando al metodo update de la propia Bala
void Arma::updateBalas(){
    
    for(int i=0;i<cargador.size(); i++){
        if(cargador[i]->updatePosition()==true){//Si la actualizacion de posicion devuelve true, se elimina la Bala del cargador
            cargador.erase(cargador.begin()+i);
        }
    }
}

//Pinta cada Bala
void Arma::pintarBalas(sf::RenderWindow &window){
    for(int i=0; i<cargador.size(); i++){
        window.draw(cargador[i]->getSprite());
    }
}

//Elimina una Bala de forma manual. Metodo necesario para cuando una Bala colisione con un objeto
void Arma::eliminarBala(int i){
    if(i>=0 && i<cargador.size())
        cargador.erase(cargador.begin()+i);
}
