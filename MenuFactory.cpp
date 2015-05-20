#include "MenuFactory.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

MenuFactory::MenuFactory() {

}

MenuFactory::MenuFactory(const MenuFactory& orig) {
}

MenuFactory::~MenuFactory() {
}

/*
 1: Menu Inicio
 2: Menu Pausa
 3: Menu Fin de nivel
 4: Menu muerte
 5: Menu Desea salir?
 */
Menu* MenuFactory::hacerMenu(int x, int y, int id){
    sf::Texture auxText;
    if (!auxText.loadFromFile("resources/menu.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    sf::Texture* tex = new sf::Texture(auxText);
    sf::Sprite sprite(*tex);
    //Este es el sprite que le pasaremos a disparar, para que las balas que se creen lo hagan con dicho sprite
    sprite.setOrigin(1300/2,750/2);
    sprite.setTextureRect(sf::IntRect(0, 0, 1300, 750));
    sf::Sprite* aux = new sf::Sprite(sprite);
    aux->setPosition(1300/2,750/2);
    
    sf::Font font;
    if(!font.loadFromFile("fonts/Avojaloin.ttf")){
        //handle error
        std::cout << "No carga la fuente!" << std::endl;
    }
    
    sf::Font* fuente=new sf::Font(font);
    std::vector<std::string> apartados;
    if(id==1){                                  //Inicio
        apartados.push_back("Jugar");
        apartados.push_back("Continuar partida");
        apartados.push_back("Modo arcade");
        apartados.push_back("Controles");
        apartados.push_back("Mejores puntuaciones");
    }else if(id==2){                            //Pausa
        apartados.push_back("Continuar");
        apartados.push_back("Guardar partida");
        apartados.push_back("Mejoras");
        apartados.push_back("Volver a inicio");
    }else if(id==3){                            //Fin de nivel
        apartados.push_back("NIVEL FINALIZADO");     /**/
        apartados.push_back("Siguiente nivel");
        apartados.push_back("Volver a inicio");
    }else if(id==4){                            //Menu muerte
        apartados.push_back("HAS MUERTO");           /**/
        apartados.push_back("Reiniciar juego");
        apartados.push_back("Volver a inicio");
    }else if(id==9){                            //Pausa
        apartados.push_back("Continuar");
        apartados.push_back("Mejoras");
        apartados.push_back("Volver a inicio");
    }
    
    if(id==5){                                  //Menu salir
        apartados.push_back("ABANDONAR EL JUEGO");   /**/
        apartados.push_back("Si");
        apartados.push_back("No");
    }else if(id==6){                            //Menu mejoras
        apartados.push_back("MEJORAR ARMA");         /**/
        apartados.push_back("Mejorar pistola");
        apartados.push_back("Mejorar metralleta");
        apartados.push_back("Mejorar escopeta");
        apartados.push_back("Mejorar hacha");
        apartados.push_back("Atras");
    }else if(id==7){                                  //Menu Puntuaciones
        apartados.push_back("Atras");
    }else if(id==8){
        apartados.push_back("Volver a inicio");
    }
    else{
        apartados.push_back("Salir");
    }
    
    menu = new Menu(aux, tex, fuente, x, y, apartados);
    return menu;
}