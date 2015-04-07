/* 
 * File:   ArmaFactory.h
 * Author: Dani
 *
 * Created on 7 de abril de 2015, 15:36
 */

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
private:

};

#endif	/* ARMAFACTORY_H */

