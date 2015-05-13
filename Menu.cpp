#include "Menu.h"
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

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
    
    if(menu[0]->getString()!=sf::String("ABANDONAR EL JUEGO") && menu[0]->getString()!=sf::String("NIVEL FINALIZADO") && menu[0]->getString()!=sf::String("MEJORAR ARMA")&& menu[0]->getString()!=sf::String("HAS MUERTO"))
        selectedItemIndex = 0;
    else{
        selectedItemIndex = 1;        
        menu[0]->setColor(sf::Color::Yellow);
        menu[1]->setColor(sf::Color::Red);
    }
    
    xbox.restart();
}

int Menu::GetPressedItem(){ 
    return selectedItemIndex; 
}

int Menu::update(sf::RenderWindow &window)
{    
    int devuelve=-1;
    
    
    if(xbox.getElapsedTime().asSeconds() > 0.1 )
    {
        if(sf::Joystick::isConnected(1))
        {
            float positionY = sf::Joystick::getAxisPosition(1, sf::Joystick::Y);   

            if(positionY < -20)
                MoveUp();
            else if(positionY > 20)
                MoveDown();

            if(sf::Joystick::isButtonPressed(1, 0))
            {
                devuelve=GetPressedItem();
                    if(menu[devuelve]->getString() == sf::String("Salir"))
                        devuelve=-2;
                    else if(menu[devuelve]->getString() == "Jugar")
                        devuelve=-3;
                    else if(menu[devuelve]->getString() == "Continuar")
                        devuelve=-4;
                    else if(menu[devuelve]->getString() == "Mejoras")
                        devuelve=-5;
                    else if(menu[devuelve]->getString() == "Siguiente nivel")
                        devuelve=-6;
                    else if(menu[devuelve]->getString() == "Reiniciar juego")
                        devuelve=-7;
                    else if(menu[devuelve]->getString() == "Opciones")
                        devuelve=-8;
                    else if(menu[devuelve]->getString() == "Volver a inicio")
                        devuelve=-9;
                    else if(menu[devuelve]->getString() == "Si")
                        devuelve=-10;
                    else if(menu[devuelve]->getString() == "No")
                        devuelve=-11;
                    else if(menu[devuelve]->getString() == "Atras")
                        devuelve=-12;
                    else if(menu[devuelve]->getString() == "Mejorar pistola")
                        devuelve=-13;
                    else if(menu[devuelve]->getString() == "Mejorar metralleta")
                        devuelve=-14;
                    else if(menu[devuelve]->getString() == "Mejorar escopeta")
                        devuelve=-15; 
                    else if(menu[devuelve]->getString() == "Mejorar hacha")
                        devuelve=-16;
            }
        }
        
        xbox.restart();
    }
    
    sf::Event event;
    window.pollEvent(event);
    
    if(event.type == sf::Event::KeyReleased){
        if(event.key.code==sf::Keyboard::Up){
            MoveUp();
        }else if(event.key.code==sf::Keyboard::Down){
            MoveDown();
        }else if(event.key.code==sf::Keyboard::Return ){            
            devuelve=GetPressedItem();
            if(menu[devuelve]->getString() == sf::String("Salir"))
                devuelve=-2;
            else if(menu[devuelve]->getString() == "Jugar")
                devuelve=-3;
            else if(menu[devuelve]->getString() == "Continuar")
                devuelve=-4;
            else if(menu[devuelve]->getString() == "Mejoras")
                devuelve=-5;
            else if(menu[devuelve]->getString() == "Siguiente nivel")
                devuelve=-6;
            else if(menu[devuelve]->getString() == "Reiniciar juego")
                devuelve=-7;
            else if(menu[devuelve]->getString() == "Opciones")
                devuelve=-8;
            else if(menu[devuelve]->getString() == "Volver a inicio")
                devuelve=-9;
            else if(menu[devuelve]->getString() == "Si")
                devuelve=-10;
            else if(menu[devuelve]->getString() == "No")
                devuelve=-11;
            else if(menu[devuelve]->getString() == "Atras")
                devuelve=-12;
            else if(menu[devuelve]->getString() == "Mejorar pistola")
                devuelve=-13;
            else if(menu[devuelve]->getString() == "Mejorar metralleta")
                devuelve=-14;
            else if(menu[devuelve]->getString() == "Mejorar escopeta")
                devuelve=-15; 
            else if(menu[devuelve]->getString() == "Mejorar hacha")
                devuelve=-16;
        }
    }
   
    return devuelve;
}

void Menu::draw(sf::RenderWindow &window){
    sf::Sprite aux = *sprite;
    window.draw(aux);
    for(int i=0; i<elementos; i++){
        window.draw(*menu[i]);
    }
}

void Menu::MoveUp(){
    if(selectedItemIndex - 1 >= 0 && (menu[selectedItemIndex-1]->getString()!=sf::String("ABANDONAR EL JUEGO")) && (menu[selectedItemIndex-1]->getString()!=sf::String("HAS MUERTO")) && (menu[selectedItemIndex-1]->getString()!=sf::String("NIVEL FINALIZADO")) && (menu[selectedItemIndex-1]->getString()!=sf::String("MEJORAR ARMA")) ){
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
