

#include "Juego.h"


int main()
{
    Juego* juego = new Juego(); 
    
    juego->ejecutarJuego();

    delete juego;

    return 0;
}
