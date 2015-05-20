#include "Arma.h"
#ifndef ARMAFACTORY_H
#define	ARMAFACTORY_H

class ArmaFactory {
public:
    
    static ArmaFactory *Instance()
    {
        if(!pinstance)
            pinstance = new ArmaFactory();
        return pinstance;
    }
    
    ArmaFactory();
    ArmaFactory(const ArmaFactory& orig);
    virtual ~ArmaFactory();
    
    Arma* crearPistola();
    Arma* crearMetralleta();
    Arma* crearEscopeta();
    Arma* crearHacha();
    Arma* crearGranada();
    ArmaFactory &operator = (const ArmaFactory & );
private:
    static ArmaFactory* pinstance;
};

#endif	/* ARMAFACTORY_H */

