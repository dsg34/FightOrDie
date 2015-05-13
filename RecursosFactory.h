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
    
    sf::Texture* texturaHud;
    

};

#endif	/* RECURSOSFACTORY_H */

