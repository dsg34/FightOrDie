/* 
 * File:   Nivel.cpp
 * Author: Dani
 * 
 * Created on 21 de abril de 2015, 9:11
 */
using namespace std;
#include "Nivel.h"

Nivel::Nivel(int i, Protagonista* &p, sf::Vector2<int> t, std::vector<int> s, float tZ) {

    id=i;
    puntuacion=0;
    racha = 0;
    hud = new HUD(p, t);
    
    relojZombie.restart();
    relojRecurso.restart();   
    relojRacha.restart();
    
    tApareceZombie=tZ;
    tApareceRecurso=15.0+rand()%15;
    
    spawnsZombies=s;
    mapa=new MapLoader();
    std::string niv;
    if(id==1)
        niv = "resources/nivel1.tmx";
    else if(id==2)
        niv = "resources/nivel2.tmx";
    else if(id==3)
        niv = "resources/nivel3.tmx";
    
    mapa->LoadFromFile(niv);
}

Nivel::Nivel(const Nivel& orig) {
}

Nivel::~Nivel() {

}

std::vector<Recurso*> Nivel::getRecursos(){
    return recursos;
}

std::vector<Zombie*> Nivel::getZombies(){
    return zombies;
}
    
void Nivel::addRecurso(Recurso* r){
    recursos.push_back(r);
}
    
void Nivel::elimnarRecurso(int i){
    recursos.erase(recursos.begin()+i);
}


void Nivel::controlarRacha(int imp){//
    /*
     Si hay impacto
     *  racha++;
     *  tiempo.restart();
     else
     * if tiempo>1.5;
            reset racha;
            sumar puntuacion
     *      calcularPuntuacionDinamica();//Anyade a la puntuacion la puntuacion producida por la racha
     */
    tiempo = relojRacha.getElapsedTime();
    if(imp > 0)
    {
        racha += imp;
        relojRacha.restart();
    }
    else if(tiempo.asSeconds() > 3)
    {
        relojRacha.restart();
        racha = 0;
    }
    
    puntuacion += 10 * racha;
    
}

bool Nivel::actualizarNivel(Protagonista* p, int impac, int fall)
{   
    impactos = impac;
    fallos = fall;
    hud->actualizarHUD(p, puntuacion);
    controlarRacha(impac);
    tiempo = relojZombie.getElapsedTime();
    if(tiempo.asSeconds()>tApareceZombie){
        generarZombies();
        relojZombie.restart();
    }
    tiempo = relojRecurso.getElapsedTime();
    actualizarRecursosExistentes();
    bool terminado = actualizarZombiesExistentes(p);
    //std::cout << "Segundos: " << tiempo.asSeconds()<< " - ApareceRecurso: " << tApareceRecurso << std::endl;
    if(tiempo.asSeconds()>tApareceRecurso){
        generarRecurso();
        relojRecurso.restart();
    }
    
    return terminado;
}

void Nivel::crearMensaje(std::string s, int t, int i){
    hud->crearMensaje(s, t, i);
}

void Nivel::actualizarRecursosExistentes(){
    int existe=1;
    for(int i=0; i<recursos.size(); i++){
        recursos[i]->actualizarRecurso();
        existe = recursos[i]->getExiste();
        if(existe==0){
            recursos.erase(recursos.begin()+i);
            i--;
        }
    }
} 

bool Nivel::actualizarZombiesExistentes(Protagonista* p){
    bool nivelTerminado=false;
    int existe=true;
    for(int i=0; i<zombies.size(); i++){ 
        zombies[i]->update(*(p->getSprite()), zombies);
        existe = zombies[i]->Existe();
        if(existe==false){
            zombies.erase(zombies.begin()+i);
            i--;
            nivelTerminado=oleada->actualizarZombiesMuertos(1,hud);
        }
    }    
    return nivelTerminado;
} 

int Nivel::devuelveTipo(){
    int tipo;
    int val =  rand()% 100;
    if (val < 10)       //  10% de posibilidades
        tipo = 3;//Zombie gordo
    else if (val < 30)  //  20% de posibilidades
        tipo = 2;//Zombie rapido
    else  //  70% de posibilidades
        tipo = 1;//Zombie normal  
    
    tipo = 1;
    
    return tipo;
}

sf::Vector2<int> Nivel::devuelvePos(){
    sf::Vector2<int> pos, tam=*hud->getTamPantalla();
    int lado = (int)rand() % spawnsZombies.size();//Genera aleatoriamente el lado en el que aparece el zombie
    switch(lado){
        //Por la izquierda
        case 1:     pos.x=0-tam.x/15;
                    pos.y=(int)rand()%tam.y;    //Genera un numero aleatorio entre la posicion 0 y la maxima altura de la pantalla
                    break;
        //Por la derecha
        case 2:     pos.x=tam.x+tam.x%15;
                    pos.y=(int)rand()%tam.y;
                    break; 
        //Por arriba
        case 3:     pos.x=(int)rand()%tam.x;
                    pos.y=0-tam.y/15;                    
                    break;             
        //Por abajo
        case 4:     pos.x=(int)rand()%tam.x;
                    pos.y=tam.y+tam.y/15;                    
                    break;
        //Por defecto, por la derecha            
        default:    pos.x=tam.x+tam.x%15;
                    pos.y=(int)rand()%tam.y;
                    break;
    }
    
    
    
    return pos;
}

void Nivel::crearZombies(int num){
    sf::Vector2<int> pos;
    int tipo;
    Zombie* aux;
    PersonajeFactory* fab = new PersonajeFactory();
    for(int i=0; i<num; i++){
        pos=devuelvePos();
        sf::Vector2<float> v;
        v.x = (float) pos.x;
        v.y = (float) pos.y;
        //cout<<"Pos en x: "<<v.x <<" - Pos en y: "<<v.y<<endl;
        tipo=devuelveTipo();
        aux = fab->crearZombie(tipo, v);
        zombies.push_back(aux);
    }
}

//Controlamos el numero de zombies que generamos, dependiendo de los que ya hay en pantalla

void Nivel::generarZombies(){
    if(zombies.size()>20)
        crearZombies(5);
    else
        crearZombies(10);
}


void Nivel::generarRecurso(){
    int tipo = 2 + rand()%6;
    RecursosFactory* fab = new RecursosFactory();
    
    Recurso* r = fab->crearRecurso(tipo);
    while(mapa->Colision((int)r->getVectorActual().x, (int)r->getVectorActual().y, 0)==false)
        r = fab->crearRecurso(tipo);
    //if(map->Colision(sprite.getPosition().x,(sprite.getPosition().y - kVel + 75/2))){    
    recursos.push_back(r);
    
    tApareceRecurso = 15.0 + rand()%15;
}

//ESTOS TRES METODOS SON INUTILES A PRIORI
/*
void Nivel::reducirSaludZombie(int i, Granada* g){
    int estado = g->getEstado();
    if(estado==1){
        int d = g->getDanyo();
        reducirSaludZombie(i, d);
    }
}
void Nivel::reducirSaludZombie(int i, Proyectil* p){
    int d = p->getDanyo();
    reducirSaludZombie(i, d);
}
void Nivel::reducirSaludZombie(int i, Proyectil* p){
    bool muerto=false;
    int d = p->getDanyo();
    reducirSaludZombie(i, d);
}*/

/*
void Nivel::reducirSaludZombie(int i, int d){
    bool muerto=false;
    if(i>0 && i<zombies.size()){
        muerto = zombies[i]->reducirSalud(d);
        if(muerto==true){
            zombies.erase(zombies.begin()+i);
            oleada->actualizarNumZombies(1, hud);//Actualizamos el numero de zombies muertos en la oleada
        }
    }
}*/

/*METODO QUE RECIBA ARRAY DE BALAS Y COMPRUEBE PARA CADA ZOMBIE SI SE PRODUCE DANYO*/

/*void Nivel::compruebaDanyoZombie(std::vector<Proyectil*> &v,){
    for(int i=0; i<zombies.size(); i++){
        zombies[i]->calcularColisionBalas(v);
    }
}*/
//Separamos mapa y nivel porque lo primero que se ha de pintar es el mapa, luego el protagonista y luego el resto del nivel
void Nivel::pintarMapa(sf::RenderWindow &w, int i){
    mapa->Draw(w,i);
}

void Nivel::pintarNivel(sf::RenderWindow &w){ 
    for(int i=0; i<zombies.size(); i++){
        sf::Vector2<float> v = zombies[i]->getSprite()->getPosition();
        cout<<"Zombie "<< i << ": Pos en x: " <<v.x <<" - Pos en y: "<<v.y<<endl;
        zombies[i]->render(w);
    }
    for(int j=0; j<recursos.size(); j++){
        recursos[j]->pintarRecursos(w);        
    }
    hud->pintarHUD(w);
    //mapa->pintarMapa()
}