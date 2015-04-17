/* 
 * File:   RecursoHUD.h
 * Author: Dani
 *
 * Created on 17 de abril de 2015, 12:31
 */
#include <SFML/Graphics.hpp>
#include <sstream>
#ifndef RECURSOHUD_H
#define	RECURSOHUD_H

class RecursoHUD {
public:
    RecursoHUD(int ti);
    RecursoHUD(const RecursoHUD& orig);
    virtual ~RecursoHUD();
    
    sf::Sprite* getSprite();
    int getNum();
    int getTipo();
    
    void setSprite(sf::Sprite* s);
    void setNum(int n);
    void setTipo(int t);
    void setScale(float s);
    
    void prueba(std::string s);
    void aumentarNum(int i);
    void masNum();
    void menosNum();
    void cambiarPosicion(int x, int y);
    std::string intAString(int p);
    
    void pintarRecurso(sf::RenderWindow &window);
    
private:
    sf::Texture* tex;
    sf::Sprite* sprite;
    sf::Font* fuente;
    sf::Text* texto;
    int num;
    int tipo;    
};

#endif	/* RECURSOHUD_H */

