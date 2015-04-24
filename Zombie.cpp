/* 
 * File:   Zombie.cpp
 * Author: USUARIO
 * 
 * Created on 22 de abril de 2015, 16:56
 */

#include "Zombie.h"

Zombie::Zombie(sf::Sprite* s, sf::Texture* t, sf::Vector2<float> p, int mV, int ve) :Personaje(s,t,p,mV,ve) {
    /*sprite = new sf::Sprite(*s);    
    tex = new sf::Texture(*t);
    sprite->setTexture(*tex);
    
    posActual = p;
    posAnterior = p;
    maxVida = mV;
    velocidad = ve;
    
    vida = maxVida;
    cont = 0;
    direc = 0;
    muriendo = false;*/
    boundingBox = new sf::FloatRect((*sprite).getGlobalBounds());
    boundingBox->width -= 70;
    boundingBox->left += 35;
    std::cout<<boundingBox->width<<std::endl;
}
Zombie::Zombie(const Zombie& orig) : Personaje(orig){
}

Zombie::~Zombie() {
}
void Zombie::update(sf::Sprite protagonista){
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

                sprite->setTextureRect(sf::IntRect(cont*53, 0, 53, 80));                

                if(cont == 5)
                    cont = 0;

            }
            else
            {
                direc = 0;
                cont = 0;

                sprite->setTextureRect(sf::IntRect(cont*53, 0, 53, 80));   
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

                sprite->setTextureRect(sf::IntRect(cont*53, 3*80, 53, 80));                

                if(cont == 5)
                    cont = 0;

            }
            else
            {
                direc = 3;
                cont = 0;

                sprite->setTextureRect(sf::IntRect(cont*53, 3*80, 53, 80));   
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

                sprite->setTextureRect(sf::IntRect(cont*53, 2*81, 53, 78));                

                if(cont == 5)
                    cont = 0;

            }
            else
            {
                direc = 2;
                cont = 0;

                sprite->setTextureRect(sf::IntRect(cont*53, 2*81, 53, 78));   
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

                sprite->setTextureRect(sf::IntRect(cont*53, 80, 53, 80));                

                if(cont == 5)
                    cont = 0;

            }
            else
            {
                direc = 1;
                cont = 0;

                sprite->setTextureRect(sf::IntRect(cont*53, 80, 53, 80));   
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
    
    if(colisionConProta(protagonista, direccion)==false)
        sprite->move(equis,y);
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

