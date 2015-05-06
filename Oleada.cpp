#include "Oleada.h"

Oleada::Oleada(int i, int niv, int numZ, float tiempo) {
    id=i;
    nivel=niv;
    numZombies=numZ;
    tiempoBonificacion=tiempo;
    zombiesEliminados=0;
    
    nIni = 10;
}

Oleada::Oleada(const Oleada& orig) {
}

Oleada::~Oleada() 
{    
    
}

int Oleada::getNumZombies(){
    return numZombies;
}

int Oleada::getId(){
    return id;
}

// 0: sigue oleada; 1: cambia oleada; 2: cambia 
int Oleada::actualizarZombiesMuertos(int i, HUD* &hud){//Actualiza el numero de zombies muertos. Autogestiona la creacion de oleadas hasta que acaba el nivel
    int estado=0;
    
    zombiesEliminados+=i;
    if(zombiesEliminados==numZombies){
        //Crear objeto MENSAJE "Oleada terminada. Puntuacion: x" y mostrar por pantalla
        hud->crearMensaje("Oleada terminada", -1, -1);
        if(terminarOleada())
            estado=2;//Nivel acabado
        else
            estado=1;//Oleada acabada
    }
    
    return estado;
}
bool Oleada::terminarOleada(){    
    bool nivelFinalizado=false;
    if(id<3){       
        nivelFinalizado=false;        
    }else{        
        nivelFinalizado=true;
    }
    
    return nivelFinalizado;
}

/********************************************************************OLEADA FACTORY***********************************************************+*/
Oleada* Oleada::crearOleada(int i, int j){
    switch(i){
        case 1:
            switch(j){
                case 1:
                {   
                    crearOleada11();
                    break;
                }
                case 2: crearOleada12();break;
                case 3: crearOleada13();break;
            }
            break;
        case 2:
            switch(j){
                case 1: crearOleada21();break;
                case 2: crearOleada22();break;
                case 3: crearOleada23();break;
            }
            break;
        case 3:
            switch(j){
                case 1: crearOleada31();break;
                case 2: crearOleada32();break;
                case 3: crearOleada33();break;
            }
            break;
    }
}

//////////////////////////////////////////////Nivel 1
Oleada* Oleada::crearOleada11(){
    Oleada* o = new Oleada(1, 1, nIni, 5);
    return o;
}

Oleada* Oleada::crearOleada12(){
    Oleada* o = new Oleada(2, 1, nIni*1.5, 4.5);
    return o;
}

Oleada* Oleada::crearOleada13(){
    Oleada* o = new Oleada(3, 1, nIni*2, 4);
    return o;
}
    
//////////////////////////////////////////////Nivel 2

Oleada* Oleada::crearOleada21(){
    Oleada* o = new Oleada(1, 2, nIni*2.5, 3.5);
    return o;
}

Oleada* Oleada::crearOleada22(){
    Oleada* o = new Oleada(2, 2, nIni*3, 3);
    return o;
}

Oleada* Oleada::crearOleada23(){
    Oleada* o = new Oleada(3, 2, nIni*3.5, 2.5);
    return o;
}
    
//////////////////////////////////////////////Nivel 3
  
Oleada* Oleada::crearOleada31(){
    Oleada* o = new Oleada(1, 1, nIni*4, 2);
    return o;
}

Oleada* Oleada::crearOleada32(){
    Oleada* o = new Oleada(1, 1, nIni*4.5, 1.5);
    return o;
}

Oleada* Oleada::crearOleada33(){
    Oleada* o = new Oleada(1, 1, nIni*5, 1);
    return o;
}
