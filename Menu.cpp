#include "Menu.h"
#include <iostream>
#include <vector>

Menu::Menu(sf::Sprite* s, sf::Texture* t, sf::Font* font, int x, int y, std::vector<std::string> apartados){
    sprite=new sf::Sprite(*s);
    tex=new sf::Texture(*t);
    sprite->setTexture(*tex);
    elementos=apartados.size();
    
    sf::Text aux;
    for(int i=0; i<elementos; i++){
        aux.setFont(*font);
        aux.setCharacterSize(40);
        if(i==0)
            aux.setColor(sf::Color::Red);
        else
            aux.setColor(sf::Color::White);
        aux.setString(apartados[i]);
        aux.setPosition(sf::Vector2f(x/7, 250+(i*50)));
        
        menu.push_back(new sf::Text(aux));
    }
    
    selectedItemIndex = 0;
}

int Menu::GetPressedItem(){ 
    return selectedItemIndex; 
}

int Menu::update(sf::RenderWindow &window){
    sf::Event event;
    window.pollEvent(event);
    if(event.type == sf::Event::KeyReleased){
        if(event.key.code==sf::Keyboard::Up){
            MoveUp();
        }else if(event.key.code==sf::Keyboard::Down){
            MoveDown();
        }else if(event.key.code==sf::Keyboard::Return){
            switch(GetPressedItem()){
                case 0:
                    std::cout << "Has presionado Jugar" <<std::endl;
                    break;
                case 1:
                    std::cout << "Has presionado Opciones" <<std::endl;
                    break;
                case 2:                  
                    return 1;
            }
        }
    }
   
    return 0;
}

void Menu::draw(sf::RenderWindow &window){
    sf::Sprite aux = *sprite;
    window.draw(aux);
    for(int i=0; i<elementos; i++){
        window.draw(*menu[i]);
    }
}

void Menu::MoveUp(){
    if(selectedItemIndex - 1 >= 0){
        menu[selectedItemIndex]->setColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex]->setColor(sf::Color::Red);
    }
}

void Menu::MoveDown(){
    if(selectedItemIndex + 1 < elementos){
        menu[selectedItemIndex]->setColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex]->setColor(sf::Color::Red);
    }
}
