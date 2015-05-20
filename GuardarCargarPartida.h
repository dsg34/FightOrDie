/* 
 * File:   GuardarCargarPartida.h
 * Author: Dani
 *
 * Created on 12 de mayo de 2015, 9:55
 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "Nivel.h"
#include "Protagonista.h"
#ifndef GUARDARCARGARPARTIDA_H
#define	GUARDARCARGARPARTIDA_H

class GuardarCargarPartida {
public:
    GuardarCargarPartida();
    GuardarCargarPartida(const GuardarCargarPartida& orig);
    virtual ~GuardarCargarPartida();
    
    void guardarPartida(Nivel* n, Protagonista* p);
    std::vector<int> cargarPartida();
    
    void guardarPuntuacion(Nivel* n, bool arcade);
    std::vector<int> cargarPuntuaciones();
    void inicializarPuntuaciones();
    void guardarPuntuacionSimple(Nivel* n);
    int cargarPuntuacionSimple();
    
    bool existeFichero(std::string nombre);
    std::string intAString(int f);
    int stringAInt(std::string s);
    
    string encriptado(string s);
    
private:
};

#endif	/* GUARDARCARGARPARTIDA_H */