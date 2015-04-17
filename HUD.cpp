/* 
 * File:   HUD.cpp
 * Author: Dani
 * 
 * Created on 15 de abril de 2015, 20:05
 */

#include "HUD.h"

HUD::HUD(Personaje* p, sf::Vector2<int> tam) {
    sf::Texture tex;
    if (!tex.loadFromFile("resources/HUD.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    //sf::Vector2<int> tam = (sf::Vector2<int>) w.getSize();
    textura=new sf::Texture(tex);
    //***************************************************Inicializacion sprites
    sf::Sprite spritePistola(*textura);sf::Sprite spriteHacha(*textura);        
           
    //Este es el sprite que le pasaremos a disparar, para que las balas que se creen lo hagan con dicho sprite
    spritePistola.setOrigin(75/2,75/2);
    spritePistola.setTextureRect(sf::IntRect(9*75, 1*75, 75, 75));
    
    spriteHacha.setOrigin(75/2,75/2);
    spriteHacha.setTextureRect(sf::IntRect(9*75, 2*75, 75, 75));
    
    armas = std::vector<sf::Sprite*>();  
    armas.push_back(new sf::Sprite(spritePistola));
    armas.push_back(new sf::Sprite(spriteHacha));
     //***************************************************Inicializacion sprite municion
    municion = new sf::Sprite(*textura);
    municion->setScale(0.8,0.8);
    municion->setOrigin(75/2,75/2);
    municion->setTextureRect(sf::IntRect(10*75, 2*75, 75, 75));
    municion->setPosition(tam.x/10*8.6, tam.y/8*7.4);
    
    
    //***************************************************Inicializacion sprite vida
    spriteVida = new sf::Sprite(*textura);
    spriteVida->setOrigin((75*9)/2, 75/4); 
    spriteVida->setScale(0.6,0.6);
    /*std::cout<<"Tam x:" << tam.x << " Tam y: " << tam.y << std::endl;
    std::cout<<"Pos x:" << tam.x/6*5 << " Pos y: " << tam.y/8*7 << std::endl;*/
    spriteVida->setPosition(tam.x/10*2.7, tam.y/8*7.4);
    //spriteVida->setPosition(133, 500);
    vida=p->getVida();
    cargarSpriteVida();
    boss=false;

    //***************************************************Inicializacion textos        
    // Load it from a file
    sf::Font font;
    if (!font.loadFromFile("fonts/ZOMBIE.ttf"))
    {
        // error...
    }    
    fuente = new sf::Font(font);
    sf::Text texto;
    texto.setFont(*fuente);
    texto.setCharacterSize(60);
    texto.setPosition(tam.x/10*0.5, tam.y/8*0.5);
    puntuacion = new sf::Text(texto);    
    setPuntuacion(2568);       
    
    numRecursos = std::vector<int>();
    
    balas = new sf::Text();
    balas->setFont(*fuente);
    balas->setCharacterSize(80);
    balas->setString(puntuacionAString(8));
    balas->setRotation(90);
    balas->setPosition(tam.x/10*9.7, tam.y/8*7.15);
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
    
void HUD::cargarSpriteVida(){    
    spriteVida->setTextureRect(sf::IntRect(0*75*9, (vida-1)*75/2, 75*8, 75/2));
}

void HUD::cargarSpriteVidaBoss(int i){
    spriteVidaBoss->setTextureRect(sf::IntRect(0*75*9, (i-1)*75/2, 75*8, 75/2));
}

void HUD::reducirVida(){
    vida--;
    cargarSpriteVida();
}

void HUD::aumentarVida(){
    vida++;
    cargarSpriteVida();
}
    
void HUD::reducirBalas(){
    
}

void HUD::aumentarBalas(){
    
}
    
void HUD::actualizarHUD(Personaje* p){
    vida=p->getVida();
    cargarSpriteVida(vida);
}
    
    
void HUD::anyadirArma(Arma* a){
    a->getTipo();
}

void HUD::eliminarArma(Arma* a){
    
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
    for(int i=0; i<armas.size(); i++){
        //window.draw(*armas[i]);
    }
    sf::Text auxTexto;
    auxTexto.setFont(*fuente);
    auxTexto.setCharacterSize(10);
    for(int j=0; j<recursos.size(); j++){
        window.draw(*recursos[j]);
        auxTexto.setPosition(recursos[j]->getPosition().x+1,recursos[j]->getPosition().y+1);
        auxTexto.setString("x"+puntuacionAString(numRecursos[j]));
        auxTexto.setScale(1.05, 1.05);
        auxTexto.setColor(sf::Color::White);
        window.draw(auxTexto);
        auxTexto.setColor(sf::Color::Black);
        auxTexto.setScale(1.0,1.0);
        window.draw(*puntuacion);
    }
    
    window.draw(*spriteVida);
    
    window.draw(*municion);
    
    balas->setColor(sf::Color::White);
    balas->setScale(1.05,1.05);
    window.draw(*balas);
    balas->setColor(sf::Color::Black);
    balas->setScale(1.0,1.0);
    window.draw(*balas);
    
    puntuacion->setColor(sf::Color::White);
    puntuacion->setScale(1.05,1.05);
    window.draw(*puntuacion);
    puntuacion->setColor(sf::Color::Black);
    puntuacion->setScale(1.0,1.0);
    window.draw(*puntuacion);
}