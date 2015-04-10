/* 
 * File:   Protagonista.cpp
 * Author: Dani
 * 
 * Created on 6 de abril de 2015, 18:31
 */

#include "Protagonista.h"

Protagonista::Protagonista(sf::Sprite* s, Arma* a, sf::Vector2<float> p, int mV, int ve) :Personaje(s,p,mV,ve) {

    //this->Personaje(sf::Sprite* s, p, mV, ve);
    sprite=s;
    arma=a;
    
}

Protagonista::Protagonista(const Protagonista& orig) : Personaje(orig) {
}

Protagonista::~Protagonista() {
}


Arma* Protagonista::getArma(){
    return arma;
}
void Protagonista::setArma(Arma a){
    arma=a;
}

/*std::Vector<Recurso*> Protagonista::getInventario(){
    return inventario;
    
1}    
void Protagonista::setInventario(std::Vector<Recurso*> i){
    inventario=i;
}
void Protagonista::anyadirAlInventario(Recurso* r){
    inventario.push_back(r);
}*
/**************************************CODIGO MANU********************************************************/
/*
bool Protagonista::actualizaMuerte(){
    bool muerte=true;
    sprite.setTextureRect(sf::IntRect(325+direc*125,cont*74,125,74));
    if(cont==5){
        cont=0;
        muerte=false;

        sprite.setOrigin(53/2,80/2);
        sprite.setTextureRect(sf::IntRect(0,direc*80,53,80));
        sprite.setPosition(256,256);
    }
    cont++;
    return muerte;
}
void zombie::muere(){
    sprite.setOrigin(125/2,84/2);
    sprite.setTextureRect(sf::IntRect(325+direc*125,0*74,125,74));
    cont=1;
}

void zombie::actualizaSprite(int tecla){
    if(tecla==1){
        if(direc==0){
            cont++;
            sprite.setTextureRect(sf::IntRect(cont*53,0,53,80));
            if(cont==5)
                cont=0;
        }else{
            cont=0;
            direc=0;
            sprite.setTextureRect(sf::IntRect(0,0,53,80));
        }
        sprite.move(-velocidad,0);
    }else if(tecla==2){
        if(direc==3){
            cont++;
            sprite.setTextureRect(sf::IntRect(cont*53,240,53,80));
            if(cont==5)
                cont=0;
        }else{
            cont=0;
            direc=3;
            sprite.setTextureRect(sf::IntRect(cont*53,240,53,80));
        }
        sprite.move(velocidad,0);
    }else if(tecla==3){
        if(direc==1){
            cont++;
            sprite.setTextureRect(sf::IntRect(cont*53,80,53,80));
            if(cont==5)
                cont=0;
        }else{
            cont=0;
            direc=1;
            sprite.setTextureRect(sf::IntRect(cont*53,80,53,80));
        }
        sprite.move(0,velocidad);
    }else if(tecla==4){
        if(direc==2){
            cont++;
            sprite.setTextureRect(sf::IntRect(cont*53,162,53,79));
            if(cont==5)
                cont=0;
        }else{
            cont=0;
            direc=2;
            sprite.setTextureRect(sf::IntRect(cont*53,162,53,79));
        }
        sprite.move(0,-velocidad);
    }
}
sf::Sprite zombie::getSprite(){
    return sprite;
}*/