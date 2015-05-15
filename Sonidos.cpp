/* 
 * File:   Sonidos.cpp
 * Author: Xisco
 * 
 * Created on 14 de mayo de 2015, 21:23
 */

#include "Sonidos.h"

Sonidos* Sonidos::pinstance = 0;

Sonidos::Sonidos() {
    nivel1.openFromFile("resources/Nivel1.wav");
    nivel2.openFromFile("resources/Nivel2.wav");
    nivel3.openFromFile("resources/Nivel3.wav");
    pistola.openFromFile("resources/pistola2.wav");
    risaBoss.openFromFile("resources/risaBoss.wav");
    ataqueZombie.openFromFile("resources/ataqueZombie.wav");
    zombie1.openFromFile("resources/zombie1.wav");
    zombie2.openFromFile("resources/zombie2.wav");
}

Sonidos::Sonidos(const Sonidos& orig) {
}

Sonidos::~Sonidos() {
}

