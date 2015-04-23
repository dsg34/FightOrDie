/* 
 * File:   Mundo.cpp
 * Author: Dani
 * 
 * Created on 23 de abril de 2015, 18:21
 */

#include "Mundo.h"


Mundo::Mundo(sf::RenderWindow &w) {
    window=&w;
    tamPantalla=(sf::Vector2<int>)window->getSize();
    
    fabricaPersonaje=new PersonajeFactory();

    std::vector<Arma*> a;
    sf::Vector2<int> pos;
    pos.x=tamPantalla.x;
    pos.y=tamPantalla.y;
    protagonista=fabricaPersonaje->crearProtagonista(pos);
       
    fabricaNivel=new NivelFactory();
    nivel = fabricaNivel->crearNivel(1, protagonista, tamPantalla);
    window->setMouseCursorVisible(false);
    
    reloj->restart();
    frecuencia=reloj->getElapsedTime();
    
    
    /***************************************************
     
     
     
     INICIALIZAR SPRITE APUNTAR
     
     
     */
}

Mundo::Mundo(const Mundo& orig) {
}

Mundo::~Mundo() {
}

sf::Vector2<int> Mundo::posicionCursor(sf::RenderWindow &window){
    sf::Vector2<int> pos;
    sf::Mouse raton;
    pos.x = raton.getPosition(window).x;
    pos.y = raton.getPosition(window).y;
    
    return pos;
}

void Mundo::ejecutarMundo(){    
    
    bool cederEjecucion=false;      
    //Bucle del juego
    while (window->isOpen() && cederEjecucion!=true)
    {
        //Controlamos la frecuencia a la que se ejecuta el programa
        frecuencia = reloj.getElapsedTime();
        if(frecuencia.asSeconds()>0.05){ 
            
            //Bucle de obtención de eventos
            sf::Event event;
            window->pollEvent(event);
            if(event.type==sf::Event::Closed){
                window->close();
            }
            if(event.type==sf::Keyboard::Escape)
               cederEjecucion=true;                                        
            
            protagonista->updateProtagonista();
            nivel->actualizarNivel(protagonista, 0,0);
        
            
            reloj.restart();
        }
    }
}

void Mundo::pintarMundo(){
    window->clear();
    nivel->pintarMapa(*window);//map->Draw(window);
    //Actualizamos la posicion de las balas
    protagonista->pintarProtagonista();
            
    //Pintamos las balas
    miPistola->pintarProyectiles(*window);
            
    //std::cout << miPistola->getSecundaria().size() << std::endl;
    //Pintamos los demas sprites
            
    window->draw(sprite);
    nivel->pintarNivel(*window);//hud.pintarHUD(window);
    apuntar.setPosition(posicionCursor(*window).x, posicionCursor(*window).y);
    window->draw(apuntar);                                    
    window->display();
}
