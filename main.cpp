
#include <math.h> 
#include <vector>
#include "Protagonista.h"
#include "HUD.h"
#include "ArmaFactory.h"
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
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Fight or Die");

    sf::Clock reloj;
    reloj.restart();
    sf::Time frecuencia;    
    
    /////////////////////////////////////////////////Pruebas ArmaFactory
    ArmaFactory* fabricaArmas = new ArmaFactory();
    
    Arma* miPistola = fabricaArmas->crearPistola();
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

    Personaje* pers = new Personaje(new sf::Sprite(sprite),new sf::Texture(tex),sprite.getPosition(), 20, 5);
    sf::Vector2<int> vec = (sf::Vector2<int>) window.getSize();
    
    HUD hud = HUD(pers, vec);
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
                        
                        //Mapeo del cursor
                        case sf::Keyboard::D:
                            sprite.setTextureRect(sf::IntRect(0*75, 2*75, 75, 75));
                            //Escala por defecto
                            sprite.setScale(1,1);
                            sprite.move(kVel,0);
                        break;

                        case sf::Keyboard::A:
                            sprite.setTextureRect(sf::IntRect(0*75, 2*75, 75, 75));
                            //Reflejo vertical
                            sprite.setScale(-1,1);
                            sprite.move(-kVel,0); 
                        break;
                        
                        case sf::Keyboard::W:
                            sprite.setTextureRect(sf::IntRect(0*75, 3*75, 75, 75));
                            sprite.move(0,-kVel); 
                        break;
                        
                        case sf::Keyboard::S:
                            sprite.setTextureRect(sf::IntRect(0*75, 0*75, 75, 75));
                            sprite.move(0,kVel); 
                        break;     
                        
                        case sf::Keyboard::Num1:
                            miPistola = fabricaArmas->crearPistola();
                        break;
                        
                        case sf::Keyboard::Num2:
                            miPistola = fabricaArmas->crearMetralleta();
                        break;
                        
                        case sf::Keyboard::Num3:
                            miPistola = fabricaArmas->crearEscopeta();
                        break;
                        
                        case sf::Keyboard::Num4:
                            miPistola = fabricaArmas->crearHacha();
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

            }
            
        }
        frecuencia = reloj.getElapsedTime();

        //Controlamos la frecuencia a la que se ejecuta el programa
        if(frecuencia.asSeconds()>0.05){  
            window.clear();
            //Actualizamos la posicion de las balas
            miPistola->updateProyectiles();
            
            //Pintamos las balas
            miPistola->pintarProyectiles(window);
            hud.pintarHUD(window);
            //std::cout << miPistola->getSecundaria().size() << std::endl;
            //Pintamos los demas sprites
            window.draw(sprite);
                
            apuntar.setPosition(posicionCursor(window).x, posicionCursor(window).y);
            window.draw(apuntar);
            
            window.setMouseCursorVisible(false);
            
            window.display();
            reloj.restart();
        }
    }

    return 0;
}