using namespace std;
#include "Nivel.h"
#include <SFML/Audio.hpp>

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
    
    fallos=0;
    impactos=0;
    
    fabR = RecursosFactory::Instance();
    fabP = PersonajeFactory::Instance();
    
    tApareceZombie=tZ;
    tApareceRecurso=4+rand()%11;
    
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
    
   audios = Sonidos::Instance();
   
   sonidosClock.restart();
    
   rec.restart();
   
   oleadaArcade=1;
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

void Nivel::siguienteOleadaArcade(int i){
    oleada = oleada->siguienteOleadaArcade(i);
    numZombies=0;
}

void Nivel::siguienteOleada(){
    oleada = oleada->crearOleada(id, oleada->getId()+1);
    numZombies=0;
}


    
void Nivel::addRecurso(Recurso* r){
    recursos.push_back(r);
}
    
void Nivel::addRecursoBloqueante(Recurso* r){
    recursosBloqueantes.push_back(r);
}

void Nivel::elimnarRecurso(int i)
{
    Recurso* r = recursos[i];
    recursos.erase(recursos.begin()+i);
    //delete r;
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

bool Nivel::actualizarNivel(Protagonista* p, int impac, int fall, sf::Vector2<int> posCursor, bool arcade)
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
    
    if(sonidosClock.getElapsedTime().asSeconds() > 15+rand()% 40)
    {
        int num = 1+rand()%8;
        
        switch(num)
        {
            case 1:
                audios->zombie1.play();
                break;
            case 2:
                audios->zombie2.play();
                break;
            case 3:
                audios->zombie3.play();
                break;
            case 4:
                audios->zombie4.play();
                break;
            case 5:
                audios->zombie5.play();
                break;
            case 6:
                audios->zombie6.play();
                break;
            case 7:
                audios->zombie7.play();
                break;
            case 8:
                audios->zombie8.play();
                break;
             
        }
        
        sonidosClock.restart();
    }
    
    tiempo = relojRecurso.getElapsedTime();
    sf::Vector2<float> gr = actualizarRecursosExistentes();
    if(gr.x!=-1 && gr.y!=-1){
        p->anyadirGranada(gr);
    }
    
    int estadoNivel = actualizarZombiesExistentes(p);
    /*if(zombies.size() > 0)
        std::cout << "update nivel " << zombies[0]->getSprite()->getPosition().x <<  std::endl;*/
    //std::cout << "Segundos: " << tiempo.asSeconds()<< " - ApareceRecurso: " << tApareceRecurso << std::endl;
    if(tiempo.asSeconds()>tApareceRecurso){
        generarRecurso();
        relojRecurso.restart();
    }
    if(estadoNivel==1)
    {
        crearMensaje("Se acerca una nueva oleada de zombies...", 40, 150, 1);   
        if(arcade==false)
            siguienteOleada();
        else{
            oleadaArcade=oleadaArcade+1;
            siguienteOleadaArcade(oleadaArcade);
        }            
    }
    else if(estadoNivel==2){
        if(arcade==false)
            terminado=true;
        else{
            oleadaArcade=oleadaArcade+1;
            siguienteOleadaArcade(oleadaArcade);            
        }
    }
    int mando = 0;
    for(int i = 0; i < 8; i++)
    {
       if(sf::Joystick::isConnected(i))
       {
           mando = i;
       }                    
    }

    if(rec.getElapsedTime().asSeconds() > 0.9)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::B) || sf::Joystick::isButtonPressed(mando, 1))
        {
            soltarRecurso(p, 2, posCursor);
        
            rec.restart();
        }
    }
    
    if(rec.getElapsedTime().asSeconds() > 0.9)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::V) || sf::Joystick::isButtonPressed(mando, 2))
        {
            soltarRecurso(p, 1, posCursor);        
        
            rec.restart();
        }
    }
    
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
    porcentajeAcierto = porcentajeAcierto * 100;
    porcentajeAcierto = round(porcentajeAcierto);
    porcentajeAcierto = porcentajeAcierto / 100;
    float puntuacion1 = 130 * porcentajeAcierto;
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

sf::Vector2<float> Nivel::actualizarRecursosExistentes(){
    int existe=1;
    Recurso* r;
    sf::Vector2<float> devuelve;
    devuelve.x=-1;
    devuelve.y=-1;
    for(int i=0; i<recursos.size(); i++){
        recursos[i]->actualizarRecurso();
        existe = recursos[i]->getExiste();
        if(existe==0 && recursos[i]->getBloqueante()==0){
            if(recursos[i]->getTipo()==5){
                devuelve = recursos[i]->getSprite()->getPosition();                
            }
            r = recursos[i];
            recursos.erase(recursos.begin()+(i));
            //delete r;
        }else if(existe==0 && recursos[i]->getBloqueante()==1){
            r = recursos[i];
            recursos.erase(recursos.begin()+(i));
        }
    }
    
    return devuelve;
}

int Nivel::actualizarZombiesExistentes(Protagonista* p){
    int estadoNivel=0;
    int zombieAtaca=0;
    int existe=true;
    int vida = 0;
    
    Zombie* z;
    for(int i=0; i<zombies.size(); i++)
    { 
        zombieAtaca=zombies[i]->update(*(p->getSprite()), zombies, p->getArmas(), recursos, mapa, id);
        if(zombieAtaca==1){
            if(p->getVida()>0){
                p->recibirDanyo(zombies[i]->getDanyo());
                p->setCont(0);
            }
        }else if(zombieAtaca==2){
            for(int j=0; j<recursos.size(); j++){ 
                vida=recursos[j]->getResistencia();
                vida=vida-zombies[i]->getDanyo();
                recursos[j]->setResistencia(vida);
                if(vida<0){
                    recursos[j]->setExiste(false);
                    //recursos.erase(recursos.begin()+j); 
                }
            }
        }

        existe = zombies[i]->getEstado();
        if(existe==false)
        {
            z = zombies[i];
            zombies.erase(zombies.begin()+i);
            //delete z;
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

int Nivel::devuelveTipoRecurso(){
    int tipo;
    //2 3 4 5 6
    
    int val =  rand()% 100;
    
    if (val<15)
        tipo=2;
    else if(val<30)
        tipo=3;
    else if(val<45)
        tipo=4;
    else if(val<60)
        tipo=5;
    else if(val<75)
        tipo=7;
    else
        tipo=6;
    
    return tipo;
}

/*
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
         case 1:    pos.x=-80;
                    pos.y=(rand()%9)*80;
                    break;
        //Por la derecha
        case 2:     pos.x=tam.x+80;
                    pos.y=(rand()%9)*80;
                    break; 
        //Por arriba
        case 3:     pos.y=-80;
                    pos.x=(rand()%17)*80;
                    break;
        //Por abajo
        case 4:     pos.y=tam.y+80;
                    pos.x=(3+(rand()%10))*80;
                    break;
        //Por defecto, por la derecha            
        default:    pos.x=tam.x+80;
                    pos.y=(rand()%9)*80;
                    break; 
    }         
    return pos;
}*/

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
         case 1:    pos.x=-80;
                    pos.y=(rand()%8)*80;
                    break;
        //Por la derecha
        case 2:     pos.x=tam.x+80;
                    pos.y=(rand()%8)*80+125;
                    break; 
        //Por arriba-izq
        case 3:     pos.y=-80;
                    pos.x=(rand()%4)*80+110;
                    break;
        //Por arriba-der
        case 4:     pos.y=-80;
                    pos.x=(rand()%4)*80+925;
                    break;
        //Por abajo          
        case 5:     pos.y=tam.y+80;
                    pos.x=(rand()%8)*80+360;
                    break;
        //Por abajo especial
        case 6:     pos.y=tam.y+80;
                    pos.x=(rand()%7)*80+150;
                    break;
                        
    }         
    return pos;
}

void Nivel::crearZombies(int num){
    sf::Vector2<int> pos;
    int tipo;
    Zombie* aux;    
    for(int i=0; i<num; i++){
        pos=creaPos();
        if(pos.x!=-1000 && pos.y!=-1000){
            sf::Vector2<float> v;

            v.x = (float) pos.x;
            v.y = (float) pos.y;

            tipo=devuelveTipo();

            if(numZombies == oleada->getNumZombies() -10 && oleada->getId()%3 == 0)
                crearMensaje("Se acerca algo fuera de lo normal...", 40, 150, 1);

            if(numZombies == oleada->getNumZombies() - 1 && oleada->getId() == 3)
            {
                tipo = 4;      
                //audios->risaBoss.setVolume(25);
                audios->risaBoss.play();
            }



            aux = fabP->crearZombie(tipo, v, id);


            if(tipo = 4)
            {
                int x = aux->getPosActual().x;
                if(x < 450)
                    x = x - 100;
                else
                    x = x + 100;

                sf::Vector2<float> v;
                v.x = x;
                v.y = aux->getPosActual().y;

                aux->setPosActual(v);
            }
            zombies.push_back(aux);
            numZombies++;
        }
    }
}

//Controlamos el numero de zombies que generamos, dependiendo de los que ya hay en pantalla

void Nivel::generarZombies(){
    //cout<<"Zombies muertos: "<<numZombies<< " de un total de "<<oleada->getNumZombies()<<endl;
    if(numZombies<oleada->getNumZombies()){
        if(zombies.size()<20)
        {            
            if(oleada->getNumZombies()-numZombies>=5)
                crearZombies(5);
            else
                crearZombies(oleada->getNumZombies()-numZombies);
        }
    }
}


void Nivel::generarRecurso(){
    int tipo = devuelveTipoRecurso();
    
    Recurso* r = fabR->crearRecurso(tipo);
    if(mapa->Colision((int)r->getVectorActual().x, (int)r->getVectorActual().y, 0)==false)
    {
        r = fabR->crearRecurso(tipo);
        tApareceRecurso = 2+rand()%5;
    }
    else
    {       
        recursos.push_back(r);

        tApareceRecurso = 4+rand()%11;
    }
}

sf::Vector2<int> Nivel::creaPos(){
    bool ocupado=false;
    sf::Vector2<int> pos;
    float distX=0;
    float distY=0;   
    ocupado=false;
    pos=devuelvePos();
    for(int i=0; i<zombies.size(); i++)
    { 
        distX=fabs(zombies[i]->getSprite()->getPosition().x-pos.x);
        distY=fabs(zombies[i]->getSprite()->getPosition().y-pos.y);

        if(distX<80 && distY<80){
            ocupado=true;
        }
    }
    if(ocupado==true){
        pos.x=-1000;
        pos.y=-1000;
    }
    return pos;
}

void Nivel::soltarRecurso(Protagonista* p, int tipo, sf::Vector2<int> posCursor){
    //RecursosFactory* fab = new RecursosFactory();
    Recurso* r;
    std::vector<Recurso*> invent = p->getInventario();
    int numRecurso=0;
    
    if(tipo==1){
        
        for(int i=0; i<invent.size(); i++){
            if(invent[i]->getTipo()==6){
                numRecurso=numRecurso+1;
            }
        }
        
        if(numRecurso>=1){
            //soltar valla
            r = fabR->crearRecurso(8);     
            r->getSprite()->setPosition(posCursor.x, posCursor.y);
            //r->getSprite()->setPosition(p->getPosActual().x+p->getSprite()->getGlobalBounds().width/2, p->getPosActual().y);
            addRecurso(r);
            p->sacarRecursoInventario(6);
        }
    }else if(tipo==2){
        for(int i=0; i<invent.size(); i++){
            if(invent[i]->getTipo()==5){
                numRecurso=numRecurso+1;
            }
        }
        if(numRecurso>=1){
            //soltar barril
            r = fabR->crearRecurso(5);
            r->getSprite()->setPosition(posCursor.x, posCursor.y);
            //r->getSprite()->setPosition(p->getPosActual().x, p->getPosActual().y);
            addRecurso(r);
            p->sacarRecursoInventario(5);
        }
    }
}

void Nivel::cambiarSerrucho()
{
    hud->cambiarHachaPorSerrucho();
}

//Separamos mapa y nivel porque lo primero que se ha de pintar es el mapa, luego el protagonista y luego el resto del nivel
void Nivel::pintarMapa(sf::RenderWindow &w, int i){
    mapa->Draw(w,i);
}


void Nivel::pintarNivel(sf::RenderWindow &w){ 
    std::vector<int> aux;   
    for(int i=0; i<zombies.size(); i++){
        aux.push_back(zombies[i]->getSprite()->getPosition().y);
    }    
    
    std::sort(aux.begin(), aux.end());
    
    
    /*for(int i=0; i<zombies.size(); i++){
        //sf::Vector2<float> v = zombies[i]->getSprite()->getPosition();
        //cout<<"Zombie "<< i << ": Pos en x: " <<v.x <<" - Pos en y: "<<v.y<<endl;
        zombies[i]->render(w);
    }*/
    
    for(int j=0; j<aux.size(); j++){
        for(int i=0; i<zombies.size(); i++){
            if(std::string(hud->intAString(aux[j])).compare(hud->intAString(zombies[i]->getSprite()->getPosition().y)) == false){
                zombies[i]->render(w);            
            }
        }
    }
            
    for(int j=0; j<recursos.size(); j++){
        recursos[j]->pintarRecursos(w);        
    }
    
    for(int j=0; j<recursosBloqueantes.size(); j++){
        recursosBloqueantes[j]->pintarRecursos(w);        
    }
    
    pintarMapa(w,2);//map->Draw(window);
    hud->pintarHUD(w);
    //mapa->pintarMapa()
}