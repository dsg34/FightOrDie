/* 
 * File:   Mundo.cpp
 * Author: Dani
 * 
 * Created on 23 de abril de 2015, 18:21
 */

#include "Mundo.h"
#define UPDATE_TIME 1/15
#define RENDER_TIME 1/60

Mundo::Mundo(sf::RenderWindow &w) {
    window=&w;
    tamPantalla=(sf::Vector2<int>)window->getSize();
    
    fabricaPersonaje=new PersonajeFactory();

    std::vector<Arma*> a;
    sf::Vector2<int> pos;
    pos.x=tamPantalla.x;
    pos.y=tamPantalla.y;
    //protagonista=fabricaPersonaje->crearProtagonista(pos);
       
    fabricaNivel=new NivelFactory();
    nivel = fabricaNivel->crearNivel(1, protagonista, tamPantalla);
    window->setMouseCursorVisible(false);
    
    relojUpdate->restart();
    relojRender->restart();    
        
    sf::Texture texAux;
    if (!texAux.loadFromFile("resources/sprite_general.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    
    tex = new sf::Texture(texAux);
    //Y creo el spritesheet a partir de la imagen anterior    
    apuntar->setTexture(*tex);    
    
    apuntar->setOrigin(75/2,75/2);
    apuntar->setTextureRect(sf::IntRect(1*75, 4*75, 75, 75));
    apuntar->setPosition((sf::Vector2f)posicionCursor(*window));
    
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

int Mundo::ejecutarMundo(){    
    int estado=0;   //estado 0: Sigue en juego; estado 1: Menu de pausa; estado 2: Menu de "Has muerto"; estado 3: Nivel finalizado; estado 4: Juego finalizado
    bool nivelAcabado=false;  
    bool estadoMuerto=false;
    //Bucle del juego
    /*
    while (window->isOpen() && estado==0)
    {
        //Controlamos la frecuencia a la que se ejecuta el programa
        frecuencia = relojUpdate->getElapsedTime();
        //Actualizamos 15 veces por segundo
        if(frecuencia.asSeconds()>UPDATE_TIME){ 
            
            //Bucle de obtención de eventos
            sf::Event event;
            window->pollEvent(event);
            if(event.type==sf::Event::Closed){
                window->close();
            }
            if(event.type==sf::Keyboard::Escape)
               estado=1;                                        
                        
            estadoMuerto=protagonista->updateProtagonista(nivel->getZombies());
            if(estadoMuerto==true)
                estado=2
            nivelAcabado = nivel->actualizarNivel(protagonista, 0,0);
            if(nivelAcabado==true)//Nivel finalizado
                estado=3                                   
            relojUpdate->restart();
        }
        frecuencia = relojRender->getElapsedTime();
        //Pintamos e interpolamos 60 veces por segundo
        if(frecuencia.asSeconds()>RENDER_TIME){
            interpolarMundo();
            pintarMundo();
            relojRender->restart();
        }
    }*/
    return estado;
}

void Mundo::interpolarMundo(){
    //SE INTERPOLA: PERSONAJE - ZOMBIES - GRANADAS - PROYECTILES
    /*if(contInterpolacion==4)
        contInterpolacion=0;
    
    sf::Vector2<int> mov = protagonista->getVectorAnterior()-protagonista->getVectorActual();
    mov.x = mov.x*contInterpolacion*0.25;
    mov.y = mov.y*contInterpolacion*0.25;
    protagonista->getSprite()->setPosition(protagonista->getVectorActual().x+mov.x, protagonista->getVectorActual().y+mov.y);
    
    std::vector<Zombie*> zom = nivel->getZombies();
    for(int i=0; i<zom.size(); i++){
        mov = zom[i]->getVectorAnterior()-zom[i]->getVectorActual();
        mov.x = mov.x*contInterpolacion*0.25;
        mov.y = mov.y*contInterpolacion*0.25;
        zom[i]->getSprite()->setPosition(zom[i]->getVectorActual().x+mov.x, zom[i]->getVectorActual().y+mov.y);
    }
    
    std::vector<Proyectil*> bal = protagonista->getArma()->getCargador();
    for(int i=0; i<bal.size(); i++){
        mov = bal[i]->getVectorAnterior()-bal[i]->getVectorActual();
        mov.x = mov.x*contInterpolacion*0.25;
        mov.y = mov.y*contInterpolacion*0.25;
        bal[i]->getSprite()->setPosition(bal[i]->getVectorActual().x+mov.x, bal[i]->getVectorActual().y+mov.y);
    }
    
    std::vector<Granada*> gra = protagonista->getArma()->getSecundaria();
    for(int i=0; i<gra.size(); i++){
        mov = gra[i]->getVectorAnterior()-gra[i]->getVectorActual();
        mov.x = mov.x*contInterpolacion*0.25;
        mov.y = mov.y*contInterpolacion*0.25;
        gra[i]->getSprite()->setPosition(gra[i]->getVectorActual().x+mov.x, gra[i]->getVectorActual().y+mov.y);
    }*/
}

void Mundo::pintarMundo(){
    /*window->clear();
    nivel->pintarMapa(*window);//map->Draw(window);
    //Actualizamos la posicion de las balas
    protagonista->pintarProtagonista();                                    
    
    nivel->pintarNivel(*window);//hud.pintarHUD(window);
    apuntar->setPosition(posicionCursor(*window).x, posicionCursor(*window).y);
    window->draw(*apuntar);                                    
    window->display();*/
}
