/* 
 * File:   Zombie.cpp
 * Author: USUARIO
 * 
 * Created on 22 de abril de 2015, 16:56
 */

#include "Zombie.h"

Zombie::Zombie(sf::Sprite* s, sf::Texture* t, sf::Vector2<float> p, int mV, int ve) :Personaje(s,t,p,mV,ve) {
    sprite = new sf::Sprite(*s);    
    tex = new sf::Texture(*t);
    sprite->setTexture(*tex);
    sprite->setPosition(p);
    
    posActual = p;
    posAnterior = p;
    maxVida = mV;
    velocidad = ve;
    estaVivo = true;
    
    vida = maxVida;
    cont = 0;
    direc = 0;
    muriendo = false;
    boundingBox = new sf::FloatRect((*sprite).getGlobalBounds());
    boundingBox->width -= 70;
    boundingBox->left += 35;
}
Zombie::Zombie(const Zombie& orig) : Personaje(orig){
}

Zombie::~Zombie() {
}
void Zombie::update(sf::Sprite protagonista , std::vector<Zombie*> zombies, std::vector<Arma*> armas){
    posAnterior=posActual;
    *boundingBox = sprite->getGlobalBounds();
    boundingBox->width -= 70;
    boundingBox->left += 30;
    
    
    bool ejey = false;
    bool ejex = true;
    
    float equis = 0;
    float y = 0;
    
    
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
    char direccion;
    if(equis>0 &&(y==0||y>0))
        direccion = 'D';
    else if(y>0 &&(equis==0||equis<0))
        direccion = 'S';
    else if(equis<0&&(y==0||y<0))
        direccion = 'A';
    else
        direccion = 'W';
    
    if(colisionConProta(protagonista, direccion)==false && colisionConZombies(zombies, direccion)==false)
        sprite->move(equis,y);
    
    colisionConBalas(armas);
    posActual = sprite->getPosition();
}
bool Zombie::colisionConProta(sf::Sprite spriteProta, char direccion){
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
        //std::cout << sizeof(p);
        
        sf::FloatRect cajaProta = spriteProta.getGlobalBounds();
        if(box->intersects(cajaProta)){
            return true;
        }        
        return false;
}
bool Zombie::colisionConZombies(std::vector<Zombie*> zombies, char direccion)
{
    /*
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
           if(box->intersects(*cajaZ) && sprite->getPosition()!=zombies[i]->getSprite()->getPosition())
           {
               //sprite->move(1.0f, 0);
               //zombies[i]->mover(-1, 0);
               return true; 
           }
        }
      */
        return false;
}
bool Zombie::colisionConBalas(std::vector<Arma*> armas){
    //sf::Sprite* spriteCopia = new sf::Sprite(*sprite);
    //sf::FloatRect* box = new sf::FloatRect(boundingBox);
    
    for(int j=0; j<armas.size();j++){
        std::vector<Proyectil*> cargador = armas[j]->getCargador();
        for(int i=0; i<cargador.size();i++){
            if(boundingBox->intersects(cargador[i]->getSprite()->getGlobalBounds())){
                //std::cout<<"Impacto!"<<std::endl;
                armas[j]->eliminarProyectil(i);
                std::cout<<"Elimino"<<std::endl;
                recibirDanyo(armas[j]->getDanyo());
                if(vida<=0){
                    muriendo=true;
                    muere();
                    //std::cout<<"Palmé"<<std::endl;
                    //std::cout<<estaVivo<<std::endl;
                }
                return true;
            }
        }
    } 
    return false;
}
bool Zombie::colisionConGranadas(Arma* armaActual){
    std::vector<Granada*> granadas = armaActual->getSecundaria();
    for(int i=0; i<granadas.size(); i++){
        if(boundingBox->intersects(granadas[i]->getSprite()->getGlobalBounds())/*&&granadas[i]->estaExplotando()*/){
            recibirDanyo(granadas[i]->getDanyo());
            if(vida<0){
                muriendo=true;
                muere();
                std::cout<<"Palmé"<<std::endl;
            }
        }
    }
}
void Zombie::recibirDanyo(int danyo){
    vida -= danyo;
}
void Zombie::muere(){
    sprite->setOrigin(125/2,84/2);
    sprite->setTextureRect(sf::IntRect(325+direc*125,0*74,125,74));
    cont=1;
    actualizaMuerte();
}
void Zombie::actualizaMuerte(){
    //bool muerte=true;
    sprite->setTextureRect(sf::IntRect(325+direc*125,cont*74,125,74));
    if(cont==5){
        cont=0;
        estaVivo=false;
        /*
        std::cout<<estaVivo<<std::endl;

        sprite->setOrigin(53/2,80/2);
        sprite->setTextureRect(sf::IntRect(0,direc*80,53,80));
        sprite->setPosition(256,256);*/
    }else{
        cont++;
        actualizaMuerte();
    //estaVivo=false;
    }
    
}

