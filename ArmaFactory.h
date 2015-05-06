#include "Arma.h"
#ifndef ARMAFACTORY_H
#define	ARMAFACTORY_H

class ArmaFactory {
public:
    ArmaFactory();
    ArmaFactory(const ArmaFactory& orig);
    virtual ~ArmaFactory();
    
    Arma* crearPistola();
    Arma* crearMetralleta();
    Arma* crearEscopeta();
    Arma* crearHacha();
    Arma* crearGranada();
private:

};

#endif	/* ARMAFACTORY_H */

