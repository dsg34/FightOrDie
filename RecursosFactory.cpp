/* 
 * File:   RecursosFactory.cpp
 * Author: Marc
 * 
 * Created on 7 de abril de 2015, 15:36
 */

/*
int bloqueante;

1 bloquea, 0 no

int danyo;

1 causa daño a enemigos, 0 no

int inventario;

1 se guarda en el inventario, 0 no

int recogida;

1 se recoge pulsando una tecla, 0 al pasar por encima
 
 * int resistencia
 * 
 * resistencia del objeto


 */

#include "RecursosFactory.h"

RecursosFactory::RecursosFactory() {
}

RecursosFactory::RecursosFactory(const RecursosFactory& orig) {
}

RecursosFactory::~RecursosFactory() 
{
}
// Escopeta=2; Botiquin=3; Metralleta=4; Barril=5; Madera=6; Granada=7; Valla=8;
Recurso* RecursosFactory::crearBotiquin()
{
    sf::Texture tex;
    if (!tex.loadFromFile("resources/hud.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    sf::Sprite spriteMadera(tex);
    
    
    sf::Sprite* aux = new sf::Sprite(spriteMadera);
    
    aux->setOrigin(75/2,75/2);
    aux->setTextureRect(sf::IntRect(9*75, 3*75, 75, 75)); 
    aux->setScale(0.5,0.5);
    
    Recurso* p = new Recurso(aux, new sf::Texture(tex), 0, 0, 0, 0, 0, 3);
    
    return p;
}

Recurso* RecursosFactory::crearMadera()
{
    sf::Texture tex;
    if (!tex.loadFromFile("resources/hud.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    sf::Sprite spriteMadera(tex);
    
    
    sf::Sprite* aux = new sf::Sprite(spriteMadera);
    
    aux->setOrigin(75/2,75/2);
    aux->setTextureRect(sf::IntRect(11*75, 0, 75, 75)); 
    aux->setScale(0.5,0.5);
    
    Recurso* p = new Recurso(aux, new sf::Texture(tex), 0, 0, 1, 0, 0, 6);
    
    return p;
}

Recurso* RecursosFactory::crearValla(int res)
{
    sf::Texture tex;
    if (!tex.loadFromFile("resources/hud.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    sf::Sprite spriteValla(tex);
    
    
    sf::Sprite* aux = new sf::Sprite(spriteValla);
    
    aux->setOrigin(75/2,75/2);
    aux->setTextureRect(sf::IntRect(10*75, 0, 75, 75)); 
    aux->setScale(0.7,0.7);
    
    Recurso* p = new Recurso(aux, new sf::Texture(tex), 1, 0, 1, 1, res, 8);
    
    return p;
}

Recurso* RecursosFactory::crearBarril()
{
    sf::Texture tex;
    if (!tex.loadFromFile("resources/hud.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    sf::Sprite sprite(tex);
    
    
    sf::Sprite* aux = new sf::Sprite(sprite);
    
    aux->setOrigin(75/2,75/2);
    aux->setTextureRect(sf::IntRect(9*75, 0, 75, 75)); 
    aux->setScale(0.5,0.5);
    
    Recurso* p = new Recurso(aux, new sf::Texture(tex), 1, 0, 1, 1, 0, 5);
    
    return p;
}

Recurso* RecursosFactory::crearMunicionEscopeta()
{
    sf::Texture tex;
    if (!tex.loadFromFile("resources/hud.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    sf::Sprite sprite(tex);
    
    
    sf::Sprite* aux = new sf::Sprite(sprite);
    
    aux->setOrigin(75/2,75/2);
    aux->setTextureRect(sf::IntRect(11*75, 2*75, 75, 75)); 
    aux->setScale(0.5,0.5);
    
    Recurso* p = new Recurso(aux, new sf::Texture(tex), 0, 0, 0, 0, 0, 2);
    
    return p;
}

Recurso* RecursosFactory::crearMunicionMetralleta()
{
    sf::Texture tex;
    if (!tex.loadFromFile("resources/hud.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    sf::Sprite sprite(tex);
    
    
    sf::Sprite* aux = new sf::Sprite(sprite);
    
    aux->setOrigin(75/2,75/2);
    aux->setTextureRect(sf::IntRect(10*75, 2*75, 75, 75)); 
    aux->setScale(0.5,0.5);
    
    Recurso* p = new Recurso(aux, new sf::Texture(tex), 0, 0, 0, 0, 0, 4);
    
    return p;
}

Recurso* RecursosFactory::crearMunicionGranada()
{
    sf::Texture tex;
    if (!tex.loadFromFile("resources/hud.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    sf::Sprite sprite(tex);
    
    
    sf::Sprite* aux = new sf::Sprite(sprite);
    
    aux->setOrigin(75/2,75/2);
    aux->setTextureRect(sf::IntRect(12*75, 2*75, 75+37.5, 75)); 
    aux->setScale(0.5,0.5);
    
    Recurso* p = new Recurso(aux, new sf::Texture(tex), 0, 0, 0, 0, 0, 7);
    
    return p;
}

Recurso* RecursosFactory::crearRecurso(int tip)
{
    Recurso* p;
    
    if(tip == 2)
    {
        p = crearMunicionEscopeta();
    }
    else if(tip == 3)
    {
        p = crearBotiquin();
    }
    else if(tip == 4)
    {
        p = crearMunicionMetralleta();
    }
    else if(tip == 5)
    {
        p = crearBarril();
    }
    else if(tip == 6)
    {
        p = crearMadera();
    }
    else
    {
        p = crearMunicionGranada();
    }
    
    return p;
}