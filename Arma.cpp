/* 
 * File:   Arma.cpp
 * Author: Dani
 * 
 * Created on 7 de abril de 2015, 13:08
 */

#include "Arma.h"

Arma::Arma(sf::Sprite* s, sf::Texture* te, int t, int d, int v, int mB, int m, float c, int r) {
    spriteProyectil = new sf::Sprite(*s);
    tex = new sf::Texture(*te);
    tipo=t;
    danyo=d;    
    velocidad=v;
    maxProyectiles=mB;
    municion=m;
    cadencia=c;
    rango = r;
    
    cargador = std::vector<Proyectil*>();   
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

std::vector<Proyectil*> Arma::getCargador(){
    return cargador;
}
void Arma::setCargador(std::vector<Proyectil*> v){
    cargador=v;
}        

int Arma::getMaxProyectiles(){
    return maxProyectiles;
}
void Arma::setMaxProyectiles(int m){
    maxProyectiles=m;
}  
/**************************************METODOS CUSTOM***********************************************************/

//El metodo disparar crea una nueva Proyectil de las disparadas por la Arma a no ser que se haya alcanzado el maximo de Proyectiles simultaneas disponible
bool Arma::disparar(sf::Vector2<float> s, sf::Vector2<float> m){
    bool agotadas=false;
    
    Proyectil* auxProyectil;
    tiempo=reloj.getElapsedTime();
    if(municion>0){
        if(tiempo.asSeconds()>cadencia){//Control de cadencia
            if(cargador.size()<maxProyectiles){ //Controlamos que no se exceda un numero maximo de balas para que el programa no tenga problemas
                if(tipo!=3){
                    auxProyectil = new Proyectil(spriteProyectil, tex, s, m, danyo, velocidad, rango);//Control de velocidad y danyo
                    cargador.push_back(auxProyectil);
                    municion--;
                    reloj.restart();
                }
                else{//Comportamiento de la escopeta
                    auxProyectil = new Proyectil(spriteProyectil, tex, s, m, danyo, velocidad, rango);//Control de velocidad y danyo
                    cargador.push_back(auxProyectil);
                    municion--;
                    reloj.restart();
                }
            }
            
            m.x=m.x-0.1;
                m.y=m.y+0.1;
        }
    }
    else{
        agotadas=true;
    }
    
    return agotadas;
}

//Actualiza la posicion de cada Proyectil llamando al metodo update de la propia Proyectil
void Arma::updateProyectiles(){
    
    for(int i=0;i<cargador.size(); i++){
        if(cargador[i]->updatePosition()==true){//Si la actualizacion de posicion devuelve true, se elimina la Proyectil del cargador
            cargador.erase(cargador.begin()+i);
        }
    }
   
}

//Pinta cada Proyectil
void Arma::pintarProyectiles(sf::RenderWindow &window){
    for(int i=0; i<cargador.size(); i++){

        window.draw(*cargador[i]->getSprite());
    }
}

//Elimina una Proyectil de forma manual. Metodo necesario para cuando una Proyectil colisione con un objeto
void Arma::eliminarProyectil(int i){
    if(i>=0 && i<cargador.size())
        cargador.erase(cargador.begin()+i);
}
