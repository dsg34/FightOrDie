#include "Recurso.h"
#ifndef RECURSOSFACTORY_H
#define	RECURSOSFACTORY_H

class RecursosFactory {
public:
    
    static RecursosFactory *Instance()
    {
        if(!pinstance)
            pinstance = new RecursosFactory();
        return pinstance;
    }
    
    RecursosFactory();
    RecursosFactory(const RecursosFactory& orig);
    virtual ~RecursosFactory();
    Recurso* crearRecurso(int tip);
    
    RecursosFactory &operator = (const RecursosFactory & );
    
private:
    
    Recurso* crearBotiquin();
    Recurso* crearMunicionMetralleta();
    Recurso* crearMunicionEscopeta();
    Recurso* crearMunicionGranada();
    Recurso* crearMadera();
    Recurso* crearValla(int res);
    Recurso* crearBarril();
    
    sf::Texture* texturaHud;
    
    static RecursosFactory* pinstance;
    

};

#endif	/* RECURSOSFACTORY_H */

