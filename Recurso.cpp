/* 
 * File:   Recurso.cpp
 * Author: Marc
 * 
 * Created on 7 de abril de 2015, 13:08
 */

#include "Recurso.h"
#include<time.h>

Recurso::Recurso(sf::Sprite* s, sf::Texture* te, int bloq, int dan, int inv, int rec, int res, int tip) {
    spriteRecurso = new sf::Sprite(*s);
    tex = new sf::Texture(*te);
    bloqueante = bloq;
    danyo = dan;
    inventario = inv;
    recogida = rec;
    resistencia = res;
    tipo = tip;
    existe = 1;
    reloj.restart();
    
    srand(time(NULL));
    
    int num = rand();
    
    num=100+rand()%(1200-100);
    
    int num2 = rand();
    
    num2=100+rand()%(700-100);
    
    spriteRecurso->setPosition(num, num2);
    
    vectorActual = spriteRecurso->getPosition();
    
}

Recurso::Recurso(const Recurso& orig) {
    
}

Recurso::~Recurso() {
}
/***********************************METODOS GET Y SET************************************************/
int Recurso::getBloqueante(){
    return bloqueante;
    
}
void Recurso::setBloqueante(int b){
    bloqueante=b;
}

sf::Vector2<float> Recurso::getVectorActual(){
    return vectorActual;
    
}
void Recurso::setVectorActual(sf::Vector2<float> v){
    vectorActual=v;
}

int Recurso::getTipo(){
    return tipo;
    
}
void Recurso::setTipo(int tip){
    tipo=tip;
}

int Recurso::getExiste(){
    return existe;
    
}
void Recurso::setExiste(int e){
    existe=e;
}


int Recurso::getResistencia(){
    return resistencia;
    
}
void Recurso::setResistencia(int res){
    resistencia=res;
}

int Recurso::getDanyo(){
    return danyo;
    
}
void Recurso::setDanyo(int d){
    danyo=d;
}

int Recurso::getInventario(){
    return inventario;
}

void Recurso::setInventario(int i){
    inventario=i;
}

int Recurso::getRecogida(){
    return recogida;
}
void Recurso::setRecogida(int r){
    recogida=r;
} 



void Recurso::pintarRecursos(sf::RenderWindow &window)
{
    sf::Sprite* aux = spriteRecurso;
    aux->setTexture(*tex);
    window.draw(*aux);
    
}

void Recurso::actualizarRecurso()
{
    tiempo = reloj.getElapsedTime();
    
    if(tiempo.asSeconds() > 15)
    {
        existe = 0;
    }
}

