/* 
 * File:   PersonajeFactory.cpp
 * Author: Dani
 * 
 * Created on 10 de abril de 2015, 15:45
 */

#include "PersonajeFactory.h"

PersonajeFactory::PersonajeFactory() {
    protagonistaCreado=false;
}

PersonajeFactory::PersonajeFactory(const PersonajeFactory& orig) {
}

PersonajeFactory::~PersonajeFactory() {
}

Protagonista* PersonajeFactory::crearProtagonista(sf::Vector2<float> p){
    
    if(protagonistaCreado==false){
        sf::Texture texAux;
        if (!texAux.loadFromFile("resources/protagonista.png"))
        {
            std::cerr << "Error cargando la imagen sprites.png";
            exit(0);
        }
        
        sf::Texture* tex = new sf::Texture(texAux);
        sf::Sprite sprite(*tex);
        
        //Este es el sprite que le pasaremos a disparar, para que las balas que se creen lo hagan con dicho sprite
        sprite.setOrigin(75/2,75/2);
        sprite.setTextureRect(sf::IntRect(0*75, 0*75, 75, 75));

        sf::Sprite* aux = new sf::Sprite(sprite);
        protagonista = new Protagonista(aux, tex, p, 20, 5);
    }
    return protagonista;
}
Zombie* PersonajeFactory::crearZombie(int tipoZombie, sf::Vector2<float> p){    
    if(tipoZombie == 1){
        //normal
        zombie = crearZombieNormal(p);
    }else if(tipoZombie == 2){
        //rapido
    }else if(tipoZombie == 3){
        //gordo
    }
    return zombie;
}
Zombie* PersonajeFactory::crearZombieNormal(sf::Vector2<float> p){
    sf::Texture texAux;
    if(!texAux.loadFromFile("resources/zombie.png")){
        std::cerr <<"Error cargando la imagen zombie.png";
        exit(0);
    }
    
    sf::Texture* tex = new sf::Texture(texAux);
    sf::Sprite sprite(texAux);
    
    sprite.setOrigin(75/2,75/2);
    sprite.setTextureRect(sf::IntRect(0*75,0*75,75,75));
    
    sf::Sprite* aux = new sf::Sprite(sprite);
    //Zombie(sprite, textura, posicion, maxVida, velocidad)
    zombie = new Zombie(aux, tex, p, 20, 1);
    
    return zombie;
}
