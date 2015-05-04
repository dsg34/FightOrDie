
#include "MenuFactory.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

MenuFactory::MenuFactory() {
}

MenuFactory::MenuFactory(const MenuFactory& orig) {
}

MenuFactory::~MenuFactory() 
{
    delete menu;
}

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
    if(!font.loadFromFile("resources/Avojaloin.ttf")){
        //handle error
        std::cout << "No carga la fuente!" << std::endl;
    }
    
    sf::Font* fuente=new sf::Font(font);
    std::vector<std::string> apartados;
    if(id==1){
        apartados.push_back("Jugar");
    }else if(id==2){
        apartados.push_back("Continuar");
    }else if(id==3){
        apartados.push_back("Siguiente nivel");

    }else if(id==4){
        apartados.push_back("Reiniciar juego");
    }
    
    apartados.push_back("Opciones");
    apartados.push_back("Salir");
    
    menu = new Menu(aux, tex, fuente, x, y, apartados);
    return menu;
}
