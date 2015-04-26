/* 
 * File:   Oleada.h
 * Author: Dani
 *
 * Created on 21 de abril de 2015, 9:12
 */

#ifndef OLEADA_H
#define	OLEADA_H
#include <SFML/Graphics.hpp>
#include "HUD.h"

class Oleada {
public:
    Oleada(int i, int niv, int numZ, float tiempo);
    Oleada(const Oleada& orig);
    virtual ~Oleada();
    
    //void crearNuevosZombies(std::vector<Zombie*> v);
    bool actualizarZombiesMuertos(int i, HUD* &hud);//Actualiza el numero de zombies muertos
    bool terminarOleada();//Se llamará cuando el numero de zombies 
    
    int getNumZombies();
    
    Oleada* crearOleada(int i, int j);    
    
    Oleada* crearOleada11();    
    Oleada* crearOleada12();
    Oleada* crearOleada13();

    Oleada* crearOleada21();
    Oleada* crearOleada22();
    Oleada* crearOleada23();

    Oleada* crearOleada31();
    Oleada* crearOleada32();
    Oleada* crearOleada33();

private:
    int id;
    int nivel;
    
    int numZombies;
    int zombiesEliminados;
    //std::vector<Recurso*> recursos;
    
    int tiempoBonificacion;//Tiempo cada 
    
    int nIni;//Numero de zombies inicial por oleada
};

#endif	/* OLEADA_H */

