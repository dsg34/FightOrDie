/* 
 * File:   Protagonista.cpp
 * Author: Dani
 * 
 * Created on 6 de abril de 2015, 18:31
 */

#include "Protagonista.h"

Protagonista::Protagonista(sf::Sprite* s, sf::Texture* t, Arma* a, sf::Vector2<float> p, int mV, int ve) :Personaje(s,t,p,mV,ve) {

    //this->Personaje(sf::Sprite* s, p, mV, ve);
    arma=a;
    tex = new sf::Texture(*t);
    sprite = new sf::Sprite(*s);
    sprite->setTexture(*tex);
    sprite->setPosition(p);
    posActual = p;
    posAnterior = p;
    maxVida = mV;
    velocidad = ve;
    //sprite->getTe
    
    vida = maxVida;
    cont = 0;
    direc = 0;
    muriendo = false;    
    boundingBox = new sf::FloatRect((*sprite).getGlobalBounds());
    boundingBox->width -= 70;
    boundingBox->left += 30;
}

Protagonista::Protagonista(const Protagonista& orig) : Personaje(orig) {
}

Protagonista::~Protagonista() {
}

/**************************************************METODOS GET Y SET***************************************************************/

Arma* Protagonista::getArma(){
    return arma;
}
void Protagonista::setArma(Arma* a){
    arma=a;
}

/***************************************************METODOS CUSTOM*************************************************************+*/

/*void Protagonista::update(char direccion){
    if(direccion == 'S'){
        sprite->setTextureRect(sf::IntRect(0*75, 0*75, 75, 75));
        sprite->move(0,velocidad); 
    }
    else if(direccion == 'W'){
        sprite->setTextureRect(sf::IntRect(0*75, 3*75, 75, 75));
        sprite->move(0,-velocidad); 
    }
    else if(direccion == 'D'){
        sprite->setTextureRect(sf::IntRect(0*75, 2*75, 75, 75));
        //Escala por defecto
        sprite->setScale(-1,1);
        sprite->move(velocidad,0);
    }
    else{
        sprite->setTextureRect(sf::IntRect(0*75, 2*75, 75, 75));
        //Reflejo vertical
        sprite->setScale(1,1);
        sprite->move(-velocidad,0);
    }
    
    //sprite.setTextureRect(sf::IntRect(0*75, 2*75, 75, 75));
 
    boundingBox = sprite->getGlobalBounds();
}*/
void Protagonista::disparar(sf::Vector2<int> posicionCursor){
    arma->disparar(sprite->getPosition(), posicionCursor);
}
void Protagonista::dispararSecundaria(sf::Vector2<int> posicionCursor){
    arma->dispararSecundaria(sprite->getPosition(), posicionCursor);
}

/*void Protagonista::movimientoCerebro(std::vector<Zombie*> enemigos)
{
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        posAnterior = posActual;
        sprite->move(2.5 * velocidad /2, 2.5 * velocidad /2);
        posActual = sprite->getPosition(); 
        posActual.x = posActual.x + (2.5 * velocidad / 2);
        posActual.y = posActual.y + (2.5 * velocidad/ 2);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        posAnterior = posActual;
        sprite->move( 2.5* -velocidad /2, 2.5 * velocidad /2);
        posActual = sprite->getPosition();
        posActual.x = posActual.x + (2.5 * -velocidad / 2);
        posActual.y = posActual.y + (2.5 * velocidad / 2);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        posAnterior = posActual;
        sprite->move(2.5 * -velocidad /2, 2.5 *-velocidad /2);
        posActual = sprite->getPosition();
        posActual.x = posActual.x + (2.5 * -velocidad / 2);
        posActual.y = posActual.y + (2.5 * -velocidad / 2);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        posAnterior = posActual;
        sprite->move(2.5 * velocidad /2,2.5 * -velocidad /2);
        posActual = sprite->getPosition();
        posActual.x = posActual.x + (2.5 * velocidad / 2);
        posActual.y = posActual.y + (2.5 * -velocidad / 2);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        posAnterior = posActual;
        sprite->setTextureRect(sf::IntRect(0*75, 2*75, 75, 75));
        sprite->setScale(-1,1);
        sprite->move(3 * velocidad/2,0);
        posActual = sprite->getPosition();
        posActual.x = posActual.x + (3 * velocidad / 2);
        posActual.y = posActual.y;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        posAnterior = posActual;
        sprite->setTextureRect(sf::IntRect(0*75, 0*75, 75, 75));
        sprite->move(0,3 * velocidad/2);
        posActual = sprite->getPosition();
        posActual.x = posActual.x;
        posActual.y = posActual.y + (3 * velocidad / 2);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        posAnterior = posActual;
        sprite->setTextureRect(sf::IntRect(0*75, 3*75, 75, 75));
        sprite->move(0,3 * -velocidad/2);
        posActual = sprite->getPosition();
        posActual.x = posActual.x;
        posActual.y = posActual.y + (3 * -velocidad / 2);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if(Colision(enemigos, 'A') == 0){
            posAnterior = posActual;
            sprite->setTextureRect(sf::IntRect(0*75, 2*75, 75, 75));
            sprite->setScale(1,1);
            sprite->move(3 * -velocidad/2,0);
            posActual = sprite->getPosition();
            posActual.x = posActual.x + (3 * -velocidad / 2);
            posActual.y = posActual.y;
        }
    }
    else
    {
        posActual = sprite->getPosition();
    }
}*/
int Protagonista::Colision(std::vector<Zombie*> zombies, char direccion){
        sf::Sprite* spriteCopia = new sf::Sprite(*sprite);
        spriteCopia->setTexture(*tex);
        if(direccion == 'S')
            spriteCopia->move(0, 3.0f);
        else if(direccion == 'W')
            spriteCopia->move(0,-3.0f);
        else if(direccion == 'D')
            spriteCopia->move(3.0f, 0);
        else
            spriteCopia->move(-3.0f, 0);
        
        sf::FloatRect* box = new sf::FloatRect(spriteCopia->getGlobalBounds());

        sf::FloatRect* cajaZ;
        for(int i=0; i<zombies.size(); i++){
           cajaZ = zombies[i]->getBoundingBox();
           if(box->intersects(*cajaZ)){
               return 1; //AQUI DEVUELVO EL DANYO QUE HAGA EL ZOMBI EN CUESTION
           }
        }
        return 0;
 }
////////////////////////////////////////////////////////////////////////////////METODOS DE MANU
void Protagonista::update(sf::Vector2<int> pos, std::vector<Zombie*> enemigos){

    
    *boundingBox = sprite->getGlobalBounds();
    boundingBox->width -= 70;
    boundingBox->left += 30;
    posmira.x = pos.x;
    posmira.y = pos.y;
    actualizaDireccion();
    int teclaX=0;
    int teclaY=0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        teclaY=-1;
    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        teclaY=1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        teclaX=-1;
    }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        teclaX=1;
    } 
    actualizaPerso(teclaX,teclaY, enemigos);  //por aqui no deberiamos pasar enemigos
    
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

void Protagonista::actualizaPerso(int teclaX, int teclaY, std::vector<Zombie*> enemigos){

        
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
        if(Colision(enemigos, 'W')==0)
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
        if(Colision(enemigos, 'S')==0)
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
        if(Colision(enemigos, 'A')==0)
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
        if(Colision(enemigos, 'D')==0){
            sprite->move(velocidad,0);   
        }
    }
        
}
/*void render(sf::RenderWindow &window){
    
}*/ 

/*std::Vector<Recurso*> Protagonista::getInventario(){
    return inventario;
    
1}    
void Protagonista::setInventario(std::Vector<Recurso*> i){
    inventario=i;
}
void Protagonista::anyadirAlInventario(Recurso* r){
    inventario.push_back(r);
}*
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

void zombie::actualizaSprite(int tecla){
    if(tecla==1){
        if(direc==0){
            cont++;
            sprite.setTextureRect(sf::IntRect(cont*53,0,53,80));
            if(cont==5)
                cont=0;
        }else{
            cont=0;
            direc=0;
            sprite.setTextureRect(sf::IntRect(0,0,53,80));
        }
        sprite.move(-velocidad,0);
    }else if(tecla==2){
        if(direc==3){
            cont++;
            sprite.setTextureRect(sf::IntRect(cont*53,240,53,80));
            if(cont==5)
                cont=0;
        }else{
            cont=0;
            direc=3;
            sprite.setTextureRect(sf::IntRect(cont*53,240,53,80));
        }
        sprite.move(velocidad,0);
    }else if(tecla==3){
        if(direc==1){
            cont++;
            sprite.setTextureRect(sf::IntRect(cont*53,80,53,80));
            if(cont==5)
                cont=0;
        }else{
            cont=0;
            direc=1;
            sprite.setTextureRect(sf::IntRect(cont*53,80,53,80));
        }
        sprite.move(0,velocidad);
    }else if(tecla==4){
        if(direc==2){
            cont++;
            sprite.setTextureRect(sf::IntRect(cont*53,162,53,79));
            if(cont==5)
                cont=0;
        }else{
            cont=0;
            direc=2;
            sprite.setTextureRect(sf::IntRect(cont*53,162,53,79));
        }
        sprite.move(0,-velocidad);
    }
}
sf::Sprite zombie::getSprite(){
    return sprite;
}*/