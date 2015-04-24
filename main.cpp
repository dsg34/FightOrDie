/*
#include <math.h> 
#include <vector>
#include "Protagonista.h"
#include "HUD.h"
#include "ArmaFactory.h"
#include "Nivel.h"
#include "Mundo.h"
#include "Menu.h"
#include "MenuFactory.h"
#define kVel 5


int main()
{
    sf::RenderWindow window(sf::VideoMode(1300, 750), "Fight or Die");
    
    Mundo* mundo = new Mundo(window);
    MenuFactory* fabMenu = new MenuFactory();
    Menu* menu = fabMenu(window.getSize().x, window.getSize().y, 1);
    //mundo->ejecutarMundo();
    int seleccion=-1;
    while(seleccion!=3){        
        menu->GetPressedItem();
        menu->update(window);
        
        menu->draw(window);
    }
    
    return 0;
}*/
#include <math.h> 
#include <vector>
#include "Protagonista.h"
#include "HUD.h"
#include "ArmaFactory.h"
#include "Nivel.h"
#define kVel 5

sf::Vector2<int> posicionCursor(sf::RenderWindow &window){
    sf::Vector2<int> pos;
    sf::Mouse raton;
    pos.x = raton.getPosition(window).x;
    pos.y = raton.getPosition(window).y;
    
    return pos;
}

sf::Vector2<float> vectorDisparo(sf::Vector2<float> puntoPersonaje, sf::Vector2<int> puntoCursor){
    static const float pi = 3.141592654f;        
    
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

int main()
{
    //Creamos una ventana 
    sf::RenderWindow window(sf::VideoMode(1300, 750), "Fight or Die");

    sf::Clock reloj;
    reloj.restart();
    sf::Time frecuencia;
    
    /////////////////////////////////////////////////Pruebas ArmaFactory
    ArmaFactory* fabricaArmas = new ArmaFactory();
    
    
    
    MapLoader* map = new MapLoader();
    map->LoadFromFile("resources/nivel1.tmx");
    Arma* miPistola = fabricaArmas->crearMetralleta();
    miPistola->setMunicionSecundaria(20);
    //Arma* miSecundaria = fabricaArmas->crearGranada();
    int balas=0;
    bool existePersonaje=true;
    
    /***********************************************************CARGA DE SPRITES****************************************************************************/
    sf::Texture tex;
    if (!tex.loadFromFile("resources/sprite_general.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    
    //Y creo el spritesheet a partir de la imagen anterior
    sf::Sprite sprite(tex);
    sf::Sprite apuntar(tex);
    
    //Le pongo el centroide donde corresponde
    sprite.setOrigin(75/2,75/2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite.setTextureRect(sf::IntRect(0*75, 0*75, 75, 75));
    
    apuntar.setOrigin(75/2,75/2);
    apuntar.setTextureRect(sf::IntRect(1*75, 4*75, 75, 75));
   
    // Lo dispongo en el centro de la pantalla
    sprite.setPosition(320, 240);
    
    Protagonista* prota = new Protagonista(new sf::Sprite(sprite),new sf::Texture(tex),sprite.getPosition(), 20, 5, miPistola);
    sf::Vector2<int> vec = (sf::Vector2<int>) window.getSize();
    std::vector<int> lados;
    lados.push_back(1);
    lados.push_back(2);
    Nivel* niv = new Nivel(1, prota, vec, lados, 5.0);
    
    HUD hud = HUD(prota, vec);
    //Bucle del juego
    while (window.isOpen())
    {
        //Bucle de obtención de eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            
            switch(event.type){
                
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                    break;
                /***** Al hacer click izquierdo con el raton, se llama al evento disparar de la Arma ************************************************************/
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        miPistola->disparar(sprite.getPosition(), posicionCursor(window));
                    }else if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        miPistola->dispararSecundaria(sprite.getPosition(), posicionCursor(window));
                    }
                    break;
                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    
                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(event.key.code) {
                        
                        case sf::Keyboard::Z:
                            prota->setVida(prota->getVida()-1);                             
                        break;
                        
                        case sf::Keyboard::X:
                            prota->setVida(prota->getVida()+1);                            
                        break;
                        
                        //Mapeo del cursor
                        case sf::Keyboard::D:
                            sprite.setTextureRect(sf::IntRect(0*75, 2*75, 75, 75));
                            //Escala por defecto
                            sprite.setScale(1,1);
                            if(map->Colision((sprite.getPosition().x + kVel),(sprite.getPosition().y + 75/2),0)){                                
                                sprite.move(kVel,0);
                            }
                        break;

                        case sf::Keyboard::A:
                            sprite.setTextureRect(sf::IntRect(0*75, 2*75, 75, 75));
                            //Reflejo vertical
                            sprite.setScale(-1,1);
                            if(map->Colision((sprite.getPosition().x-kVel),sprite.getPosition().y + 75/2, 0)){                                
                                sprite.move(-kVel,0); 
                            }
                        break;
                        
                        case sf::Keyboard::W:
                            sprite.setTextureRect(sf::IntRect(0*75, 3*75, 75, 75));
                            if(map->Colision(sprite.getPosition().x,(sprite.getPosition().y - kVel + 75/2),0)){
                                sprite.move(0,-kVel);  
                            }
                                                         
                        break;
                        
                        case sf::Keyboard::S:
                            sprite.setTextureRect(sf::IntRect(0*75, 0*75, 75, 75));
                            if(map->Colision(sprite.getPosition().x,(sprite.getPosition().y + kVel + 75/2),0)){
                                sprite.move(0,kVel);
                            }
                        break;  
                        
                        case sf::Keyboard::Num1:
                            miPistola = fabricaArmas->crearPistola();
                            prota->setArma(miPistola);
                        break;
                        
                        case sf::Keyboard::Num2:
                            miPistola = fabricaArmas->crearMetralleta();
                            prota->setArma(miPistola);
                        break;
                        
                        case sf::Keyboard::Num3:
                            miPistola = fabricaArmas->crearEscopeta();
                            prota->setArma(miPistola);
                        break;
                        
                        case sf::Keyboard::Num4:
                            miPistola = fabricaArmas->crearHacha();
                            prota->setArma(miPistola);
                        break;
                        
                        case sf::Keyboard::M:
                            niv->crearMensaje("Has pulsado la M \nENHORABUENA", -1, 30);
                            
                        break;
                        
                        //Pulsar R para reiniciar partida
                        case sf::Keyboard::R:
                            existePersonaje=true;
                            balas=0;
                            
                        break;
                        
                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            window.close();
                        break;
                        
                        //Cualquier tecla desconocida se imprime por pantalla su código
                        default:
                            std::cout << event.key.code << std::endl;
                        break;
                              
                    }
                    prota->setSprite(new sf::Sprite(sprite));
            }
            
        }
        frecuencia = reloj.getElapsedTime();
        niv->actualizarNivel(prota, 0,0);
        //Controlamos la frecuencia a la que se ejecuta el programa
        if(frecuencia.asSeconds()>0.05){  
            window.clear();
            niv->pintarMapa(window,0);//map->Draw(window);
            //Actualizamos la posicion de las balas
            miPistola->updateProyectiles();
            
            //Pintamos las balas
            miPistola->pintarProyectiles(window);            
            
            window.draw(sprite);
            niv->pintarNivel(window);//hud.pintarHUD(window);
            apuntar.setPosition(posicionCursor(window).x, posicionCursor(window).y);
            window.draw(apuntar);
            
            window.setMouseCursorVisible(false);
            
            window.display();
            reloj.restart();
        }
    }

    return 0;
}