#include "NivelFactory.h"

NivelFactory::NivelFactory() {
}

NivelFactory::NivelFactory(const NivelFactory& orig) {
}

NivelFactory::~NivelFactory() 
{
}


Nivel* NivelFactory::crearNivel(int i, Protagonista* p, sf::Vector2<int> t){
    switch(i){
        case 1: crearNivel1(p, t);break;
        case 2: crearNivel2(p, t);break;
        case 3: crearNivel3(p, t);break;
    }
}
    
Nivel* NivelFactory::crearNivel1(Protagonista* p, sf::Vector2<int> t){
    std::vector<int> s;
    s.push_back(1);
    s.push_back(2);
    
    float tz=6.0;    
    Nivel* n = new Nivel(1, p, t, s, tz);
    
    return n;
}

Nivel* NivelFactory::crearNivel2(Protagonista* p, sf::Vector2<int> t){
    std::vector<int> s;

    s.push_back(3);
    s.push_back(4);
    s.push_back(5);
    
    float tz=4.0;
    
    Nivel* n = new Nivel(2, p, t, s, tz);
    
    return n;
}

Nivel* NivelFactory::crearNivel3(Protagonista* p, sf::Vector2<int> t){
    std::vector<int> s;
    s.push_back(2);
    s.push_back(3);
    s.push_back(6);
    
    float tz=2.0;
    
    Nivel* n = new Nivel(3, p, t, s, tz);
    
    return n;
}
