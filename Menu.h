#ifndef MENU_H
#define	MENU_H
#include <SFML/Graphics.hpp>
#include "Sonidos.h"

class Menu {
public:
    Menu(sf::Sprite* s, sf::Texture* t, sf::Font* font, int x, int y, std::vector<std::string> apartados);
    
    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem();
    int update(sf::RenderWindow &window);    

private:
    sf::Sprite* sprite;
    sf::Texture* tex;
    int selectedItemIndex;
    sf::Font* font;
    int elementos;
    std::vector<sf::Text*> menu;
    sf::Clock xbox;
    Sonidos* audios;
};

#endif	/* MENU_H */
