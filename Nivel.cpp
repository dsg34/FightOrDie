/* 
 * File:   Nivel.cpp
 * Author: Dani
 * 
 * Created on 21 de abril de 2015, 9:11
 */

#include "Nivel.h"

Nivel::Nivel(int i, Protagonista* &p, sf::Vector2<int> v) {
    id=i;
    puntuacion=0;
    
    hud = new HUD(p, v);
}

Nivel::Nivel(const Nivel& orig) {
}

Nivel::~Nivel() {

}

void Nivel::controlarRacha(){//
    /*
     Si hay impacto
     *  racha++;
     *  tiempo.restart();
     else
     * if tiempo>1.5;
            reset racha;
            sumar puntuacion
     *      calcularPuntuacionDinamica();//Anyade a la puntuacion la puntuacion producida por la racha
     */
}

void Nivel::actualizarNivel(Personaje* p, int impactos, int fallos){
    
}

void Nivel::pintarNivel(sf::RenderWindow &w){
    hud->pintarHUD(w);
    //mapa->pintarMapa()
}