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
    bool getMostrarPuntuacion();
    
    void setSprite(sf::Sprite* s);
    void setNum(int n);
    void setTipo(int t);
    void setScale(float s);
    void setMostrarPuntuacion(bool m);
    void setOpacity(float o);
    std::string intAString(int p);
    void cambiarASerrucho();
    
    void cambiarNum(int i);
    void aumentarNum(int i);
    void masNum();
    void menosNum();
    void cambiarPosicion(int x, int y);
    
    void pintarRecurso(sf::RenderWindow &window);
    
private:
    sf::Texture* tex;
    sf::Sprite* sprite;
    sf::Font* fuente;
    sf::Text* texto;
    float opacidad;
    int num;
    int tipo;
    bool mostrarPuntuacion;
};

#endif	/* RECURSOHUD_H */

