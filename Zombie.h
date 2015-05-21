#ifndef ZOMBIE_H
#define	ZOMBIE_H

#include "Personaje.h"
#include "Arma.h"
#include "MapLoader.h"
#include "Recurso.h"
#include "Sonidos.h"

//#include "Protagonista.h"
struct eleccion{
    int direccion;
    float distancia;
};
struct posicion{
    int posX;
    int posY;
};

class Zombie: public Personaje {

public:
    
    Zombie(sf::Sprite* s, sf::Texture* t, sf::Vector2<float> p, int mV, float ve, float dan);
    Zombie(const Zombie& orig);
    virtual ~Zombie();
    
    int update(sf::Sprite protagonista, std::vector<Zombie*> zombies, std::vector<Arma*> armas, std::vector<Recurso*> recursos, MapLoader* mapa, int id);
    std::vector<eleccion> calcularDistancia(sf::Sprite protagonista);
    int colision(int direccion, sf::Sprite protagonista, std::vector<Zombie*> zombies, std::vector<Recurso*> recursos, MapLoader* mapa);
    void calcularDireccion(sf::Sprite protagonista, int aux);
    //bool ordenEleccion(eleccion const& pri, eleccion const& seg);

    //bool calcularDireccion(sf::Sprite protagonista);
    //void detectarObstaculos(MapLoader* mapa, bool dominante);
    //void detectarZombie(std::vector<Zombie*> zombies, char direccion, MapLoader* mapa);

    bool colisionConProta(sf::Sprite protagonista, char direccion);
    bool colisionConZombies(std::vector<Zombie*> zombies, char direccion);
    bool colisionConBalas(std::vector<Arma*> armas);
    bool colisionConGranadas(std::vector<Arma*> armas);
    void recibirDanyo(int danyo);
    void muere();
    bool posVisitada(int posX, int posY);
    bool zombieEnRango(int posX, int posY, int idm);
    void actualizaMuerte();
    void atacar();
    bool colisionConRecursos(std::vector<Recurso*> &recursos, char direccion);
        //bool colisionConRecursos(std::vector<Recurso*> &recursos);

    float getDanyo();
    bool getEstado();

    //bool Colision(Protagonista player);
private:
    float equis;
    float y;
    bool atacando;
    float danyo;
    sf::Clock reloj;
    sf::Clock tiempoVida;
    int contA;
    int esquiva;
    std::vector<posicion> visitadas;
    /*int anteriorY;
    int anteriorX;
    int antREY;
    int antREX;
    int antREREY;
    int antREREX;*/
    
    bool obsMapa;
    bool esqDir;
    Sonidos* audios;
    int auxAnterior;
    
    bool gordo;
    bool dominante;
};

#endif	/* ZOMBIE_H */

