/* 
 * File:   ArmaFactory.cpp
 * Author: Dani
 * 
 * Created on 7 de abril de 2015, 15:36
 */

#include "ArmaFactory.h"

ArmaFactory::ArmaFactory() {
}

ArmaFactory::ArmaFactory(const ArmaFactory& orig) {
}

ArmaFactory::~ArmaFactory() {
}

Arma* ArmaFactory::crearPistola(){//Se debe controlar que, al acabarse la municion de la pistola, se proporcione al usuario mas, ya que esta es infinita
    Arma* p = new Arma(1, 2, 5, 150, 2000, 0.3);
    
    return p;
}

Arma* ArmaFactory::crearMetralleta(){//Se debe controlar que, al acabarse la municion de la pistola, se proporcione al usuario mas, ya que esta es infinita
    Arma* m = new Arma(2, 1, 7, 150, 2000, 0.1);
    
    return m;
}

Arma* ArmaFactory::crearEscopeta(){//Se debe controlar que, al acabarse la municion de la pistola, se proporcione al usuario mas, ya que esta es infinita
    Arma* e = new Arma(3, 3, 5, 150, 2000, 0.7);
    
    return e;
}