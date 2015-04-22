/* 
 * File:   Nivel.h
 * Author: Dani
 *
 * Created on 21 de abril de 2015, 9:11
 */

#include "Oleada.h"
#ifndef NIVEL_H
#define	NIVEL_H

class Nivel {
public:
    Nivel(int i, Protagonista* &p, sf::Vector2<int> v);
    Nivel(const Nivel& orig);
    virtual ~Nivel();
    
    int calcularPuntuacionTotal();
    int calcularPuntuacionDinamica();    
    
    
    void actualizarNivel(Personaje* p, int impactos, int fallos);
    void actualizarInfoBalas(int impactos, int fallos);//Debe actulizar la variable de impactos y fallos
    void controlarRacha();
    
    void pintarNivel(sf::RenderWindow &w);//Pinta nivel, recursos y HUD
    
private:
    int id;
    
    HUD* hud;
    
    Oleada* oleada;
    int puntuacion;
    int racha;
    //std::vector<Zombie*> zombies;
    //Mapa* mapa;
    
    sf::Clock reloj;
    sf::Time tiempo;
    int impactos;//Almacena los aciertos y los fallos durante la ultima racha
    int fallos;    
    int numZombies;
};

#endif	/* NIVEL_H */

