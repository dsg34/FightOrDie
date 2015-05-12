#include <math.h> 
#include <vector>
#include "Protagonista.h"
#include "HUD.h"
#include "ArmaFactory.h"
#include "Nivel.h"
#include "Mundo.h"
#include "Menu.h"
#include "MenuFactory.h"
#include "GuardarCargarPartida.h"
using namespace std;
#define kVel 5

#define UPDATE_TIME 1000/15

#ifndef JUEGO_H
#define	JUEGO_H

class Juego {
public:
    Juego();
    Juego(const Juego& orig);
    virtual ~Juego();   
    
    int menuMejoras();
    void cambiarNivel();
    bool menuSalirDelJuego();
    bool capturarCierre();
    int ejecutarMenu(int tipo);
    
    void reiniciarJuego();
    void siguienteNivel();
    void repetirNivel();
    
    
    int ejecutarJuego();
private:
    sf::RenderWindow* window;
    Mundo* mundo;
    Menu* menu;
    GuardarCargarPartida* gestionPartida;
};

#endif	/* JUEGO_H */