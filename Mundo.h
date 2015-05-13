#include <math.h> 
#include <vector>
#include "Protagonista.h"
#include "HUD.h"
#include "NivelFactory.h"
#include "ArmaFactory.h"
#define kVel 5

#ifndef MUNDO_H
#define	MUNDO_H

class Mundo {
public:
    Mundo(sf::RenderWindow &w);
    Mundo(const Mundo& orig);
    virtual ~Mundo();
    
    sf::Vector2<int> posicionCursor();
    bool capturarCierre();
    bool capturarPausa();
    Nivel* getNivel();
    void setMejoraArma(int i, int m);
    void cargarPartida(std::vector<int> v);
    
    int getPuntuacionMundo();
    int setPuntuacionMundo(int p);
    Protagonista* getProtagonista();
    void siguienteNivel();
    void reiniciarProtagonista();
    void reiniciarMundo();
    void reiniciarNivel();
    void cambiarNivel(int i);
    
    void setPuntuacionNivel(int p);
    int getPuntuacionNivel();
    
    int ejecutarMundo();
    
    void interpolarMundo();
    void pintarMundo();
private:
    sf::RenderWindow* window;    
    
    Protagonista* protagonista;
    PersonajeFactory* fabricaPersonaje;
    
    Nivel* nivel;
    NivelFactory* fabricaNivel;
    
    sf::Vector2<int> tamPantalla;  
    
    sf::Texture* tex;
    sf::Sprite* apuntar;
    
    sf::Clock relojUpdate;
    sf::Clock relojRender;
    
    float frecuencia;
    int contInterpolacion;
    int px;
    int py;
};

#endif	/* MUNDO_H */