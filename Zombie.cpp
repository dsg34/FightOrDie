#include "Zombie.h"

Zombie::Zombie(sf::Sprite* s, sf::Texture* t, sf::Vector2<float> p, int mV, float ve, float dan) :Personaje(s,t,p,mV,ve) {
    sprite = new sf::Sprite(*s);    
    tex = new sf::Texture(*t);
    sprite->setTexture(*tex);
    sprite->setPosition(p);
    posActual = p;
    posAnterior = p;
    auxAnterior=10;
    maxVida = mV;
    velocidad = ve;
    estaVivo = true;
    danyo = dan;
    vida = maxVida;
    cont = 0;
    contA = 0;
    direc = 0;
    muriendo = false;
    atacando = false;
    boundingBox = new sf::FloatRect((*sprite).getGlobalBounds());
    boundingBox->width -= 55;
    boundingBox->left += 25;
    boundingBox->height -= 55;
    boundingBox->top += 25;
    
    esquiva = 0;
    esqDir = false;
    obsMapa = true;
    reloj.restart();
    audios = Sonidos::Instance();
    
    gordo=false;
    dominante=false;
    
    tiempoVida.restart();
}

Zombie::Zombie(const Zombie& orig) : Personaje(orig){
}

Zombie::~Zombie() {
}

int Zombie::update(sf::Sprite protagonista , std::vector<Zombie*> zombies, std::vector<Arma*> armas, std::vector<Recurso*> recursos, MapLoader* mapa, int id){
    
    equis=0;
    y=0;
    posAnterior = posActual;
    *boundingBox = sprite->getGlobalBounds();
    boundingBox->width -= 70;
    boundingBox->left += 35;
    boundingBox->height -= 70;
    boundingBox->top += 35;
    
    int ataque = 0;
    sf::Time frecuencia;
    bool pri=false;
    frecuencia=tiempoVida.getElapsedTime();
    float distX,distY;
    bool ocupado=false;
    if(frecuencia.asSeconds()>10 && pri==false && id==1){
        if(sprite->getPosition().x<0 || sprite->getPosition().x>1275 || sprite->getPosition().y<0 || sprite->getPosition().y>725){
            for(int i=0; i<zombies.size(); i++)
            { 
                distY=fabs(zombies[i]->getSprite()->getPosition().y-350);
                distX=fabs(zombies[i]->getSprite()->getPosition().x+10);
                
                if(distX<80 && distY<80)
                    ocupado=true;
            }
            if(ocupado==false){
                sprite->setPosition(-10,350);
                pri=true;
            }
        }
    }else if(frecuencia.asSeconds()>15 && pri==false && id==2){
        if(sprite->getPosition().x<0 || sprite->getPosition().x>1275 || sprite->getPosition().y<0 || sprite->getPosition().y>725){
            for(int i=0; i<zombies.size(); i++)
            { 
                distY=fabs(zombies[i]->getSprite()->getPosition().y-750);
                distX=fabs(zombies[i]->getSprite()->getPosition().x-650);

                if(distX<80 && distY<80)
                    ocupado=true;
            }
            if(ocupado==false){
                sprite->setPosition(650,750);
                pri=true;
            }
        }
    }else if(frecuencia.asSeconds()>15 && pri==false && id==3){
        if(sprite->getPosition().x<0 || sprite->getPosition().x>1275 || sprite->getPosition().y<0 || sprite->getPosition().y>725){
            for(int i=0; i<zombies.size(); i++)
            { 
                distY=fabs(zombies[i]->getSprite()->getPosition().y-750);
                distX=fabs(zombies[i]->getSprite()->getPosition().x-450);

                if(distX<80 && distY<80)
                    ocupado=true;
            }
            if(ocupado==false){
                sprite->setPosition(450,750);
                pri=true;
            }
        }
    }
    
    //obsMapa = true;
    std::vector<eleccion> direccion;
    
    if(muriendo==false){
        colisionConBalas(armas);
        colisionConGranadas(armas);
        
        if(atacando==true){        
            frecuencia = reloj.getElapsedTime();            
            if(frecuencia.asSeconds()>0.15){
                atacar();
                reloj.restart();
            }
        }else{
//            if(danyo=0.3 && gordo==false){
//                dominante = calcularDireccion(protagonista, aux);
//                gordo=true;
//            }else
//                gordo=false;
            direccion=calcularDistancia(protagonista);
            
            int decision=-1;
            int actualX;
            int actualY;
            int aux;
            posicion nueva;
            for(int i=0; i<8; i++){
                decision = colision(direccion[i].direccion, protagonista, zombies, recursos, mapa);
                aux = direccion[i].direccion;
                if(decision!=1 && decision!=11){
                    if(decision==0){
                        actualX = sprite->getPosition().x + equis;
                        actualY = sprite->getPosition().y+y;
                        
                        if(!posVisitada(actualX,actualY) && zombieEnRango(actualX,actualY,id)){
                           break;
                        }
                    }else{
                        break;
                    }
                }
            }
            if(decision==-1){
                visitadas.clear();
            }
            
            if(decision==0){
                if(danyo=0.3 && gordo==false){
                    calcularDireccion(protagonista,aux);
                    gordo=true;
                }else
                    gordo=false;
                nueva.posX = sprite->getPosition().x;
                nueva.posY = sprite->getPosition().y;
                visitadas.push_back(nueva);
                sprite->move(equis,y);
                posActual = sprite->getPosition();
            }else if(decision==2){                  //ataca a prota
                calcularDireccion(protagonista, aux);
                ataque=2;
                contA=0;
                atacando=true;
            }else if(decision==3){
                calcularDireccion(protagonista, aux);
                ataque=1;
                contA=0;
                atacando=true;
            } 
            
        }
    }else{
        frecuencia = reloj.getElapsedTime();            
        if(frecuencia.asSeconds()>0.175){
            actualizaMuerte();
            reloj.restart();
        }    
    }
    return ataque;
}


bool ordenEleccion(const eleccion& pri, const eleccion& seg){
    if(pri.distancia != seg.distancia)
        return pri.distancia < seg.distancia;
    else
        return pri.direccion < seg.direccion;
}
bool Zombie::posVisitada(int posX, int posY){
    if(visitadas.size() > 30){
        visitadas.erase(visitadas.begin());
    }
    for(int i=0;i<visitadas.size();i++){
        if((visitadas[i].posX == posX)&&(visitadas[i].posY==posY)){
            return true;
        }
    }
    return false;
}
bool Zombie::zombieEnRango(int posX, int posY, int idm){
    switch(idm){
        case 1:{
            if((posX > -80 && posX <1400) && (posY < -80 || posY > 750))
                return false; 
            break;
        }
        case 2:{
            if(posY < 0){
                if((posX>100 && posX<400) || (posX>900 && posX<1200)){
                    return true;
                }else{
                    return false;
                }
            }else if(posY > 750){
                if(posX<350 || posX>950){
                    return false;
                }
            }
            break;
        }
        case 3:{
            if(posY < 0){
                if(posX<100 || posX>500){
                    return false;
                }
            }else if(posY > 750){
                if(posX<125 || posX>675){
                    return false;
                }
            }else if(posX > 1300){
                if(posY<100 || posY>725){
                    return false;
                }
            }
         break; 
        }        
    }
    return true;
}

std::vector<eleccion> Zombie::calcularDistancia(sf::Sprite protagonista){
    /*std::vector<float> distancia;
    std::vector<float> ordenado;
    std::vector<int> resultado;
*/
    std::vector<eleccion> movimiento;

    int posZX=sprite->getPosition().x;
    int posZY=sprite->getPosition().y;
    int posPX=protagonista.getPosition().x;
    int posPY=protagonista.getPosition().y;
    
    for(int i=0; i<8; i++)
        movimiento.push_back(eleccion());
    
    movimiento[0].direccion=0;
    movimiento[0].distancia=fabs((posZX+velocidad)-posPX)+fabs(posZY-posPY);                   //Derecha y sentido horario
    movimiento[1].direccion=1;
    movimiento[1].distancia=fabs((posZX+velocidad)-posPX)+fabs((posZY+velocidad)-posPY);
    movimiento[2].direccion=2;
    movimiento[2].distancia=fabs(posZX-posPX)+fabs((posZY+velocidad)-posPY);
    movimiento[3].direccion=3;
    movimiento[3].distancia=fabs((posZX-velocidad)-posPX)+fabs((posZY+velocidad)-posPY);
    movimiento[4].direccion=4;
    movimiento[4].distancia=fabs((posZX-velocidad)-posPX)+fabs(posZY-posPY);
    movimiento[5].direccion=5;
    movimiento[5].distancia=fabs((posZX-velocidad)-posPX)+fabs((posZY-velocidad)-posPY);
    movimiento[6].direccion=6;
    movimiento[6].distancia=fabs(posZX-posPX)+fabs((posZY-velocidad)-posPY);
    movimiento[7].direccion=7;
    movimiento[7].distancia=fabs((posZX+velocidad)-posPX)+fabs((posZY-velocidad)-posPY);
    
    std::sort(movimiento.begin(), movimiento.end(), &ordenEleccion);
    
    /*
    for(int i=0; i<distancia.size(); i++){
        ordenado.push_back(distancia[i]);
    }
    
    std::sort(ordenado.begin(), ordenado.end());
    
    for(int i=0; i<ordenado.size(); i++){
        for(int j=0; j<distancia.size(); j++){
            if(ordenado[i]==distancia[j]){
                resultado.push_back(j);
                
            }
            break;
        }
    }
    */
    return movimiento;
}

int Zombie::colision(int direccion, sf::Sprite protagonista, std::vector<Zombie*> zombies, std::vector<Recurso*> recursos, MapLoader* mapa){
    int dev=6;
    if(direccion==0){
        equis=velocidad;
        y=0;
        if(!mapa->Colision(sprite->getPosition().x+velocidad, sprite->getPosition().y,1))
            dev= 1;
        else if(colisionConZombies(zombies, 'D'))
            dev= 11;
        else if(colisionConRecursos(recursos, 'D'))
            dev= 2;
        else if(colisionConProta(protagonista, 'D'))
            dev= 3;
        else 
            dev= 0;
    }else if(direccion==1){
        equis=velocidad;
        y=velocidad;
        if(!mapa->Colision(sprite->getPosition().x+velocidad, sprite->getPosition().y+velocidad,1))
            dev= 1;
        else if(colisionConZombies(zombies, 'C'))
            dev= 11;
        else if(colisionConRecursos(recursos, 'C'))
            dev= 2;
        else if(colisionConProta(protagonista, 'C'))
            dev= 3;
        else 
            dev= 0;
    }else if(direccion==2){
        equis=0;
        y=velocidad;
        if(!mapa->Colision(sprite->getPosition().x, sprite->getPosition().y+velocidad,1))
            dev= 1;
        else if(colisionConZombies(zombies, 'S'))
            dev= 11;
        else if(colisionConRecursos(recursos, 'S'))
            dev= 2;
        else if(colisionConProta(protagonista, 'S'))
            dev= 3;
        else 
            dev= 0;
    }else if(direccion==3){
        equis=-velocidad;
        y=velocidad;
        if(!mapa->Colision(sprite->getPosition().x-velocidad, sprite->getPosition().y+velocidad,1))
            dev= 1;
        else if(colisionConZombies(zombies, 'Z'))
            dev= 11;
        else if(colisionConRecursos(recursos, 'Z'))
            dev= 2;
        else if(colisionConProta(protagonista, 'Z'))
            dev= 3;
        else 
            dev= 0;
    }else if(direccion==4){
        equis=-velocidad;
        y=0;
        if(!mapa->Colision(sprite->getPosition().x-velocidad, sprite->getPosition().y,1))
            dev= 1;
        else if(colisionConZombies(zombies, 'A'))
            dev= 11;
        else if(colisionConRecursos(recursos, 'A'))
            dev= 2;
        else if(colisionConProta(protagonista, 'A'))
            dev= 3;
        else 
            dev= 0;
    }else if(direccion==5){
        equis=-velocidad;
        y=-velocidad;
        if(!mapa->Colision(sprite->getPosition().x-velocidad, sprite->getPosition().y-velocidad,1))
            dev= 1;
        else if(colisionConZombies(zombies, 'Q'))
            dev= 11;
        else if(colisionConRecursos(recursos, 'Q'))
            dev= 2;
        else if(colisionConProta(protagonista, 'Q'))
            dev= 3;
        else 
            dev= 0;
    }else if(direccion==6){
        equis=0;
        y=-velocidad;
        if(!mapa->Colision(sprite->getPosition().x, sprite->getPosition().y-velocidad,1))
            dev= 1;
        else if(colisionConZombies(zombies, 'W'))
            dev= 11;
        else if(colisionConRecursos(recursos, 'W'))
            dev= 2;
        else if(colisionConProta(protagonista, 'W'))
            dev= 3;
        else 
            dev= 0;
    }else if(direccion==7){
        equis=velocidad;
        y=-velocidad;
        if(!mapa->Colision(sprite->getPosition().x+velocidad, sprite->getPosition().y-velocidad,1))
            dev= 1;
        else if(colisionConZombies(zombies, 'E'))
            dev= 11;
        else if(colisionConRecursos(recursos, 'E'))
            dev= 2;
        else if(colisionConProta(protagonista, 'E'))
            dev= 3;
        else 
            dev= 0;
    }        
        /*default:
            equis=velocidad;
            y=0;
            if(!mapa->Colision(sprite->getPosition().x+velocidad, sprite->getPosition().y,1) || !colisionConZombies(zombies, 'D'))
                return 1;
            else if(colisionConRecursos(recursos, 'D'))
                return 2;
            else if(colisionConProta(protagonista, 'D'))
                return 3;
            else 
                return 0;
            break;*/    
    
    return dev;
}

void Zombie::calcularDireccion(sf::Sprite protagonista, int aux){
    
    if(aux==4 || aux==5)
    {

        if(direc == 0)
        {
            cont++;

            sprite->setTextureRect(sf::IntRect(cont*75, 0, 75, 75));                

            if(cont == 5)
                cont = 0;


        }
        else
        {
            direc = 0;
            cont = 0;
            sprite->setTextureRect(sf::IntRect(cont*75, 0, 75, 75));   
        }
        
    }
    else if(aux==0 || aux==1)
    {
               
        if(direc == 3)
        {
            cont++;

            sprite->setTextureRect(sf::IntRect(cont*75, 3*75, 75, 75));                

            if(cont == 5)
                cont = 0;
        }
        else
        {
            direc = 3;
            cont = 0;
            sprite->setTextureRect(sf::IntRect(cont*75, 3*75, 75, 75));   
        }
    }         

    if(aux==6 || aux==7)
    {
         if(direc == 2)
        {
            cont++;

            sprite->setTextureRect(sf::IntRect(cont*75, 2*75, 75, 75));                

            if(cont == 5)
                cont = 0;


        }
        else
        {
            direc = 2;
            cont = 0;
            sprite->setTextureRect(sf::IntRect(cont*75, 2*75, 75, 75));   
        }
    }
    else if(aux==2 || aux==3)
    {

        if(direc == 1)
        {
            cont++;

            sprite->setTextureRect(sf::IntRect(cont*75, 75, 75, 75));                

            if(cont == 5)
                cont = 0;
        }
        else
        {
            direc = 1;
            cont = 0;
            sprite->setTextureRect(sf::IntRect(cont*75, 75, 75, 75));   
        }
    }
}

/*
int Zombie::update(sf::Sprite protagonista , std::vector<Zombie*> zombies, std::vector<Arma*> armas, std::vector<Recurso*> recursos, MapLoader* mapa){
    equis=0;
    y=0;
    posAnterior = posActual;
    *boundingBox = sprite->getGlobalBounds();
    int ataque = 0;
    bool dominante = false;
    sf::Time frecuencia;
    obsMapa = true;
    boundingBox->width -= 70;
    boundingBox->left += 35;
    boundingBox->height -= 70;
    boundingBox->top += 35;
    if(muriendo==false){
        colisionConBalas(armas);
        colisionConGranadas(armas);
        
        if(atacando==true){        
            frecuencia = reloj.getElapsedTime();            
            if(frecuencia.asSeconds()>0.15){
                atacar();
                reloj.restart();
            }
        }else{
            dominante = calcularDireccion(protagonista);

            char direccion;
            if(equis>0)
                direccion = 'D';
            else if(y>0)
                direccion = 'S';
            else if(equis<0)
                direccion = 'A';
            else
                direccion = 'W';

            if(colisionConProta(protagonista, direccion)){
                ataque=1;
                contA=0;
                atacando=true;
            }else if(colisionConRecursos(recursos)){
                ataque=2;
                contA=0;
                atacando=true;
            }else{
                
                detectarObstaculos(mapa, dominante);
                if(equis>0 && y>0)
                    direccion = 'C';
                else if(equis<0 && y>0)
                    direccion = 'Z';
                else if(equis>0 && y<0)
                    direccion = 'E';
                else if(equis<0 && y<0)      
                    direccion = 'Q';
                else if(equis>0)
                    direccion = 'D';
                else if(y>0)
                    direccion = 'S';
                else if(equis<0)
                    direccion = 'A';
                else
                    direccion = 'W';
                if(obsMapa==false)
                    detectarZombie(zombies, direccion, mapa);
                else if(!colisionConZombies(zombies, direccion))
                    sprite->move(equis,y);
                
                posActual = sprite->getPosition();
            }
        }
    }else{
        frecuencia = reloj.getElapsedTime();            
        if(frecuencia.asSeconds()>0.175){
            actualizaMuerte();
            reloj.restart();
        }    
    }
    return ataque;
}
 
bool Zombie::calcularDireccion(sf::Sprite protagonista){
    
    bool ejey = false;
    bool ejex = true;
        
    int diferenciax = protagonista.getPosition().x - sprite->getPosition().x;
    diferenciax = std::abs(diferenciax);

    int diferenciay = protagonista.getPosition().y - sprite->getPosition().y;
    diferenciay = std::abs(diferenciay);

    if(diferenciay < diferenciax)
    {
        ejey = false;
        ejex = true;
    }
    else
    {
        ejey = true;
        ejex = false;
    }
    

    if(((protagonista.getPosition().x) + 10) < sprite->getPosition().x)
    {
        equis = -velocidad;

        if(ejex == true)
        {
            if(direc == 0)
            {
                cont++;

                sprite->setTextureRect(sf::IntRect(cont*75, 0, 75, 75));                

                if(cont == 5)
                    cont = 0;


            }
            else
            {
                direc = 0;
                cont = 0;
                sprite->setTextureRect(sf::IntRect(cont*75, 0, 75, 75));   
            }
        }
    }
    else if(((protagonista.getPosition().x) - 10) > sprite->getPosition().x)
    {
        equis = velocidad;

        if(ejex == true)
        {                
            if(direc == 3)
            {
                cont++;

                sprite->setTextureRect(sf::IntRect(cont*75, 3*75, 75, 75));                

                if(cont == 5)
                    cont = 0;


            }
            else
            {
                direc = 3;
                cont = 0;
                sprite->setTextureRect(sf::IntRect(cont*75, 3*75, 75, 75));   
            }
        }
    }
    else
    {
        equis = 0;            
    }          

    if((protagonista.getPosition().y + 10) < sprite->getPosition().y)
    {
        y = -velocidad;

        if(ejey == true)
        {
            if(direc == 2)
            {
                cont++;

                sprite->setTextureRect(sf::IntRect(cont*75, 2*75, 75, 75));                

                if(cont == 5)
                    cont = 0;


            }
            else
            {
                direc = 2;
                cont = 0;
                sprite->setTextureRect(sf::IntRect(cont*75, 2*75, 75, 75));   
            }
        }

    }
    else if((protagonista.getPosition().y - 10) > sprite->getPosition().y)
    {
        y = velocidad;

        if(ejey == true)
        {
            if(direc == 1)
            {
                cont++;

                sprite->setTextureRect(sf::IntRect(cont*75, 75, 75, 75));                

                if(cont == 5)
                    cont = 0;


            }
            else
            {
                direc = 1;
                cont = 0;
                sprite->setTextureRect(sf::IntRect(cont*75, 75, 75, 75));   
            }
        }
    }
    else
    {                
        y = 0;
    }
    
    return ejex;
}

void Zombie::detectarObstaculos(MapLoader* mapa, bool dominante){
    if(!mapa->Colision(sprite->getPosition().x+equis, sprite->getPosition().y+y,1)){          //no se puede mover
        if(dominante){          //horizontal
            if(mapa->Colision(sprite->getPosition().x, sprite->getPosition().y-velocidad,1) && sprite->getPosition().y>250){
                equis=0;
                y=-velocidad;
            }else if(mapa->Colision(sprite->getPosition().x, sprite->getPosition().y+velocidad,1) && sprite->getPosition().y<650){
                equis=0;
                y=velocidad;
            }
        }else{                      //vertizal
            if(mapa->Colision(sprite->getPosition().x-velocidad, sprite->getPosition().y,1) && sprite->getPosition().x>150){
                equis=-velocidad;
                y=0;
            }else if(mapa->Colision(sprite->getPosition().x+velocidad, sprite->getPosition().y,1) && sprite->getPosition().x<1150){
                equis=velocidad;
                y=0;
            }
        }
    }else
        obsMapa=false;
}

void Zombie::detectarZombie(std::vector<Zombie*> zombies, char direccion, MapLoader* mapa){
    sf::Time frecuencia;

    if(esquiva!=0){
        frecuencia = reloj.getElapsedTime();            
        if(frecuencia.asSeconds()>(5/velocidad)){
            if(esquiva==1){
                if(colisionConZombies(zombies, 'W') && !colisionConZombies(zombies, 'S'))
                    sprite->move(0,velocidad);
            }else if(esquiva==2){
                if(colisionConZombies(zombies, 'S') && !colisionConZombies(zombies, 'W'))
                    sprite->move(0,-velocidad);
            }else if(esquiva==3){
                if(colisionConZombies(zombies, 'A') && !colisionConZombies(zombies, 'D'))
                    sprite->move(velocidad,0);
            }else if(esquiva==4){
                if(colisionConZombies(zombies, 'D') && !colisionConZombies(zombies, 'A'))
                    sprite->move(-velocidad,0);
            }
            esquiva=0;
            reloj.restart();
        }else{
            if(esquiva==1){
                if(!colisionConZombies(zombies, 'W'))
                    sprite->move(equis,-velocidad);
            }else if(esquiva==2){
                if(!colisionConZombies(zombies, 'S'))
                    sprite->move(equis,velocidad);
            }else if(esquiva==3){
                if(!colisionConZombies(zombies, 'A'))
                    sprite->move(-velocidad,y);
            }else if(esquiva==4){
                if(!colisionConZombies(zombies, 'D'))
                    sprite->move(velocidad,y);
            }
        }
    }else if(!colisionConZombies(zombies, direccion)){
        sprite->move(equis,y);
    }else {
        
        if(direccion=='Q'||direccion=='Z'||direccion=='E'||direccion=='C'){
            if(direccion=='Q'){
                if(!colisionConZombies(zombies, 'A'))
                    sprite->move(-velocidad,0);
                else if(!colisionConZombies(zombies, 'W'))
                    sprite->move(0,-velocidad);
                else if(!colisionConZombies(zombies, 'Z'))
                    sprite->move(-velocidad,velocidad);
                else if(!colisionConZombies(zombies, 'S'))
                    sprite->move(0,velocidad);

            }else if(direccion=='E'){
                if(!colisionConZombies(zombies, 'D'))
                    sprite->move(velocidad,0);
                else if(!colisionConZombies(zombies, 'W'))
                    sprite->move(0,-velocidad);
                else if(!colisionConZombies(zombies, 'C'))
                    sprite->move(velocidad,velocidad);
                else if(!colisionConZombies(zombies, 'S'))
                    sprite->move(0,velocidad);
                
            }else if(direccion=='Z'){
                if(!colisionConZombies(zombies, 'A'))
                    sprite->move(-velocidad,0);
                else if(!colisionConZombies(zombies, 'S'))
                    sprite->move(0,velocidad);
                else if(!colisionConZombies(zombies, 'Q'))
                    sprite->move(-velocidad,-velocidad);
                else if(!colisionConZombies(zombies, 'W'))
                    sprite->move(0,-velocidad);

            }else{
                if(!colisionConZombies(zombies, 'D'))
                    sprite->move(velocidad,0);
                else if(!colisionConZombies(zombies, 'S'))
                    sprite->move(0,velocidad);
                else if(!colisionConZombies(zombies, 'E')) 
                    sprite->move(velocidad,-velocidad);
                else if(!colisionConZombies(zombies, 'W'))
                    sprite->move(0,-velocidad);
            }
        }else{
            reloj.restart();
            if(direccion=='W' || direccion=='S'){ 
                if(!colisionConZombies(zombies, 'A') && esqDir==false){
                    sprite->move(-velocidad,0);
                    esquiva=3;
                    esqDir=true;
                }else if(!colisionConZombies(zombies, 'D') && esqDir==true){
                    sprite->move(velocidad,0);
                    esquiva=4;
                    esqDir=false;
                }else if(!colisionConZombies(zombies, 'A')){
                    sprite->move(-velocidad,0);
                    esquiva=3;
                }else if(!colisionConZombies(zombies, 'D')){
                    sprite->move(velocidad,0);
                    esquiva=4;
                }
            }else {
                if(!colisionConZombies(zombies, 'W') && esqDir==false){
                    sprite->move(0,-velocidad);
                    esquiva=1;
                    esqDir=true;
                }else if(!colisionConZombies(zombies, 'S') && esqDir==true){
                    sprite->move(0,velocidad);
                    esquiva=2;
                    esqDir=false;
                }else if(!colisionConZombies(zombies, 'W')){
                    sprite->move(0,-velocidad);
                    esquiva=1;
                }else if(!colisionConZombies(zombies, 'S')){
                    sprite->move(0,velocidad);
                    esquiva=2;
                } 
            }
        }
    }
}*/
bool Zombie::colisionConProta(sf::Sprite spriteProta, char direccion){
    
    sf::Sprite* spriteCopia = new sf::Sprite(*sprite);
    spriteCopia->setTexture(*tex);

    if(direccion == 'S')
        spriteCopia->move(0, velocidad);
    else if(direccion == 'W')
        spriteCopia->move(0,-velocidad);
    else if(direccion == 'D')
        spriteCopia->move(velocidad, 0);
    else
        spriteCopia->move(-velocidad, 0);


    sf::FloatRect* box = new sf::FloatRect(spriteCopia->getGlobalBounds());
    box->width -= 70;
    box->left += 40;
    boundingBox->height -= 70;
    boundingBox->top += 35;
    sf::FloatRect cajaProta = spriteProta.getGlobalBounds();
    if(box->intersects(cajaProta)){
        return true;
    }        
    return false;
}

bool Zombie::colisionConZombies(std::vector<Zombie*> zombies, char direccion){
    
    sf::Sprite* spriteCopia = new sf::Sprite(*sprite);
    spriteCopia->setTexture(*tex);
    sf::FloatRect* box = new sf::FloatRect(spriteCopia->getGlobalBounds());
    sf::FloatRect* cajaZ;
    if(direccion == 'C')
        spriteCopia->move(velocidad, velocidad);
    else if(direccion == 'Z')
        spriteCopia->move(-velocidad, velocidad);
    else if(direccion == 'E')
        spriteCopia->move(velocidad, -velocidad);
    else if(direccion == 'Q')
        spriteCopia->move(-velocidad, -velocidad);
    else if(direccion == 'D')
        spriteCopia->move(velocidad, 0);
    else if(direccion == 'S')
        spriteCopia->move(0, velocidad);
    else if(direccion == 'A')
        spriteCopia->move(-velocidad, 0);
    else 
        spriteCopia->move(0, -velocidad);

    for(int i=0; i<zombies.size(); i++){
       cajaZ = zombies[i]->getBoundingBox();
       if(box->intersects(*cajaZ) && sprite->getPosition()!=zombies[i]->getSprite()->getPosition()){
            if(direccion == 'D'){
                if(spriteCopia->getPosition().x > zombies[i]->getSprite()->getPosition().x)
                    return false;
            }else if(direccion == 'S'){
                if(spriteCopia->getPosition().y > zombies[i]->getSprite()->getPosition().y)
                    return false;
            }else if(direccion == 'A'){
                if(spriteCopia->getPosition().x < zombies[i]->getSprite()->getPosition().x)
                    return false;
            }else{
                if(spriteCopia->getPosition().y < zombies[i]->getSprite()->getPosition().y)
                    return false;
            }
            return true; 
       }
    }
    return false;
}
bool Zombie::colisionConBalas(std::vector<Arma*> armas){
    if(muriendo==false){
        for(int j=0; j<armas.size();j++){
            std::vector<Proyectil*> cargador = armas[j]->getCargador();
            for(int i=0; i<cargador.size();i++){
                if(boundingBox->intersects(cargador[i]->getSprite()->getGlobalBounds())){
                    armas[j]->eliminarProyectil(i);
                    recibirDanyo(armas[j]->getDanyo());
                    if(vida<=0){
                        muere();
                    }
                    return true;
                }
            }
        } 
    }
    return false;
}
bool Zombie::colisionConRecursos(std::vector<Recurso*> &recursos, char direccion)
{
    sf::Sprite* spriteCopia = new sf::Sprite(*sprite);
    spriteCopia->setTexture(*tex);
    sf::FloatRect* box = new sf::FloatRect(spriteCopia->getGlobalBounds());
    sf::FloatRect* cajaZ;
    if(direccion == 'C')
        spriteCopia->move(velocidad, velocidad);
    else if(direccion == 'Z')
        spriteCopia->move(-velocidad, velocidad);
    else if(direccion == 'E')
        spriteCopia->move(velocidad, -velocidad);
    else if(direccion == 'Q')
        spriteCopia->move(-velocidad, -velocidad);
    else if(direccion == 'D'){
        spriteCopia->move(velocidad, 0);
    }else if(direccion == 'S')
        spriteCopia->move(0, velocidad);
    else if(direccion == 'A')
        spriteCopia->move(-velocidad, 0);
    else 
        spriteCopia->move(0, -velocidad);

    //Recurso* r;
    for(int i=0;i<recursos.size();i++){
        if(boundingBox->intersects(recursos[i]->getSprite()->getGlobalBounds())){
            if(recursos[i]->getBloqueante()==1){
                recursos[i]->setResistencia(recursos[i]->getResistencia()-danyo);
                if(recursos[i]->getResistencia()<=0){
                    recursos[i]->setBloqueante(0);
                    recursos[i]->setExiste(0);
                }
                    
                return true;
            }
        }
    }
    return false;
}
/*
bool Zombie::colisionConRecursos(std::vector<Recurso*> &recursos)
{
    //Recurso* r;
    for(int i = recursos.size() - 1 ;i >= 0; i--)
    {
        if(boundingBox->intersects(*recursos[i]->getBoundingBox()))
        {
            if(recursos[i]->getBloqueante()){
                return true;
            }
        }
    }
    return false;
}
*/
bool Zombie::colisionConGranadas(std::vector<Arma*> armas){
    if(muriendo==false){
        for(int j=0; j<armas.size();j++){
            std::vector<Granada*> granadas = armas[j]->getSecundaria();
            for(int i=0; i<granadas.size(); i++){
                if(boundingBox->intersects(granadas[i]->getSprite()->getGlobalBounds()) && granadas[i]->estaExplotando()){
                    recibirDanyo(granadas[i]->getDanyo());
                    if(vida<=0){
                        muere();
                    }
                    return true;
                }
            }
        }
    }
    return false;
}
void Zombie::recibirDanyo(int danyo){
    vida -= danyo;
}

float Zombie::getDanyo(){
    return danyo;
}

bool Zombie::getEstado(){
    return estaVivo;
}

void Zombie::atacar(){
    sprite->setTextureRect(sf::IntRect(contA*75,300+direc*75,75,75));
    contA++;
    if(contA==5){
        atacando=false;
        cont=0;
        //audios->ataqueZombie.setVolume(50);
        audios->ataqueZombie.play();
    }
}

void Zombie::actualizaMuerte(){
    sprite->setTextureRect(sf::IntRect(450+direc*75,cont*75,75,75));
    if(cont==5)
        estaVivo=false;
    
    cont++;
}

void Zombie::muere(){
    sprite->setOrigin(75/2,75/2);
    sprite->setTextureRect(sf::IntRect(450+direc*75,0,75,75));
    sprite->setPosition(sprite->getPosition().x,sprite->getPosition().y+75/3);
    cont=1;
    muriendo=true;
}
