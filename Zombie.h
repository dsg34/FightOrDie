#ifndef ZOMBIE_H
#define	ZOMBIE_H

#include "Personaje.h"
#include "Arma.h"
#include "MapLoader.h"
#include "Recurso.h"

//#include "Protagonista.h"

class Zombie: public Personaje {
public:
    Zombie(sf::Sprite* s, sf::Texture* t, sf::Vector2<float> p, int mV, int ve, float dan);
    Zombie(const Zombie& orig);
    virtual ~Zombie();
    
    bool update(sf::Sprite protagonista, std::vector<Zombie*> zombies, std::vector<Arma*> armas, std::vector<Recurso*> recursos, MapLoader* mapa);
    void calcularDireccion(sf::Sprite protagonista);
    void detectarObstaculos(MapLoader* mapa);
    void detectarZombie(std::vector<Zombie*> zombies, char direccion, MapLoader* mapa);

    bool colisionConProta(sf::Sprite protagonista, char direccion);
    bool colisionConZombies(std::vector<Zombie*> zombies, char direccion);
    bool colisionConBalas(std::vector<Arma*> armas);
    bool colisionConGranadas(Arma* armaActual);
    void recibirDanyo(int danyo);
    void muere();
    void actualizaMuerte();
    void atacar();
    bool colisionConRecursos(std::vector<Recurso*> recursos, char direccion);
    float getDanyo();
    bool getEstado();

    //bool Colision(Protagonista player);
private:
    float equis;
    float y;
    bool atacando;
    float danyo;
    sf::Clock reloj;;
    int contA;
    int esquiva;
    bool obsMapa;
};

#endif	/* ZOMBIE_H */

