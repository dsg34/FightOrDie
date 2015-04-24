/* 
 * File:   RecursosFactory.h
 * Author: Marc
 *
 * Created on 14 de abril de 2015, 10:26
 */
#include "Recurso.h"
#ifndef RECURSOSFACTORY_H
#define	RECURSOSFACTORY_H

class RecursosFactory {
public:
    RecursosFactory();
    RecursosFactory(const RecursosFactory& orig);
    virtual ~RecursosFactory();
    Recurso* crearRecurso(int tip);
    
private:
    
    Recurso* crearBotiquin();
    Recurso* crearMunicionMetralleta();
    Recurso* crearMunicionEscopeta();
    Recurso* crearMunicionGranada();
    Recurso* crearMadera();
    Recurso* crearValla(int res);
    Recurso* crearBarril();

};

#endif	/* RECURSOSFACTORY_H */

