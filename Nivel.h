#include "MapLoader.h"
#include "Oleada.h"
#include "RecursosFactory.h"
#include "Sonidos.h"
#include "Proyectil.h"
#include "PersonajeFactory.h"
#include "Zombie.h"

#ifndef NIVEL_H
#define	NIVEL_H

class Nivel {
public:
    Nivel(int i, Protagonista* &p, sf::Vector2<int> v, std::vector<int> s, float f);
    Nivel(const Nivel& orig);
    virtual ~Nivel();
    
    MapLoader* getMapa();
    std::vector<Recurso*> getRecursos();
    std::vector<Zombie*> getZombies();
    void addRecurso(Recurso* r);
    void elimnarRecurso(int i);
    int calcularPuntuacionTotal();
    int calcularPuntuacionDinamica();  
    int getPuntuacion();
    void setPuntuacion(int p);
    void siguienteOleadaArcade(int i);
    
    int getId();
    
    int devuelveTipo();
    int devuelveTipoRecurso();
    sf::Vector2<int> devuelvePos();
    sf::Vector2<int> creaPos();
    
    void crearZombies(int num);
    void generarZombies();
    int actualizarZombiesExistentes(Protagonista* p);
    void siguienteOleada();
    void generarRecurso();
    sf::Vector2<float> actualizarRecursosExistentes();
    bool actualizarNivel(Protagonista* p, int impactos, int fallos, sf::Vector2<int> posCursor, bool arcade);
    void actualizarInfoBalas(int impactos, int fallos);//Debe actulizar la variable de impactos y fallos
    void soltarRecurso(Protagonista* p, int tipo, sf::Vector2<int> posCursor);
    void cambiarSerrucho();
    void addRecursoBloqueante(Recurso* r);
    
    void compruebaDanyoZombie(std::vector<Proyectil*> &v);
    void crearMensaje(std::string s, int t, int i, int p);
    
    void pintarMapa(sf::RenderWindow &w, int i);
    void pintarNivel(sf::RenderWindow &w);//Pinta nivel, recursos y HUD
    
private:

    void controlarRacha(int imp);
    
    int id;
    
    HUD* hud;
    MapLoader* mapa;
    
    Oleada* oleada;
    int puntuacion;
    int racha;
    std::vector<Zombie*> zombies;
    std::vector<Recurso*> recursos;
    std::vector<Recurso*> recursosBloqueantes;
    int oleadaArcade;
    sf::Clock relojZombie;
    sf::Clock relojRecurso;
    sf::Clock relojRacha;
    sf::Clock tiempoPartida;
    sf::Time tiempo;
    sf::Clock rec;
    
    float tApareceZombie;
    float tApareceRecurso;
    int impactos;//Almacena los aciertos y los fallos durante la ultima racha
    int fallos;    
    int numZombies;
    std::vector<Granada*> explosiones;
    
    
    int posAnt1;
    int posAnt2;
    int posAnt3;
    int posAnt4;
    PersonajeFactory* fabP;
    RecursosFactory* fabR;
    std::vector<int> spawnsZombies;//Se debe indicar por que direcciones (izquierda 1, derecha 2, arriba 3, abajo 4) saldran los zombies
    Sonidos* audios;
    sf::Clock sonidosClock;
};

#endif	/* NIVEL_H */
