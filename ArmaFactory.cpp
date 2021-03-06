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
    spriteBala.scale(0.3,0.3);
    sf::Sprite* aux = new sf::Sprite(spriteBala);
    
    Arma* p = new Arma(aux, new sf::Texture(tex), 1, 2, 20, 150, 2000, 0.3, 25);
    
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
    spriteBala.scale(0.3,0.3);
    
    sf::Sprite* aux = new sf::Sprite(spriteBala);
    
    Arma* m = new Arma(aux, new sf::Texture(tex), 2, 1, 25, 150, 100, 0.1, 30);
    
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
    spriteBala.scale(0.5,0.5);
    sf::Sprite* aux = new sf::Sprite(spriteBala);
    
    Arma* e = new Arma(aux, new sf::Texture(tex), 3, 3, 15, 150, 50, 0.7, 10);
    
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
    spriteBala.setTextureRect(sf::IntRect(1*75, 3*75, 75, 75));
    
    sf::Sprite* aux = new sf::Sprite(spriteBala);
    
    Arma* h = new Arma(aux, new sf::Texture(tex), 4, 4, 7, 1, 2000, 0.1, 2);
   
    return h;
}