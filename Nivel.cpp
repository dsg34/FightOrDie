/* 
 * File:   Nivel.cpp
 * Author: Dani
 * 
 * Created on 21 de abril de 2015, 9:11
 */

#include "Nivel.h"

Nivel::Nivel(int i, Protagonista* &p, sf::Vector2<int> v, std::vector<int> s) {
    id=i;
    puntuacion=0;
    
    hud = new HUD(p, v);
    
    relojZombie.restart();
    relojRecurso.restart();        
    
    spawnsZombies=s;
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

void Nivel::actualizarNivel(Protagonista* p, int impactos, int fallos){
    hud->actualizarHUD(p, puntuacion);
    /*calcularPuntuacionDinamica();
    calcularPuntuacionDinamica();*/
    tiempo = relojZombie.getElapsedTime();
    if(tiempo.asSeconds()>tApareceZombie)
        generarZombies();
    
    tiempo = relojRecurso.getElapsedTime();
    actualizarRecursosExistentes();
    if(tiempo.asSeconds()>tApareceRecurso)
        generarRecurso();
}

void Nivel::actualizarRecursosExistentes(){
    /*bool eliminar=false;
    for(int i=0; i<recursos.size(); i++){
        eliminar = recursos[i]->getExiste();
        if(eliminar==true){
            recursos.erase(recursos.begin()+i);
            i--;
        }
    }*/
} 

int Nivel::devuelveTipo(){
    int tipo;
    double val = (double)rand() / 1;
    if (val < 0.1)       //  10% de posibilidades
        tipo = 3;//Zombie gordo
    else if (val < 0.3)  //  20% de posibilidades
        tipo = 2;//Zombie rapido
    else  //  70% de posibilidades
        tipo = 1;//Zombie delgado  
    
    return tipo;
}

sf::Vector2<int> Nivel::devuelvePos(){
    sf::Vector2<int> pos;/*, tam=hud->getTamPantalla();
    int lado = (int)rand() / spawnsZombies.size();//Genera aleatoriamente el lado en el que aparece el zombie
    switch(lado){
        //Por la izquierda
        case 1:     pos.x=0-tam.x/15;
                    pos.y=(int)rand()/tam.y;    //Genera un numero aleatorio entre la posicion 0 y la maxima altura de la pantalla
                    break;
        //Por la derecha
        case 2:     pos.x=tam.x+tam.x/15;
                    pos.y=(int)rand()/tam.y;
                    break; 
        //Por arriba
        case 3:     pos.x=(int)rand()/tam.x;
                    pos.y=0-tam.y/15;                    
                    break;             
        //Por abajo
        case 4:     pos.x=(int)rand()/tam.x;
                    pos.y=tam.y+tam.y/15;                    
                    break;
    }
    */
    
    
    return pos;
}

void Nivel::crearZombies(int num){
    sf::Vector2<int> pos;
    int tipo;
    /*Zombie* aux;
    PersonajeFactory* fab = new PersonajeFactory();
    for(int i=0; i<num; i++){
        pos=devuelvePos();
        tipo=devuelveTipo();
        aux = fab.crearZombie(tipo, pos);
        zombies.push_back(aux);
    }*/
}

//Controlamos el numero de zombies que generamos, dependiendo de los que ya hay en pantalla

void Nivel::generarZombies(){
    /*if(zombies.size()>20)
        crearZombies(5);
    else
        crearZombies(10);*/
}


void Nivel::generarRecurso(){
    /*int tipo = 2 + int rand()/6;
    RecursoFactory* fab = new RecursoFactory();
    fab->crearRecurso(tipo);
    
    tApareceRecurso = 15 + (float)rand/15;*/
}

//ESTOS TRES METODOS SON INUTILES A PRIORI
/*
void Nivel::reducirSaludZombie(int i, Granada* g){
    int estado = g->getEstado();
    if(estado==1){
        int d = g->getDanyo();
        reducirSaludZombie(i, d);
    }
}
void Nivel::reducirSaludZombie(int i, Proyectil* p){
    int d = p->getDanyo();
    reducirSaludZombie(i, d);
}
void Nivel::reducirSaludZombie(int i, Proyectil* p){
    bool muerto=false;
    int d = p->getDanyo();
    reducirSaludZombie(i, d);
}*/

void Nivel::reducirSaludZombie(int i, int d){
    bool muerto=false;
    /*if(i>0 && i<zombies.size()){
        muerto = zombies[i]->reducirSalud(d);
        if(muerto==true){
            zombies.erase(zombies.begin()+i);
            oleada->actualizarNumZombies(1, hud);//Actualizamos el numero de zombies muertos en la oleada
        }
    }*/
}

/*METODO QUE RECIBA ARRAY DE BALAS Y COMPRUEBE PARA CADA ZOMBIE SI SE PRODUCE DANYO*/

void Nivel::compruebaDanyoZombie(){
    /*for(int i=0; i<zombies.size(); i++){
        zombies[i]->calcular
    }*/
}


void Nivel::pintarNivel(sf::RenderWindow &w){    
    /*for(int i=0; i<zombies.size(); i++)
        w.draw(zombies[i]);
    
    for(int j=0; j<recurso.size(); j++)
        w.draw(recurso[i]);
      */  
    hud->pintarHUD(w);
    //mapa->pintarMapa()
}