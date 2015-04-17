/* 
 * File:   HUD.cpp
 * Author: Dani
 * 
 * Created on 15 de abril de 2015, 20:05
 */

#include "HUD.h"

HUD::HUD(Personaje* p, sf::Vector2<int> tam) {
    tamPantalla=new sf::Vector2<int>();
    tamPantalla->x=tam.x;
    tamPantalla->y=tam.y;
    tipoPrincipal=1;
    
    sf::Texture tex;
    if (!tex.loadFromFile("resources/HUD.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    //sf::Vector2<int> tam = (sf::Vector2<int>) w.getSize();
    textura=new sf::Texture(tex);
    //***************************************************Inicializacion sprites        
    RecursoHUD* pistola = new RecursoHUD(1);
    RecursoHUD* hacha = new RecursoHUD(2);
    armas = std::vector<RecursoHUD*>();  
    armas.push_back(pistola);
    armas.push_back(hacha);
    actualizarArmasHUD();
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

    balas = new sf::Text();
    balas->setFont(*fuente);
    balas->setCharacterSize(80);
    balas->setString(intAString(8));
    balas->setRotation(90);
    balas->setPosition(tam.x/10*9.7, tam.y/8*7.15);
    //***************************************************Inicializacion de opacidades
    boss=false;
    opacidadVida=1.0;
    opacidadMunicion=1.0;
    opacidadPuntuacion=1.0;
    opacidadVidaBoss=0.0;
    recursos = std::vector<RecursoHUD*>();     

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
    puntuacion->setString(intAString(p));
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
    
void HUD::actualizarHUD(Protagonista* p){
    vida=p->getVida();
    cargarSpriteVida();
    
    //tipoPrincipal=p->getArma()->getTipo();
}
    
void HUD::actualizarArmasHUD(){    
    float separacion=50;        
    float posX=tamPantalla->x/10*9.7;// .getPosition().x;
    float posY=tamPantalla->y/8*7.15;
    int j=0;
    for(int i=0; i<armas.size();i++){
        if(armas[i]->getTipo()!=tipoPrincipal){
            armas[i]->cambiarPosicion(posX-50, (2*-separacion)+posY-(j*separacion));//(i*separacion));
            j++;
            std::cout<<armas[i]->getTipo()<<std::endl;
        }else{
            armas[i]->setScale(1.5);
            armas[i]->cambiarPosicion(posX-200, posY);
        }
    }
}
    
void HUD::anyadirArma(Arma* a){
    int tipo = a->getTipo();
    bool esta=false;
    for(int i=0; i<armas.size();i++){
        if(esta==false && armas[i]->getTipo()==tipo){
            armas[i]->masNum();
            esta=true;
        }            
    }
    
    if(esta==false){
        RecursoHUD* nuevoRecurso = new RecursoHUD(tipo);
        armas.push_back(nuevoRecurso);
        actualizarArmasHUD();
    }    
}

void HUD::eliminarArma(Arma* a){
    int tipo = a->getTipo();
    bool esta=false;
    for(int i=0; i<armas.size();i++){
        if(esta==false && armas[i]->getTipo()==tipo){
            armas[i]->menosNum();
            if(armas[i]->getNum()<=0){
                armas.erase(armas.begin()+i);
                actualizarArmasHUD();
            }
            esta=true;
        }            
    }      
}

/*void HUD::anyadirRecurso(Recurso r){
    
}

void HUD::eliminarRecurso(Recurso r){
    
}*/

void HUD::cambiarOpacidad(sf::Vector2<float> v){
    
}

std::string HUD::intAString(int p){
    std::string devuelve;
    
    std::stringstream aux;
    aux << p;

    aux >> devuelve;
    
    return devuelve;
}
    
void HUD::pintarHUD(sf::RenderWindow &window){
    for(int i=0; i<armas.size(); i++){
        armas[i]->pintarRecurso(window);       
    }
    sf::Text auxTexto;
    auxTexto.setFont(*fuente);
    auxTexto.setCharacterSize(10);
    /*for(int j=0; j<recursos.size(); j++){
        recursos[j]->pintarRecurso(window);        
    }*/

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