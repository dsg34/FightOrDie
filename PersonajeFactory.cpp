#include "PersonajeFactory.h"

PersonajeFactory* PersonajeFactory::pinstance = 0;

PersonajeFactory::PersonajeFactory() 
{   
    protagonistaCreado=false;
    
    sf::Texture texAux;
    if (!texAux.loadFromFile("resources/BillyPistola.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }

    texturaProtagonista = new sf::Texture(texAux);
    
    if(!texAux.loadFromFile("resources/zombie.png")){
        std::cerr <<"Error cargando la imagen zombie.png";
        exit(0);
    }
    
    texturaZombieNormal = new sf::Texture(texAux);
    
    
    if(!texAux.loadFromFile("resources/zombie_rapido.png")){
        std::cerr <<"Error cargando la imagen zombie.png";
        exit(0);
    }
    
    texturaZombieRapido = new sf::Texture(texAux);
    

    if(!texAux.loadFromFile("resources/zombie_fuerte.png")){
        std::cerr <<"Error cargando la imagen zombie.png";
        exit(0);
    }
    
    texturaZombieFuerte = new sf::Texture(texAux);
    
}

PersonajeFactory::PersonajeFactory(const PersonajeFactory& orig) {
}

PersonajeFactory::~PersonajeFactory() {
    
}

Protagonista* PersonajeFactory::crearProtagonista(sf::Vector2<float> p){
    
    if(protagonistaCreado==false)
    {
        sf::Sprite sprite(*texturaProtagonista);
        
        //Este es el sprite que le pasaremos a disparar, para que las balas que se creen lo hagan con dicho sprite
        sprite.setOrigin(75/2,75/2);
        sprite.setTextureRect(sf::IntRect(0*75, 0*75, 75, 75));

        sf::Sprite* aux = new sf::Sprite(sprite);
        protagonista = new Protagonista(aux, texturaProtagonista, p, 20, 5);
    }
    return protagonista;
}
Zombie* PersonajeFactory::crearZombie(int tipoZombie, sf::Vector2<float> p, int n){    
    if(tipoZombie == 1){
        //normal
        zombie = crearZombieNormal(p);
    }else if(tipoZombie == 2){
        //rapido
        zombie = crearZombieRapido(p);
    }else if(tipoZombie == 3){
        //gordo
        zombie = crearZombieGordo(p);
    }
    else if(tipoZombie == 4){
        //gordo
        zombie = crearBoss(p, n);
    }
    return zombie;
}
Zombie* PersonajeFactory::crearZombieNormal(sf::Vector2<float> p)
{
    
    sf::Sprite sprite(*texturaZombieNormal);
    
    sprite.setOrigin(75/2,75/2);
    sprite.setTextureRect(sf::IntRect(0*75,0*75,75,75));
    
    sf::Sprite* aux = new sf::Sprite(sprite);
    //Zombie(sprite, textura, posicion, maxVida, velocidad, danyo)
    zombie = new Zombie(aux, texturaZombieNormal, p, 20, 2, 0.2);
    
    return zombie;
}

Zombie* PersonajeFactory::crearBoss(sf::Vector2<float> p, int n)
{
    if(n == 1)
    {
        sf::Sprite sprite(*texturaZombieRapido);

        sprite.setOrigin(75/2,75/2);
        sprite.setTextureRect(sf::IntRect(0*75,0*75,75,75));
        sprite.setScale(2.5, 2.5);

        sf::Sprite* aux = new sf::Sprite(sprite);
        //Zombie(sprite, textura, posicion, maxVida, velocidad, danyo)
        zombie = new Zombie(aux, texturaZombieRapido, p, 100, 6, 2);
    }
    else if(n == 2)
    {
        sf::Sprite sprite(*texturaZombieNormal);

        sprite.setOrigin(75/2,75/2);
        sprite.setTextureRect(sf::IntRect(0*75,0*75,75,75));
        sprite.setScale(2.5, 2.5);

        sf::Sprite* aux = new sf::Sprite(sprite);
        //Zombie(sprite, textura, posicion, maxVida, velocidad, danyo)
        zombie = new Zombie(aux, texturaZombieNormal, p, 150, 5, 3);
    }
    else
    {
        sf::Sprite sprite(*texturaZombieFuerte);

        sprite.setOrigin(75/2,75/2);
        sprite.setTextureRect(sf::IntRect(0*75,0*75,75,75));
        sprite.setScale(2.5, 2.5);

        sf::Sprite* aux = new sf::Sprite(sprite);
        //Zombie(sprite, textura, posicion, maxVida, velocidad, danyo)
        zombie = new Zombie(aux, texturaZombieFuerte, p, 300, 4.5, 5);
    }
    
    return zombie;
}


Zombie* PersonajeFactory::crearZombieRapido(sf::Vector2<float> p)
{    
    sf::Sprite sprite(*texturaZombieRapido);
    
    sprite.setOrigin(75/2,75/2);
    sprite.setTextureRect(sf::IntRect(0*75,0*75,75,75));
    
    sf::Sprite* aux = new sf::Sprite(sprite);
    //Zombie(sprite, textura, posicion, maxVida, velocidad, danyo)
    zombie = new Zombie(aux, texturaZombieRapido, p, 10, 5, 0.1);
    
    return zombie;
}
    
Zombie* PersonajeFactory::crearZombieGordo(sf::Vector2<float> p){
    
    sf::Sprite sprite(*texturaZombieFuerte);
    
    sprite.setOrigin(75/2,75/2);
    sprite.setTextureRect(sf::IntRect(0*75,0*75,75,75));
    
    sf::Sprite* aux = new sf::Sprite(sprite);
    //Zombie(sprite, textura, posicion, maxVida, velocidad, danyo)
    zombie = new Zombie(aux, texturaZombieFuerte, p, 30, 1, 0.3);
    
    return zombie;
}
