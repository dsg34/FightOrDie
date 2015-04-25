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
    danyoSecundaria=0;
    velocidad=v;
    maxProyectiles=mB;
    municion=m;
    municionSecundaria=0;
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

int Arma::getDanyoSecundaria(){
    return danyoSecundaria;
    
}
void Arma::setDanyoSecundaria(int ds){
    danyoSecundaria=ds;
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

std::vector<Granada*> Arma::getSecundaria(){
    return secundaria;
}
void Arma::setSecundaria(std::vector<Granada*> g){
    secundaria=g;
}   

int Arma::getMaxProyectiles(){
    return maxProyectiles;
}
void Arma::setMaxProyectiles(int m){
    maxProyectiles=m;
}

void Arma::aumentarDanyo(){
    danyo++;
}

void Arma::aumentarMunicion(){
    municion++;
}

void Arma::setMunicionSecundaria(int i){
    municionSecundaria=i;
}

int Arma::getTipo(){
    return tipo;
}
void Arma::setTipo(int i){
    tipo=i;
}

/**************************************METODOS CUSTOM***********************************************************/

sf::Vector2<float> Arma::vectorDisparo(sf::Vector2<float> puntoPersonaje, sf::Vector2<int> puntoCursor){
    static const float pi = 3.141592654f;        
    //std::cout<<puntoCursor.x<<" - "<< puntoCursor.y << std::endl;
    sf::Vector2<float> devuelve;
    
    float vecX = (float) puntoCursor.x - puntoPersonaje.x;
    float vecY = (float) puntoCursor.y - puntoPersonaje.y;
    
    float angulo = atan(vecY/vecX);
    
    devuelve.x = cos(angulo);
    devuelve.y = sin(angulo);

    if(vecX<0){
        devuelve.x = -devuelve.x;
        devuelve.y = -devuelve.y;
    } 
    return devuelve;
}

//El metodo disparar crea una nueva Proyectil de las disparadas por la Arma a no ser que se haya alcanzado el maximo de Proyectiles simultaneas disponible
bool Arma::disparar(sf::Vector2<int> s, sf::Vector2<int> pos){
    bool agotadas=false;    
    sf::Vector2<int> aux;
    sf::Vector2<float> m = vectorDisparo(s, pos);

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
                    //Bala central
                    auxProyectil = new Proyectil(spriteProyectil, tex, s, m, danyo, velocidad, rango);//Control de velocidad y danyo
                    cargador.push_back(auxProyectil);
                                
                    //Bala lateral 1                    
                    aux.x = pos.x + fabs(m.y*40);
                    aux.y = pos.y + fabs(m.x*40);
                    
                    //Evitamos que se junten las balas en las diagonales
                    if(fabs(fabs(m.x)-fabs(m.y))<0.2){
                        aux.x=aux.x+80;
                        aux.y=aux.y-80;
                    }                   
                    
                    sf::Vector2<float> m1 = vectorDisparo(s, aux);                                        
                    
                    auxProyectil = new Proyectil(spriteProyectil, tex, s, m1, danyo, velocidad, rango);//Control de velocidad y danyo
                    cargador.push_back(auxProyectil);
                    
                    //Bala lateral 2
                    aux.x = pos.x - fabs(m.y*40);
                    aux.y = pos.y - fabs(m.x*40);
                    
                    //Evitamos que se junten las balas en las diagonales
                    if(fabs(fabs(m.x)-fabs(m.y))<0.2){
                        aux.x=aux.x+80;
                        aux.y=aux.y-80;
                    }                    
                    
                    m1 = vectorDisparo(s, aux);
                    auxProyectil = new Proyectil(spriteProyectil, tex, s, m1, danyo, velocidad, rango);//Control de velocidad y danyo
                    cargador.push_back(auxProyectil);
                    
                    reloj.restart();
                    municion--;
                    /**m.x=m.x-0.1;
                    m.y=m.y+0.1;**/
                }
            }            
        }
    }
    else{
        agotadas=true;
    }
    
    return agotadas;
}
//Lanzara las granadas
void Arma::dispararSecundaria(sf::Vector2<int> s, sf::Vector2<int> pos){
    Granada* auxGranada;
    sf::Vector2<float> m = vectorDisparo(s, pos);
    tiempo=reloj.getElapsedTime();
    if(municionSecundaria>0){
        if(secundaria.size()<maxProyectiles){ //Controlamos que no se exceda un numero maximo de balas para que el programa no tenga problemas
            auxGranada = new Granada(s, m, danyoSecundaria, pos);//Control de velocidad y danyo
            secundaria.push_back(auxGranada);
            municionSecundaria--;        
        }
    }
}

//Actualiza la posicion de cada Proyectil llamando al metodo update de la propia Proyectil
void Arma::updateProyectiles(){
    
    for(int i=0;i<cargador.size(); i++){
        if(cargador[i]->updatePosition()==true){//Si la actualizacion de posicion devuelve true, se elimina la Proyectil del cargador
            cargador.erase(cargador.begin()+i);
        }
    }
    for(int i=0;i<secundaria.size(); i++){
        if(secundaria[i]->updateGranada()==2){//Si la actualizacion de posicion devuelve true, se elimina la Proyectil del cargador
            secundaria.erase(secundaria.begin()+i);
        }
    }
   
}

//Pinta cada Proyectil
void Arma::pintarProyectiles(sf::RenderWindow &window){
    for(int i=0; i<cargador.size(); i++){
        window.draw(*cargador[i]->getSprite());
    }
    for(int j=0; j<secundaria.size();j++){
        sf::Sprite aux = *secundaria[j]->getSprite();
        aux.setTexture(*tex);
        window.draw(aux);
    }
}

//Elimina una Proyectil de forma manual. Metodo necesario para cuando una Proyectil colisione con un objeto
void Arma::eliminarProyectil(int i){
    if(i>=0 && i<cargador.size())
        cargador.erase(cargador.begin()+i);
}
