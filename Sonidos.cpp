/* 
 * File:   Sonidos.cpp
 * Author: Xisco
 * 
 * Created on 14 de mayo de 2015, 21:23
 */

#include "Sonidos.h"

Sonidos* Sonidos::pinstance = 0;

Sonidos::Sonidos() {
    inicio.openFromFile("resources/inicio.wav");
    inicio.setVolume(75);
    nivel1.openFromFile("resources/Nivel1.wav");
    nivel1.setVolume(40);
    nivel2.openFromFile("resources/Nivel2.wav");
    nivel2.setVolume(10);
    nivel3.openFromFile("resources/Nivel3.wav");
    nivel3.setVolume(20);
    pistola.openFromFile("resources/pistola2.wav");
    pistola.setVolume(6);
    escopeta.openFromFile("resources/escopeta.wav");
    escopeta.setVolume(35);
    metralleta.openFromFile("resources/metralleta.wav");
    metralleta.setVolume(35);
    risaBoss.openFromFile("resources/risaBoss.wav");
    ataqueZombie.openFromFile("resources/ataqueZombie.wav");
    ataqueZombie.setVolume(60);
    zombie1.openFromFile("resources/zombie1.wav");    
    zombie2.setVolume(40);
    zombie2.openFromFile("resources/zombie2.wav");
    zombie2.setVolume(100);
    zombie3.openFromFile("resources/zombie3.wav");
    zombie3.setVolume(45);
    zombie4.openFromFile("resources/zombie4.wav");
    zombie5.openFromFile("resources/zombie5.wav");
    zombie5.setVolume(60);   
    zombie6.openFromFile("resources/zombie6.wav");
    zombie7.openFromFile("resources/zombie7.wav");
    zombie7.setVolume(60);   
    zombie8.openFromFile("resources/zombie8.wav");
    zombie8.setVolume(80);
    
}

Sonidos::Sonidos(const Sonidos& orig) {
}

Sonidos::~Sonidos() {
}

