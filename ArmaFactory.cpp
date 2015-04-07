/* 
 * File:   ArmaFactory.cpp
 * Author: Dani
 * 
 * Created on 7 de abril de 2015, 15:36
 */

#include "ArmaFactory.h"

ArmaFactory::ArmaFactory() {
}

ArmaFactory::ArmaFactory(const ArmaFactory& orig) {
}

ArmaFactory::~ArmaFactory() {
}

Arma* ArmaFactory::crearPistola(){//Se debe controlar que, al acabarse la municion de la pistola, se proporcione al usuario mas, ya que esta es infinita
    sf::Texture tex;
    if (!tex.loadFromFile("resources/sprite_general.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    sf::Sprite spriteBala(tex);
    
    
    //Este es el sprite que le pasaremos a disparar, para que las balas que se creen lo hagan con dicho sprite
    spriteBala.setOrigin(75/2,75/2);
    spriteBala.setTextureRect(sf::IntRect(0*75, 4*75, 75, 75));
    
    sf::Sprite* aux = new sf::Sprite(spriteBala);
    
    Arma* p = new Arma(aux, 1, 2, 5, 150, 2000, 0.3, 45);
    
    return p;
}

Arma* ArmaFactory::crearMetralleta(){//Se debe controlar que, al acabarse la municion de la pistola, se proporcione al usuario mas, ya que esta es infinita
    sf::Texture tex;
    if (!tex.loadFromFile("resources/sprite_general.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    sf::Sprite spriteBala(tex);
    
    //Este es el sprite que le pasaremos a disparar, para que las balas que se creen lo hagan con dicho sprite
    spriteBala.setOrigin(75/2,75/2);
    spriteBala.setTextureRect(sf::IntRect(0*75, 4*75, 75, 75));
    
    sf::Sprite* aux = new sf::Sprite(spriteBala);
    
    Arma* m = new Arma(aux, 2, 1, 7, 150, 100, 0.1, 45);
    
    return m;
}

Arma* ArmaFactory::crearEscopeta(){//Se debe controlar que, al acabarse la municion de la pistola, se proporcione al usuario mas, ya que esta es infinita
    sf::Texture tex;
    if (!tex.loadFromFile("resources/sprite_general.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    sf::Sprite spriteBala(tex);
    
    //Este es el sprite que le pasaremos a disparar, para que las balas que se creen lo hagan con dicho sprite
    spriteBala.setOrigin(75/2,75/2);
    spriteBala.setTextureRect(sf::IntRect(0*75, 4*75, 75, 75));
    
    sf::Sprite* aux = new sf::Sprite(spriteBala);
    
    Arma* e = new Arma(aux, 3, 3, 5, 150, 50, 0.7, 20);
    
    return e;
}

Arma* ArmaFactory::crearHacha(){//Se debe controlar que, al acabarse la municion de la pistola, se proporcione al usuario mas, ya que esta es infinita
    sf::Texture tex;
    if (!tex.loadFromFile("resources/sprite_general.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    sf::Sprite spriteBala(tex);
    
    //Este es el sprite que le pasaremos a disparar, para que las balas que se creen lo hagan con dicho sprite
    spriteBala.setOrigin(75/2,75/2);
    spriteBala.setTextureRect(sf::IntRect(0*75, 4*75, 75, 75));
    
    sf::Sprite* aux = new sf::Sprite(spriteBala);
    
    Arma* h = new Arma(aux, 4, 4, 7, 150, 2000, 0.1, 3);
   
    return h;
}