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
/***********************************************************************************************************GESTION DE PARTIDAS*/
void GuardarCargarPartida::guardarPartida(Nivel* n, Protagonista* p){
    std::ofstream escribirPartida;
    escribirPartida.open("data.txt");
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
    int intAux=-1;
    if(existeFichero("data.txt")){
        std::ifstream leerPartida("data.txt");
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
/***********************************************************************************************************GESTION DE PUNTUACIONES*/
void GuardarCargarPartida::guardarPuntuacion(Nivel* n, bool arcade){
    std::vector<int> v;
    std::vector<std::string> original;
    int intAux=-1, nuevaPunt=n->getPuntuacion(), pos=-1;
    if(existeFichero("data-point.txt")==false)
        inicializarPuntuaciones(); 
    std::ifstream leerPuntuaciones("data-point.txt");            
    if(existeFichero("data-point.txt")){
        //COMPROBAMOS SI LA NUEVA PUNTUACION ES MAS ALTA QUE LAS 5 QUE YA HAY EN EL NIVEL
        std::string linea;    
        int nivel=0;
        if(arcade==false)
            nivel = n->getId();
        else
            nivel = 4;
            
        int cont = 1;
        if (leerPuntuaciones.is_open())
        {
          while ( getline (leerPuntuaciones,linea))
          {
              linea=encriptado(linea);
              original.push_back(linea);
              //cout<<"Valor original: "<<linea<< "(nivel actual: "<< intAString(cont) << " - nivel buscado: " << intAString(nivel) << ")" <<endl;
              if(linea.compare(std::string("-"))!=false){
                  if(cont==nivel){
                      intAux=stringAInt(linea)+0;
                      v.push_back(intAux);
                  }                  
              }else{                 
                  cont++;
              }                            
          }
          /*cout<<endl<<endl<<"Valores a comparar: "<<endl;
          for(int i=0; i<v.size(); i++)
              cout<<"-"<<intAString(v[i])<<endl;
          
          cout<<endl;
          cout<<"Tamaño de V: "<<intAString(v.size())<<endl;*/
           leerPuntuaciones.close();
        }
        //cout<<"Tamaño de V: "<<intAString(v.size())<<endl;
        for(int i=v.size()-1; i>=0; i--){
            //cout<<"Valor anterior: "<<intAString(v[i])<< " - Valor a comparar: "<<intAString(nuevaPunt)<<endl;
            if(v[i]<nuevaPunt)
                pos=i;            
        }                 
        
        //EN CASO DE QUE ASÍ SEA, ANYADIMOS LA PUNTUACION DONDE CORRESPONDA
        if(pos>-1){            
            
            v.insert(v.begin()+pos, nuevaPunt);
            v.pop_back();            
            
            //POR ULTIMO, REESCRIBIMOS EL FICHERO
            std::ofstream escribirPartida("data-point.txt");
            int cont=1;//Llevamos la cuenta del nivel que estamos comprobando y de la iteracion que llevamos en total
            while(cont<5){
                if(cont==nivel){
                    for(int i=0; i<v.size(); i++){
                        escribirPartida<<encriptado(intAString(v[i]))<<endl;                                        
                    }
                }else{
                    for(int i=(cont-1)*6; i<(cont*5)+((cont-1)); i++){
                        escribirPartida<<encriptado(original[i])<<endl;
                    }
                }
                //Cuando llega aqui, ha escrito un nivel entero, por lo que escribimos un -
                
                escribirPartida<<encriptado(std::string("-"))<<endl;
                cont++;
            }
            escribirPartida.close();
        }
    }
}
//Devuelve un vector con las 5 mejores puntuaciones del nivel indicado
std::vector<int> GuardarCargarPartida::cargarPuntuaciones(){
    std::vector<int> v;
    
    if(existeFichero("data-point.txt")==false)
        inicializarPuntuaciones();    
        
    
    std::ifstream leerPuntuaciones("data-point.txt");
    int intAux=-1;    
    
    if(existeFichero("data-point.txt")){
        std::string linea;        
        if (leerPuntuaciones.is_open())
        {
          while ( getline (leerPuntuaciones,linea) )
          {
              linea=encriptado(linea);
            if(linea.compare(std::string("-"))!=false){
                intAux=stringAInt(linea)+0;
                v.push_back(intAux);
            }
          }
           leerPuntuaciones.close();
        }        
    }
    return v;
}

void GuardarCargarPartida::guardarPuntuacionSimple(Nivel* n){
    std::ofstream escribirPartida;
    int punt=n->getPuntuacion();
    escribirPartida.open("data-p.txt");
    if(existeFichero(std::string("data-p.txt"))){
        escribirPartida<<encriptado(intAString(punt))<<endl;        
        escribirPartida.close();
    }    
}

int GuardarCargarPartida::cargarPuntuacionSimple(){
    int v=0;
    if(existeFichero("data-p.txt")){
        std::ifstream leerPartida("data-p.txt");
        std::string linea;        
        if (leerPartida.is_open())
        {
          while ( getline (leerPartida,linea) )
          {
            v=stringAInt(encriptado(linea))+0;
          }
           leerPartida.close();
        }     
    }
    return v;    
}


void GuardarCargarPartida::inicializarPuntuaciones(){
    std::ofstream inicializarPuntuaciones("data-point.txt");
    if(existeFichero(std::string("data-point.txt"))){
        
        int cont=0;
        while(cont<4){
            for(int i=0; i<5; i++)
                inicializarPuntuaciones<<encriptado(intAString(0))<<endl;
            
            inicializarPuntuaciones<<encriptado(std::string("-"))<<endl;
            cont++;
        }
        inicializarPuntuaciones.close();
    }  
}


/*************************************************************************************FUNCIONES GENERALES*/
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