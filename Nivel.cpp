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
    tiempoPartida.restart();
    
    numZombies=0;
    posAnt1=0;
    posAnt2=0;
    posAnt3=0;
    posAnt4=0;
    
    tApareceZombie=tZ;
    tApareceRecurso=15.0+rand()%15;
    
    spawnsZombies=s;
    mapa=new MapLoader();
    oleada = new Oleada(1,id,10,5);
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

Nivel::~Nivel() 
{
    delete mapa;
    delete hud;
    delete oleada;
    
    for(int i = 0; i < zombies.size(); i++)
    {
        delete zombies[i];
    }
    
    for(int i = 0; i < recursos.size(); i++)
    {
        delete recursos[i];
    }
    
}

int Nivel::getId(){
    return id;
}

std::vector<Recurso*> Nivel::getRecursos(){
    return recursos;
}

std::vector<Zombie*> Nivel::getZombies(){
    return zombies;
}

void Nivel::siguienteOleada(){
    oleada = oleada->crearOleada(id, oleada->getId()+1);
    numZombies=0;
}
    
void Nivel::addRecurso(Recurso* r){
    recursos.push_back(r);
}
    
void Nivel::elimnarRecurso(int i)
{
    Recurso* r = recursos[i];
    recursos.erase(recursos.begin()+i);
    delete r;
}
MapLoader* Nivel::getMapa(){
    return mapa;
}

void Nivel::controlarRacha(int imp){//
    
    tiempo = relojRacha.getElapsedTime();
    if(imp > 0 && racha <= 20)
    {
        racha += imp;
        relojRacha.restart();
        puntuacion += 5 * racha;
    }
    else if(tiempo.asSeconds() > 3)
    {
        relojRacha.restart();
        racha = 0;
    }        
}

bool Nivel::actualizarNivel(Protagonista* p, int impac, int fall)
{   

    bool terminado=false;
    
    impactos += impac;
    fallos += fall;
    hud->actualizarHUD(p, puntuacion);
    
    controlarRacha(impac);
    tiempo = relojZombie.getElapsedTime();
    
    if(tiempo.asSeconds()>tApareceZombie){
        generarZombies();
        relojZombie.restart();
    }
    tiempo = relojRecurso.getElapsedTime();
    actualizarRecursosExistentes();
    int estadoNivel = actualizarZombiesExistentes(p);
    //std::cout << "Segundos: " << tiempo.asSeconds()<< " - ApareceRecurso: " << tApareceRecurso << std::endl;
    if(tiempo.asSeconds()>tApareceRecurso){
        generarRecurso();
        relojRecurso.restart();
    }
    if(estadoNivel==1)
        siguienteOleada();
    else if(estadoNivel==2)
        terminado=true;
    
    return terminado;
}

int Nivel::getPuntuacion(){
    return puntuacion;
}
    
void Nivel::setPuntuacion(int p){
    puntuacion = puntuacion+p;
}

std::string floatAString(float f){
    std::string devuelve;
    
    std::stringstream aux;
    aux << f;

    aux >> devuelve;
    
    return devuelve;
}

int Nivel::calcularPuntuacionTotal()
{
    int tirosTotales = impactos + fallos;
    float porcentajeAcierto = (impactos/(float)tirosTotales) * 100;
    float puntuacion1 = 100 * porcentajeAcierto;
    std::string mensaje = "Porcentaje de acierto de tiros - " + floatAString(porcentajeAcierto) + "%";
    mensaje = mensaje+"\n"+"Puntuacion por aciertos - " + floatAString(puntuacion1);
//    crearMensaje("Porcentaje de acierto de tiros: " + floatAString(porcentajeAcierto) + "%", -1,-1);
//    crearMensaje('Puntuacion por aciertos: ' + hud->intAString(puntuacion1), -1,-1);
    puntuacion += puntuacion1;
    
    tiempo = tiempoPartida.getElapsedTime();
    
    int tiempoP = tiempo.asSeconds();
    int minutos;
    int segundos;
    
    if(tiempoP > 60)
    {
        minutos = tiempoP / 60;
        segundos = tiempoP % 60;
    }
    else
    {
        minutos = 0;
        segundos = tiempoP;
    }
    
    int puntuacion2 = 2000 - tiempoP;
    if(puntuacion2 < 0)
        puntuacion2 = 0;
    
//    crearMensaje('Tiempo de la partida: ' + hud->intAString(minutos) + ':' + hud->intAString(segundos), -1,-1);
//    crearMensaje('Puntuacion por tiempo: ' + hud->intAString(puntuacion2), -1,-1);
    
    mensaje = mensaje+"\n"+"Tiempo de la partida - " + hud->intAString(minutos) + "m " + hud->intAString(segundos) + 's';
    mensaje = mensaje+"\n"+"Puntuacion por tiempo - " + hud->intAString(puntuacion2);
    puntuacion += puntuacion2;
    mensaje = mensaje+"\n"+"Puntuacion total - " + hud->intAString(puntuacion);
    //crearMensaje('Puntuacion total: ' + hud->intAString(puntuacion1), -1,-1);
    crearMensaje(mensaje, -1, -1, 1);
    
    return 1;
}

void Nivel::crearMensaje(std::string s, int t, int i, int p){
    hud->crearMensaje(s, t, i, p);
}

void Nivel::actualizarRecursosExistentes(){
    int existe=1;
    Recurso* r;
    for(int i=0; i<recursos.size(); i++){
        recursos[i]->actualizarRecurso();
        existe = recursos[i]->getExiste();
        if(existe==0)
        {
            r = recursos[i];
            recursos.erase(recursos.begin()+(i-1));
            delete r;
        }
    }
} 

int Nivel::actualizarZombiesExistentes(Protagonista* p){
    int estadoNivel=0;
    bool zombieAtaca=false;
    int existe=true;
    
    Zombie* z;
    for(int i=0; i<zombies.size(); i++){ 
        zombieAtaca=zombies[i]->update(*(p->getSprite()), zombies, p->getArmas(), recursos, mapa);
        if(zombieAtaca==true){
            p->recibirDanyo(zombies[i]->getDanyo());
        }
        existe = zombies[i]->getEstado();
        if(existe==false)
        {
            z = zombies[i];
            zombies.erase(zombies.begin()+i);
            delete z;
            estadoNivel=oleada->actualizarZombiesMuertos(1,hud);
            //numZombies++;
        }
    }    
    return estadoNivel;
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
    
    
    return tipo;
}

sf::Vector2<int> Nivel::devuelvePos(){
    sf::Vector2<int> pos, tam=*hud->getTamPantalla();
    
    bool correcto=false;
    int lado=-1;
    while(!correcto){
        lado = 1+(int)rand() % 4;
        if(std::find(spawnsZombies.begin(), spawnsZombies.end(), lado)!=spawnsZombies.end())
            correcto=true;
    }
    
    //Genera aleatoriamente el lado en el que aparece el zombie
    
     switch(lado){
        //Por la izquierda
        case 1:     pos.x=0-tam.x/50;
                    pos.y=rand()%9;
                    if(pos.y==posAnt1)
                        pos.y+=1;
                    
                    posAnt1=pos.y;
                    pos.y=pos.y*80;    //Genera un numero aleatorio entre la posicion 0 y la maxima altura de la pantalla
                    break;
        //Por la derecha
        case 2:     pos.x=tam.x+tam.x/50;
                    pos.y=rand()%9;
                    if(pos.y==posAnt2)
                        pos.y+=1;
        
                    posAnt2=pos.y;
                    pos.y=pos.y*80;
                    break; 
        //Por arriba
        case 3:     pos.y=0-tam.y/50;
                    pos.x=rand()%9;
                    if(pos.x==posAnt3)
                        pos.x+=1;
        
                    posAnt3=pos.x;
                    pos.x=pos.x*80;
                    break;
        //Por abajo
        case 4:     pos.y=tam.y+tam.y/50;
                    pos.x=rand()%9;
                    if(pos.x==posAnt4)
                        pos.x+=1;
        
                    posAnt4=pos.x;
                    pos.x=pos.x*80;
                    break;
        //Por defecto, por la derecha            
        default:    pos.x=tam.x+tam.x/50;
                    pos.y=rand()%9;
                    if(pos.y==posAnt2)
                        pos.y+=1;
        
                    posAnt2=pos.y;
                    pos.y=pos.y*80;
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

        tipo=devuelveTipo();
        aux = fab->crearZombie(tipo, v);
        zombies.push_back(aux);
        numZombies++;
    }
}

//Controlamos el numero de zombies que generamos, dependiendo de los que ya hay en pantalla

void Nivel::generarZombies(){
    //cout<<"Zombies muertos: "<<numZombies<< " de un total de "<<oleada->getNumZombies()<<endl;
    if(numZombies<oleada->getNumZombies()){
        if(zombies.size()<20)
        {            
            if(oleada->getNumZombies()-numZombies>=2)
                crearZombies(2);
            else
                crearZombies(oleada->getNumZombies()-numZombies);
        }
    }
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

//Separamos mapa y nivel porque lo primero que se ha de pintar es el mapa, luego el protagonista y luego el resto del nivel
void Nivel::pintarMapa(sf::RenderWindow &w, int i){
    mapa->Draw(w,i);
}

void Nivel::pintarNivel(sf::RenderWindow &w){ 
    for(int i=0; i<zombies.size(); i++){
        sf::Vector2<float> v = zombies[i]->getSprite()->getPosition();
        //cout<<"Zombie "<< i << ": Pos en x: " <<v.x <<" - Pos en y: "<<v.y<<endl;
        zombies[i]->render(w);
    }
    for(int j=0; j<recursos.size(); j++){
        recursos[j]->pintarRecursos(w);        
    }
    pintarMapa(w,2);//map->Draw(window);
    hud->pintarHUD(w);
    //mapa->pintarMapa()
}
