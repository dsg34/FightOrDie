/* 
 * File:   GuardarCargarPartida.cpp
 * Author: Dani
 * 
 * Created on 12 de mayo de 2015, 9:55
 */

#include "GuardarCargarPartida.h"

GuardarCargarPartida::GuardarCargarPartida() {

}

GuardarCargarPartida::GuardarCargarPartida(const GuardarCargarPartida& orig) {
}

GuardarCargarPartida::~GuardarCargarPartida() {
}

//Debe devolver: -Estado mejoras de armas (4 ints) -Nivel actual (1 int) -Oleada actual (1 int)

void GuardarCargarPartida::guardarPartida(Nivel* n, Protagonista* p){
    std::ofstream escribirPartida("data.txt");
    if(existeFichero(std::string("data.txt"))){
        //ESCRIBIMOS LAS MEJORAS DE ARMAS
        for(int i=0; i<4; i++)
            escribirPartida<<encriptado(intAString(p->getArmas()[i]->getMejora()))<<endl;
        //Escribimos el nivel actual
        escribirPartida<<encriptado(intAString(n->getId()))<<endl;
        //Escribimos la puntuacion 
        escribirPartida<<encriptado(intAString(n->getPuntuacion()))<<endl;
        
        escribirPartida.close();
    }    
}

//Debe devolver: -Estado mejoras de armas (4 ints) -Nivel actual (1 int) -Oleada actual (1 int)
std::vector<int> GuardarCargarPartida::cargarPartida(){
    std::vector<int> v;
    std::ifstream leerPartida("data.txt");
    int intAux=-1;
    if(existeFichero("data.txt")){
        std::string linea;        
        if (leerPartida.is_open())
        {
          while ( getline (leerPartida,linea) )
          {
            intAux=stringAInt(encriptado(linea))+0;
            v.push_back(intAux);
            //cout<<intAString(intAux)<<endl;
          }
           leerPartida.close();
        }        
    }
    return v;
}

bool GuardarCargarPartida::existeFichero(std::string nombre) {
    ifstream f(nombre.c_str());
    if (f.good()) {
        f.close();
        return true;
    } else {
        f.close();
        return false;
    }   
}

std::string GuardarCargarPartida::intAString(int f){
    std::string devuelve;
    
    std::stringstream aux;
    aux << f;

    aux >> devuelve;
    
    return devuelve;
}

int GuardarCargarPartida::stringAInt(std::string s){
    int devuelve;        
    std::istringstream ss(s);
    ss >> devuelve;
    
    return devuelve;
}

string GuardarCargarPartida::encriptado(string s) {
    char key = 'K'; //Any char will work
    string devuelve = s;
    
    for (int i = 0; i < s.size(); i++)
        devuelve[i] = s[i] ^ key;
    
    return devuelve;
}

/*void actualizarRanking(int niv, int p){
 
 (PARA CADA NIVEL) DEBE COMPROBAR SI LA NUEVA PUNTUACION ES MEJOR QUE LAS ANTERIORES O PEOR, Y SI ES MEJOR QUE ALGUNA DE LAS X MEJORES, INCLUIRLA
 }
 */