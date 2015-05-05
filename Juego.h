/* 
 * File:   Juego.h
 * Author: Dani
 *
 * Created on 4 de mayo de 2015, 21:54
 */

#include <math.h> 
#include <vector>
#include "Protagonista.h"
#include "HUD.h"
#include "ArmaFactory.h"
#include "Nivel.h"
#include "Mundo.h"
#include "Menu.h"
#include "MenuFactory.h"
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
    
    void reiniciarJuego();
    bool menuSalirDelJuego();
    bool capturarCierre();
    int ejecutarMenu(int tipo);
    void siguienteNivel();
    
    int ejecutarJuego();
private:
    sf::RenderWindow* window;
    Mundo* mundo;
    Menu* menu;
};

#endif	/* JUEGO_H */

