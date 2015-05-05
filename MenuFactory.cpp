
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
    if(id==1){
        apartados.push_back("Jugar");
    }else if(id==2){
        apartados.push_back("Continuar");
        apartados.push_back("Mejoras");
        apartados.push_back("Volver a inicio");
    }else if(id==3){
        apartados.push_back("Siguiente nivel");
        apartados.push_back("Volver a inicio");
    }else if(id==4){
        apartados.push_back("Reiniciar juego");
        apartados.push_back("Volver a inicio");
    }
    
    if(id==5){
        apartados.push_back("Abandonar el juego");
        apartados.push_back("Si");
        apartados.push_back("No");
    }else{
        apartados.push_back("Opciones");
        apartados.push_back("Salir");
    }
    
    menu = new Menu(aux, tex, fuente, x, y, apartados);
    return menu;
}
