#include "Protagonista.h"
#include "ArmaFactory.h"
#include "Recurso.h"
#include "RecursosFactory.h"

Protagonista::Protagonista(sf::Sprite* s, sf::Texture* t, sf::Vector2<float> p, int mV, int ve) :Personaje(s,t,p,mV,ve) {

    ArmaFactory* fab = new ArmaFactory();    
    armas.push_back(fab->crearPistola());
    arma=armas[0];
    armas.push_back(fab->crearMetralleta());
    armas.push_back(fab->crearEscopeta());
    armas.push_back(fab->crearHacha());
    
    tex = new sf::Texture(*t);
    sprite = new sf::Sprite(*s);
    sprite->setTexture(*tex);
    sprite->setPosition(p);
    
    posActual = p;
    posAnterior = p;
    maxVida = mV;
    velocidad = ve;
    estaVivo = true;
    municionSecundaria = 5;
    
    vida = maxVida;
    cont = 0;
    direc = 0;
    muriendo = false;    
    boundingBox = new sf::FloatRect((*sprite).getGlobalBounds());
    boundingBox->width -= 70;
    boundingBox->left += 30;
    delete fab;
    inventario = std::vector<Recurso*>();
    
    relojCambioArma.restart();
}

Protagonista::Protagonista(const Protagonista& orig) : Personaje(orig) {
}

Protagonista::~Protagonista() 
{
    delete arma;
    
    for(int i = 0; i < armas.size(); i++)
    {
        delete armas[i];
    }
    
    int municionSecundaria;
    
    for(int i = 0; i < inventario.size(); i++)
    {
        delete inventario[i];
    }
}
void Protagonista::setPosMira(sf::Vector2<int> pos){
    posmira = pos;
}
Arma* Protagonista::getArma(){
    return arma;
}

void Protagonista::disparar(sf::Vector2<int> posicionCursor){
    if(arma->getMunicion()<=0){
        if(arma->getTipo()==1 || arma->getTipo()==4)
            arma->setMunicion(5000);
        else
            siguienteArma();
    }else
        arma->disparar(sprite->getPosition(), posicionCursor);
}
void Protagonista::dispararSecundaria(sf::Vector2<int> posicionCursor){
    if(municionSecundaria>0)
    {
        arma->dispararSecundaria(sprite->getPosition(), posicionCursor);
        municionSecundaria--;
       
    }
}

void Protagonista::recibirRecurso(Recurso* r){
    // Escopeta=2; Botiquin=3; Metralleta=4; Barril=5; Madera=6; Granada=7; Valla=8;
    int tipo = r->getTipo();
    RecursosFactory* fab = new RecursosFactory();
    if(tipo==5 || tipo==6 || tipo==8){        
        inventario.push_back(fab->crearRecurso(tipo));  
    }else if(tipo==2 || tipo==4 || tipo==7)
    { 
        //Pistola: 1; Metralleta: 2; Escopeta: 3; Hacha: 4;
        for(int i=0; i<armas.size(); i++)
        {
            if(tipo==2 && armas[i]->getTipo()==3)//Escopeta
                armas[i]->aumentarMunicion(50);
            else if(tipo==4 && armas[i]->getTipo()==2)//Metralleta
                armas[i]->aumentarMunicion(100);
            /*else if(tipo==7)
            {
                armas[i]->aumentarMunicionSecundaria(3);
            }      */
        }
        if(tipo==7)
        {
            inventario.push_back(fab->crearRecurso(tipo));
            inventario.push_back(fab->crearRecurso(7));
            inventario.push_back(fab->crearRecurso(7));
            municionSecundaria += 3;
        }
    }else if(tipo ==3){
        if(vida+3>maxVida)
            vida=maxVida;
        else
            vida+=3;
    }
    delete fab;
}
std::vector<Arma*> Protagonista::getArmas(){
    return armas;
}

void Protagonista::recibirDanyo(float cant)
{
    vida -= cant;
}

//EN ESTOS DOS METODOS SE DEBE CONTROLAR EL CAMBIO DE SPRITESHEET
void Protagonista::siguienteArma(){
    
    bool encontrado=false;
    for(int i=0; i<armas.size(); i++){
        if((armas[i]->getTipo()==arma->getTipo()) && encontrado==false){
            encontrado=true;
            std::cout<<"Entra"<<std::endl; 
            if(i<armas.size()-1){                
                arma=armas[i+1];
                std::cout<<"Siguiente arma: "<< armas[i+1]->getTipo() << " = "<<arma->getTipo() <<std::endl; 
            }else
                arma=armas[0];
        }
    }
    if(arma->getMunicion()<=0){
        std::cout<<"Arma: "<<arma->getTipo()<<"Munición: "<<arma->getMunicion()<<std::endl; 
        siguienteArma();
    }else{
        std::cout<<"Fin "<<arma->getTipo()<<std::endl<<std::endl;   
    }
}

void Protagonista::anteriorArma(){
    bool encontrado=false;
    for(int i=0; i<armas.size(); i++){
        if(armas[i]->getTipo()==arma->getTipo() && encontrado==false){
            encontrado=true;
            if(i>0)
                arma=&arma[i--];
            else
                arma=&arma[armas.size()-1];
        }
    }
    if(arma->getMunicion()<=0)
        anteriorArma();
    else{
    }
}

int Protagonista::Colision(std::vector<Zombie*> zombies, char direccion){
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

        sf::FloatRect* cajaZ;
        for(int i=0; i<zombies.size(); i++){
           cajaZ = zombies[i]->getBoundingBox();
           if(box->intersects(*cajaZ))
           {
               //this->vida -= 0.2;
               
               return 1; //AQUI DEVUELVO EL DANYO QUE HAGA EL ZOMBI EN CUESTION
           }
        }
        return 0;
 }
void Protagonista::colisionConRecursos(std::vector<Recurso*> &recursos)
{
    //Recurso* r;
        for(int i = recursos.size() - 1 ;i >= 0; i--)
        {
            if(boundingBox->intersects(*recursos[i]->getBoundingBox()))
            {
                recibirRecurso(recursos[i]);
                recursos[i]->setExiste(false);
                recursos.erase(recursos.begin()+i);                
            }
        }
}

int Protagonista::update(sf::Vector2<int> pos, std::vector<Zombie*> enemigos, MapLoader* m,std::vector<Recurso*> recursos){
    posmira.x = pos.x;
    posmira.y = pos.y;
    posAnterior = sprite->getPosition();
    *boundingBox = sprite->getGlobalBounds();
    boundingBox->width -= 70;
    boundingBox->left += 30;
    
    actualizaDireccion();
    colisionConRecursos(recursos);
    int teclaX=0;
    int teclaY=0;
    float positionY = sf::Joystick::getAxisPosition(1, sf::Joystick::Y);
    float positionX = sf::Joystick::getAxisPosition(1, sf::Joystick::X);   
        
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||positionY < -20){
        teclaY=-1;
    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||positionY > 20){
        teclaY=1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||positionX < -20){
        teclaX=-1;
    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || positionX > 20){
        teclaX=1;
    }
    actualizaPerso(teclaX,teclaY, enemigos, m);  //por aqui no deberiamos pasar enemigos
    if (sf::Joystick::isButtonPressed(1,5) || sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        //miPistola->disparar(sprite.getPosition(), posicionCursor(window));
        disparar(posmira);
                        //miProtagonista->getArma()->disparar(*miProtagonista->getSprite()->getPosition(), posicionCursor(window));
    }else if (sf::Joystick::isButtonPressed(1,4) || sf::Mouse::isButtonPressed((sf::Mouse::Right))){
                        //miPistola->dispararSecundaria(sprite.getPosition(), posicionCursor(window));
        dispararSecundaria(posmira);
    }
    if(relojCambioArma.getElapsedTime().asSeconds()>0.4){//Controlamos que reciba solamente un evento cada 0.5 segundos
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Joystick::isButtonPressed(1, 3)){//Opcional CAMBIO DE ARMA CON RUEDA DE RATON
            siguienteArma();
            relojCambioArma.restart();
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Joystick::isButtonPressed(1, 2)){
            anteriorArma();
            relojCambioArma.restart();
        }        
    }
    int fallos = 0;
    for(int i=0; i<armas.size(); i++)
    {
        fallos += armas[i]->updateProyectiles();
    }
    return fallos;
}

void Protagonista::actualizaDireccion(){
    
    int miraX=posmira.x;
    int miraY=posmira.y;
    int persoX=sprite->getPosition().x;
    int persoY=sprite->getPosition().y;
        
    if((miraY>persoY-60 && miraX<persoX-25) && (miraY<persoY+60 && miraX<persoX-25)){
        direc=0;    //Izquierda
        sprite->setTextureRect(sf::IntRect(cont*75,150,75,75));
        sprite->setScale(1,1);
    }else if((miraY>persoY-60 && miraX>persoX+25) && (miraY<persoY+60 && miraX>persoX+25)){
        direc=1;    //Derecha
        sprite->setTextureRect(sf::IntRect(cont*75,150,75,75));
        sprite->setScale(-1,1);
    }else if(miraX<persoX-60 && miraY>persoY+35){
        direc=2;    //Abajo-Izda
        sprite->setTextureRect(sf::IntRect(cont*75,225,75,75));
        sprite->setScale(1,1);
    }else if((miraX>persoX-60 && miraY>persoY+35) && (miraX<persoX+60 && miraY>persoY+35)){   
        direc=3;    //Abajo
        sprite->setTextureRect(sf::IntRect(cont*75,0,75,75));
        sprite->setScale(1,1); 
    }else if(miraX>persoX+60 && miraY>persoY+35){
        direc=4;   //Abajo-der
        sprite->setTextureRect(sf::IntRect(cont*75,225,75,75));
        sprite->setScale(-1,1);
    }else if(miraX<persoX-60 && miraY<persoY-35){
        direc=5;   //Arriba-izda
        sprite->setTextureRect(sf::IntRect(cont*75,300,75,75));
        sprite->setScale(1,1);
    }else if((miraX>persoX-60 && miraY<persoY-35) && (miraX<persoX+60 && miraY<persoY+35)){
        direc=6;    //Arriba
        sprite->setTextureRect(sf::IntRect(cont*75,75,75,75));  
        sprite->setScale(1,1);
    }else if(miraX>persoX+60 && miraY<persoY-35){
        direc=7;   //Arriba-der
        sprite->setTextureRect(sf::IntRect(cont*75,300,75,75));
        sprite->setScale(-1,1);
    }    
}

void Protagonista::actualizaPerso(int teclaX, int teclaY, std::vector<Zombie*> enemigos, MapLoader* m){

        
    if (teclaY==-1){
        if(direc==0 || direc==1 || direc==5 || direc==6 || direc==7){
            cont++;
            if(cont==6)
                cont=0;
        }else{
            if(cont==0)
                cont=6;
            cont--;
        }
        if(Colision(enemigos, 'W')==0 && (m->Colision(sprite->getPosition().x, sprite->getPosition().y-velocidad, 0)))
            sprite->move(0,-velocidad);
    }else if (teclaY==1){
        if(direc==0 || direc==1 || direc==2 || direc==3 || direc==4){
            cont++;
            if(cont==6)
                cont=0;
        }else{
            if(cont==0)
                cont=6;
            cont--;
        }
        if(Colision(enemigos, 'S')==0 && (m->Colision(sprite->getPosition().x, sprite->getPosition().y+velocidad, 0)))
            sprite->move(0,velocidad);
    }

    if (teclaX==-1){
        if((teclaY==-1 && direc==2) || (teclaY==-1 && direc==7) || (teclaY==1 && direc==4) || (teclaY==1 && direc==5) || (teclaY==-1 && direc==1)|| (teclaY==1 && direc==1) || (teclaY==1 && direc==6) || (teclaY==-1 && direc==3)){
        }else{
            if(direc==0 || direc==2 || direc==3 || direc==5 || direc==6){
                cont++;
                if(cont==6)
                    cont=0;
            }else{
                if(cont==0)
                    cont=6;
                cont--;
            }   
        }
        if(Colision(enemigos, 'A')==0 && (m->Colision(sprite->getPosition().x-velocidad, sprite->getPosition().y, 0)))
            sprite->move(-velocidad,0);      
    }else if (teclaX==1){
        if((teclaY==1 && direc==2) || (teclaY==1 && direc==7) || (teclaY==-1 && direc==4) || (teclaY==-1 && direc==5) || (teclaY==-1 && direc==0)|| (teclaY==1 && direc==0) || (teclaY==1 && direc==6) || (teclaY==-1 && direc==3)){
        }else{
            if(direc==1 || direc==3 || direc==4 || direc==6 || direc==7){
                cont++;
                if(cont==6)
                    cont=0;
            }else{
                if(cont==0)
                    cont=6;
                cont--;
            }    
        }
        if(Colision(enemigos, 'D')==0 && (m->Colision(sprite->getPosition().x+velocidad, sprite->getPosition().y, 0))){
            sprite->move(velocidad,0);   
        }
    }
    posActual = sprite->getPosition();    
}

void Protagonista::pintarProtagonista(sf::RenderWindow &w){
    w.draw(*sprite);
    for(int i=0; i<armas.size(); i++)
        armas[i]->pintarProyectiles(w);
}

std::vector<Recurso*> Protagonista::getInventario(){
    return inventario;
}    
void Protagonista::setInventario(std::vector<Recurso*> i){
    inventario=i;
}

/**************************************CODIGO MANU********************************************************/
/*
bool Protagonista::actualizaMuerte(){
    bool muerte=true;
    sprite.setTextureRect(sf::IntRect(325+direc*125,cont*74,125,74));
    if(cont==5){
        cont=0;
        muerte=false;
        sprite.setOrigin(53/2,80/2);
        sprite.setTextureRect(sf::IntRect(0,direc*80,53,80));
        sprite.setPosition(256,256);
    }
    cont++;
    return muerte;
}
void zombie::muere(){
    sprite.setOrigin(125/2,84/2);
    sprite.setTextureRect(sf::IntRect(325+direc*125,0*74,125,74));
    cont=1;
}
*/
