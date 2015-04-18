/* 
 * File:   RecursoHUD.cpp
 * Author: Dani
 * 
 * Created on 17 de abril de 2015, 12:31
 */

#include "RecursoHUD.h"

RecursoHUD::RecursoHUD(int ti) {
    //Tipo: 1=pistola; 2=hacha; 3=metralleta; 4=escopeta; 5=barril; 6=madera; 7=valla; 8=granada
    //Tipo: 1=pistola; 2=metralleta; 3=escopeta; 4=hacha; 5=barril; 6=madera; 7=valla; 8=granada
    tipo=ti;
    num=0;
    sf::Texture texture;
    if (!texture.loadFromFile("resources/HUD.png"))
    {
    }
    //sf::Vector2<int> tam = (sf::Vector2<int>) w.getSize();
    tex=new sf::Texture(texture);
    //Configuracion sprite

    sf::Sprite aux;
    aux.setTexture(*tex);
    sprite=new sf::Sprite(aux);  
    sprite->setOrigin(75/2,75/2);
    int i=-1, j=-1;
    switch(tipo){                
        case 1: i=9; j=1; break;
        case 2: i=10; j=1; break;
        case 3: i=11; j=1; break;
        case 4: i=9; j=2; break;
        case 5: i=9; j=0; break;
        case 6: i=11; j=0; break;
        case 7: i=10; j=0; break;
        case 8: i=11; j=0; break;
        default: i=11; j=2; break;
    }
    sprite->setTextureRect(sf::IntRect(i*75, j*75, 75, 75));
    
  
    //Configuracion texto
    sf::Font font;
    if (!font.loadFromFile("fonts/ZOMBIE.ttf"))
    {
        // error...
    }    
    fuente = new sf::Font(font);
    sf::Text auxFont;
    auxFont.setFont(*fuente);
    
    //Si las armas son del tipo pistola o hacha, creamos el simbolo infinito
    if(tipo==1 || tipo==4){
        num=8;
        auxFont.setRotation(90);
        auxFont.setString(intAString(num));
    }else{
        auxFont.setString("x"+intAString(num));
    }        
    
    auxFont.setCharacterSize(35);        
    texto = new sf::Text(auxFont);
    mostrarPuntuacion=true;
}

RecursoHUD::RecursoHUD(const RecursoHUD& orig) {
}

RecursoHUD::~RecursoHUD() {
}

void RecursoHUD::prueba(std::string s){
    texto->setString(s);
} 
sf::Sprite* RecursoHUD::getSprite(){
    return sprite;
}
void RecursoHUD::setSprite(sf::Sprite* s){
    sprite=s;
}

bool RecursoHUD::getMostrarPuntuacion(){
    return mostrarPuntuacion;
}
void RecursoHUD::setMostrarPuntuacion(bool m){
    mostrarPuntuacion=m;
}

void RecursoHUD::setOpacity(float o){
    sf::Color c = sprite->getColor();
    c.a=255*o;
    sprite->setColor(c);
    
    opacidad=o;
}

int RecursoHUD::getNum(){
    return num;
}
void RecursoHUD::setNum(int n){
    num=n;
}

int RecursoHUD::getTipo(){
    return tipo;
}
void RecursoHUD::setTipo(int t){
    tipo=t;
}

void RecursoHUD::setScale(float s){
    sprite->setScale(s,s);
    texto->setScale(s,s);
}

void RecursoHUD::aumentarNum(int i){
    if(tipo!=1 && tipo!=4){
        num+i;    
        texto->setString("x"+intAString(num));
    }
}
       
void RecursoHUD::masNum(){
    if(tipo!=1 && tipo!=4){
        num++;    
        texto->setString("x"+intAString(num));
    }
}
void RecursoHUD::menosNum(){
    if(tipo!=1 && tipo!=4){
        num--;    
        texto->setString("x"+intAString(num));
    }
}

void RecursoHUD::cambiarPosicion(int x, int y){
    sprite->setPosition(x,y);
    texto->setPosition(x+30,y+15);
}

std::string RecursoHUD::intAString(int p){
    std::string devuelve;
    
    std::stringstream aux;
    aux << p;

    aux >> devuelve;
    
    return devuelve;
}

void RecursoHUD::pintarRecurso(sf::RenderWindow &window){
    window.draw(*sprite);

    if(mostrarPuntuacion==true){
        sf::Color c = sf::Color(255,255,255,opacidad*255);        
        texto->setScale(1.05, 1.05);
        texto->setColor(c);        
        window.draw(*texto);
        c = sf::Color(0,0,0,opacidad*255);
        texto->setColor(c);
        texto->setScale(1.0,1.0);
        window.draw(*texto);
    }
}