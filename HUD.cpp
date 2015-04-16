/* 
 * File:   HUD.cpp
 * Author: Dani
 * 
 * Created on 15 de abril de 2015, 20:05
 */

#include "HUD.h"

HUD::HUD(Personaje* p, sf::RenderWindow w) {
    
    if (!textura->loadFromFile("resources/HUD.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    sf::Vector2<unsigned int> tam = w.getSize();
    
    //***************************************************Inicializacion sprites
    sf::Sprite spritePistola(*textura);sf::Sprite spriteHacha(*textura);        
           
    //Este es el sprite que le pasaremos a disparar, para que las balas que se creen lo hagan con dicho sprite
    spritePistola.setOrigin(75/2,75/2);
    spritePistola.setTextureRect(sf::IntRect(1*75, 9*75, 75, 75));
    
    spriteHacha.setOrigin(75/2,75/2);
    spriteHacha.setTextureRect(sf::IntRect(2*75, 9*75, 75, 75));
    
    armas = std::vector<sf::Sprite*>();  
    armas.push_back(new sf::Sprite(spritePistola));
    armas.push_back(new sf::Sprite(spriteHacha));
    
    municion = new sf::Sprite(*textura);
    municion->setOrigin(75/2,75/2);
    municion->setTextureRect(sf::IntRect(2*75, 10*75, 75, 75));
    municion->setPosition((tam.x/8)*7, tam.y/7);
    
    spriteVida = new sf::Sprite(*textura);
    spriteVida->setOrigin(75/4,(75*9)/2);   
    spriteVida->setPosition(tam.x/8, tam.y/7);
    //***************************************************Inicializacion sprite vida
    vida=p->getVida();
    cargarSpriteVida(vida);
    boss=false;

    //***************************************************Inicializacion sprite municion
    sf::Sprite* municion;

    
    //***************************************************Inicializacion textos        
    // Load it from a file
    if (!fuente->loadFromFile("fonts/ZOMBIE.ttf"))
    {
        // error...
    }    
    
    puntuacion->setFont(*fuente);
    puntuacion->setCharacterSize(30);    
    puntuacion->setPosition(tam.x/8, (tam.y/6)*5);
    setPuntuacion(0);       
    
    numRecursos = std::vector<sf::Text*>();
    
    //***************************************************Inicializacion de opacidades
    boss=false;
    opacidadVida=1.0;
    opacidadMunicion=1.0;
    opacidadPuntuacion=1.0;
    opacidadVidaBoss=0.0;
    
}

HUD::HUD(const HUD& orig) {
}

HUD::~HUD() {
}

sf::Texture* HUD::getTextura(){
    return textura;
}
void HUD::setTextura(sf::Texture* t){
    textura=t;
}

sf::Sprite* HUD::getVida(){
    return spriteVida;
}
void HUD::setVida(sf::Sprite* v){
    spriteVida=v;
}

sf::Sprite* HUD::getMunicion(){
    return municion;
}
void HUD::setMunicion(sf::Sprite* m){
    municion=m;
}

sf::Font* HUD::getFuente(){
    return fuente;
}
void HUD::setFuente(sf::Font* f){
    fuente=f;
}

sf::Text* HUD::getPuntuacion(){
    return puntuacion;
}
void HUD::setPuntuacion(int p){    
    puntuacion->setString(puntuacionAString(p));
}

bool HUD::getBoss(){
    return boss;
}
void HUD::setBoss(bool b){
    boss=b;
}

float HUD::getOpacidadVida(){
    return opacidadVida;
}
void HUD::setOpacidadVida(float f){
    opacidadVida=f;
}

float HUD::getOpacidadMunicion(){
    return opacidadMunicion;
}
void HUD::setOpacidadMunicion(float f){
    opacidadMunicion=f;
}

float HUD::getOpacidadPuntuacion(){
    return opacidadPuntuacion;
}
void HUD::setOpacidadPuntuacion(float f){
    opacidadPuntuacion=f;
}

float HUD::getOpacidadVidaBoss(){
    return opacidadVidaBoss;
}
void HUD::setOpacidadVidaBoss(float f){
    opacidadVidaBoss=f;
}   
    
/******************************************METODOS CUSTOM************************************************************/   
    
void HUD::cargarSpriteVida(int i){    
    municion->setTextureRect(sf::IntRect(0*75*8, (i-1)*75/2, 75*8, 75/2));
}

void HUD::cargarSpriteVidaBoss(int i){
    
}

void HUD::reducirVida(){
    
}

void HUD::aumentarVida(){
    
}
    
void HUD::reducirBalas(){
    
}

void HUD::aumentarBalas(){
    
}
    
void HUD::actualizarHUD(Personaje* p){
    vida=p->getVida();
    cargarSpriteVida(vida);
}
    
    
void HUD::anyadirArma(Arma a){
    
}

void HUD::eliminarArma(Arma a){
    
}

/*void HUD::anyadirRecurso(Recurso r){
    
}

void HUD::eliminarRecurso(Recurso r){
    
}*/

void HUD::cambiarOpacidad(sf::Vector2<float> v){
    
}

std::string HUD::puntuacionAString(int p){
    std::string devuelve;
    
    std::stringstream aux;
    aux << p;

    aux >> devuelve;
    
    return devuelve;
}
    
void HUD::pintarHUD(sf::RenderWindow &window){
    for(int i=0; i<armas.size(); i++)
        window.draw(*armas[i]);
    
    for(int j=0; j<recursos.size(); j++)
        window.draw(*recursos[j]);
    
    for(int k=0; k<numRecursos.size(); k++)
        window.draw(*numRecursos[k]);
    
    window.draw(*spriteVida);
    window.draw(*municion);
    window.draw(*puntuacion);
}