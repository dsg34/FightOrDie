/* 
 * File:   Nivel.h
 * Author: Dani
 *
 * Created on 21 de abril de 2015, 9:11
 */
#include "MapLoader.h"
#include "Oleada.h"
#include "Proyectil.h"
#include "PersonajeFactory.h"
#ifndef NIVEL_H
#define	NIVEL_H

class Nivel {
public:
    Nivel(int i, Protagonista* &p, sf::Vector2<int> v, std::vector<int> s);
    Nivel(const Nivel& orig);
    virtual ~Nivel();
    
    /*int calcularPuntuacionTotal();
    int calcularPuntuacionDinamica();    */
    
    int devuelveTipo();
    sf::Vector2<int> devuelvePos();
    void crearZombies(int num);
    void generarZombies();
    void reducirSaludZombie(int i, Proyectil* p);
    void reducirSaludZombie(int i, int d);
    void generarRecurso();
    void actualizarRecursosExistentes();
    void actualizarNivel(Protagonista* p, int impactos, int fallos);
    void actualizarInfoBalas(int impactos, int fallos);//Debe actulizar la variable de impactos y fallos
    void controlarRacha();
    void compruebaDanyoZombie();
    
    void Nivel::pintarMapa(sf::RenderWindow &w);
    void pintarNivel(sf::RenderWindow &w);//Pinta nivel, recursos y HUD
    
private:
    int id;
    
    HUD* hud;
    MapLoader* mapa;
    
    Oleada* oleada;
    int puntuacion;
    int racha;
    //std::vector<Zombie*> zombies;
    //Mapa* mapa;
    
    sf::Clock relojZombie;
    sf::Clock relojRecurso;
    sf::Time tiempo;
    
    float tApareceZombie;
    float tApareceRecurso;
    int impactos;//Almacena los aciertos y los fallos durante la ultima racha
    int fallos;    
    int numZombies;
    
    std::vector<int> spawnsZombies;//Se debe indicar por que direcciones (izquierda 1, derecha 2, arriba 3, abajo 4) saldran los zombies
};

#endif	/* NIVEL_H */

