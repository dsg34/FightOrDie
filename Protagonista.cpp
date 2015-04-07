/* 
 * File:   Protagonista.cpp
 * Author: Dani
 * 
 * Created on 6 de abril de 2015, 18:31
 */

#include "Protagonista.h"

Protagonista::Protagonista(sf::Sprite* p, Arma* a) {
    prueba=0;
    sprite=p;
    arma=a;
    cont=0;
    velocidad=5;
    direc=0;
    
    vida=20;
    maxVida=20;

    direc=0;//Direccion del personaje
    muriendo=false;//Booleano para determinar si el personaje esta en animacion de muerte
    
}

Protagonista::Protagonista(const Protagonista& orig) {
}

Protagonista::~Protagonista() {
}


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