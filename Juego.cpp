/* 
 * File:   Juego.cpp
 * Author: Dani
 * 
 * Created on 4 de mayo de 2015, 21:54
 */

#include "Juego.h"

Juego::Juego() {

}

Juego::Juego(const Juego& orig) {
}

Juego::~Juego() {    
    
}

bool Juego::menuSalirDelJuego(){
    bool salir=false;
    
    int estadoMenu = ejecutarMenu(5);
    switch(estadoMenu){
        case -10: salir=true; break;
        case -11: salir=false; break;
    }
    return salir;    
}

bool Juego::capturarCierre()
{
    bool captura=false;
    //Bucle de obtencion de eventos
    sf::Event event;
    while(window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            if(menuSalirDelJuego()==true){
                exit(0);
            }
        }
    }
    return captura;
}

int Juego::ejecutarMenu(int tipo){
    
    //1: Menu Inicio ; 2: Menu Pausa ; 3: Menu Fin de nivel ; 4: Menu muerte ; 5: Salir
    sf::Clock reloj;
    reloj.restart();    
    MenuFactory* fab = new MenuFactory();
    Menu* menu;        
    menu=fab->hacerMenu(window->getSize().x, window->getSize().y, tipo);
    int estadoMenu = -1;
    while(estadoMenu==-1){                              
        if(reloj.getElapsedTime().asMilliseconds()>UPDATE_TIME){
            estadoMenu = menu->update(*window);
            window->clear();
            menu->draw(*window);
            window->display();
            reloj.restart();
            capturarCierre();
         }
    }
    return estadoMenu;
}
void Juego::reiniciarJuego(){
    //int niv = mundo->getNivel()->getId();
    int niv=1;
    delete mundo;
    mundo = new Mundo(*window, niv);
}

void Juego::siguienteNivel(){
    //int niv = mundo->getNivel()->getId();
    int niv=1;
    delete mundo;
    mundo = new Mundo(*window, niv);
}

int Juego::ejecutarJuego()
{        
    sf::RenderWindow w(sf::VideoMode(1300, 750), "Fight or Die");    
    window=&w;
    mundo = new Mundo(*window, 1);
    bool salir = false; bool salirJuego = false; bool salirMenu = false;
    bool confirmar = false;
    int estadoMundo = -1;
    int estadoMenu = -1;
    sf::Clock reloj;
    reloj.restart();    

    //1: Menu Inicio ; 2: Menu Pausa ; 3: Menu Fin de nivel ; 4: Menu muerte ; 5: Menu ¿Desea Salir?            
    //MENU DE INICIO
    while(salir!=true){
        delete mundo;
        mundo = new Mundo(*window, 1);
        estadoMenu = ejecutarMenu(1);    
        if(estadoMenu==-2){
            if(menuSalirDelJuego())
                exit(0);
        }else{
            while(salirJuego!=true){
                estadoMundo = mundo->ejecutarMundo(); 
                while(salirMenu!=true){
                    //MENU DE PAUSA-FIN DE NIVEL-MUERTE
                    estadoMenu = ejecutarMenu(estadoMundo);
                    //-2: Salir ; -3: Jugar ; -4: Continuar ; -5: Mejoras ; -6: Siguiente nivel ; -7: Reiniciar juego; -8: Opciones ; -9: Volver a inicio      
                    switch(estadoMenu){
                        case -2: if(menuSalirDelJuego()){
                                    salir=true;salirJuego=true;salirMenu=true;
                                 }break; //Salir
                        case -3: /*salir=true;*/break; //Jugar
                        case -4: salirMenu=true; break;            //Continuar
                        case -5: /*salir=true;*/break; //Mejoras
                        case -6: /*salir=true;*/break; //Siguiente nivel                    
                        case -7: salirMenu=true; reiniciarJuego();break; //Reiniciar juego 
                        case -8: /*salir=true;*/break; //Opciones
                        case -9: salirMenu=true; salirJuego=true;reiniciarJuego();break; //Volver a inicio                     
                    }
                }
                salirMenu=false;
            }
            salirJuego=false;
        }
    }
    return 0;
}
