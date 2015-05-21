#include "HUD.h"

HUD::HUD(Protagonista* p, sf::Vector2<int> tam) {
    tamPantalla=new sf::Vector2<int>();
    tamPantalla->x=tam.x;
    tamPantalla->y=tam.y;
    tipoPrincipal=p->getArma()->getTipo();
    sf::Texture tex;
    if (!tex.loadFromFile("resources/HUD.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    //sf::Vector2<int> tam = (sf::Vector2<int>) w.getSize();
    textura=new sf::Texture(tex);
    //***************************************************Inicializacion sprites        
    armas = std::vector<RecursoHUD*>();
    actualizarArrayArmas(p->getArmas());
    actualizarArmasHUD();
    
    /*RecursoHUD* pistola = new RecursoHUD(1);
    RecursoHUD* hacha = new RecursoHUD(4);
    RecursoHUD* metralleta = new RecursoHUD(3);
    RecursoHUD* escopeta = new RecursoHUD(2);
    armas = std::vector<RecursoHUD*>();  
    armas.push_back(pistola);
    armas.push_back(hacha);
    armas.push_back(metralleta);
    armas.push_back(escopeta);    
    */    
    
    sprintDisponible = new sf::Sprite(*textura);
    sprintDisponible->setTextureRect(sf::IntRect(9*75, 4*75, 75*3, 75));
    sprintDisponible->setPosition(tam.x/10*1, tam.y/8*6);
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
    spriteVida->setPosition(tam.x/10*2, tam.y/8*7.4);
    //spriteVida->setPosition(133, 500);
    vida=p->getVida();
    cargarSpriteVida();
    sprint=false;

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
    if(tipoPrincipal==1 || tipoPrincipal==4){
        balas->setRotation(90);
        balas->setCharacterSize(100);
        balas->setString(intAString(8));
        balas->setPosition(tam.x/10*9.93, tam.y/8*7.15);
    }else{
        balas->setCharacterSize(60);
        balas->setString(intAString(p->getArma()->getMunicion()));
        balas->setPosition(tam.x/10*9, tam.y/8*7);
    }    
    
    //***************************************************Inicializacion de opacidades
    sprint=false;
    opacidadVida=1.0;
    opacidadMunicion=1.0;
    opacidadPuntuacion=1.0;
    opacidadVidaBoss=0.0;
    recursos = std::vector<RecursoHUD*>(); 
    actualizarArrayRecursos(p, p->getInventario());
    actualizarRecursosHUD();
    
    /*RecursoHUD* recurso1 = new RecursoHUD(5);
    RecursoHUD* recurso2 = new RecursoHUD(6);
    RecursoHUD* recurso3 = new RecursoHUD(7);
    RecursoHUD* recurso4 = new RecursoHUD(8);
    recursos.push_back(recurso1);
    recursos.push_back(recurso2);
    recursos.push_back(recurso3);
    recursos.push_back(recurso4);
    actualizarRecursosHUD();*/
        
    contMensaje=0;
    tiempoMensaje=50;
}

HUD::HUD(const HUD& orig) {
}

HUD::~HUD() 
{
    //delete textura;
    //delete fuente;
    
    //delete spriteVida;
    //delete spriteVidaBoss;
    delete municion;
    
    for(int i = 0; i < armas.size(); i++)
    {
        delete armas[i];
    }
    
    for(int i = 0; i < recursos.size(); i++)
    {
        delete recursos[i];
    }

    delete puntuacion;
    delete balas;    
    delete mensaje;    
    delete tamPantalla;
    
    
}

sf::Texture* HUD::getTextura(){
    return textura;
}
void HUD::setTextura(sf::Texture* t){
    textura=t;
}

void HUD::cambiarHachaPorSerrucho(){
    for(int i=0; i<armas.size(); i++){
        if(armas[i]->getTipo()==4)
            armas[i]->cambiarASerrucho();
    }
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
    return sprint;
}
void HUD::setBoss(bool b){
    sprint=b;
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

sf::Vector2<int>* HUD::getTamPantalla(){
    return tamPantalla;
}
    
/******************************************METODOS CUSTOM************************************************************/   
    
void HUD::cargarSpriteVida(){    
    if(vida>0)
        spriteVida->setTextureRect(sf::IntRect(0*75*9, (vida-1)*75/2, 75*8, 75/2));
    else
        spriteVida->setTextureRect(sf::IntRect(0*75*9, 20*75/2, 75*8, 75/2));
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
    
void HUD::actualizarHUD(Protagonista* p, int punt){
    vida=p->getVida();
    //Actualizamos vida
    cargarSpriteVida();
    
    sprint=p->devuelveSprintDisponible();
    
    //Actualizamos arma principal
    Arma* a = p->getArma();
    tipoPrincipal=a->getTipo();
    if(tipoPrincipal!=1 && tipoPrincipal!=4){        
        balas->setRotation(0);
        balas->setCharacterSize(60);
        balas->setString(intAString(a->getMunicion()));
        balas->setPosition(tamPantalla->x/10*9, tamPantalla->y/8*7);        
    }else{
        balas->setCharacterSize(100);
        balas->setRotation(90);
        balas->setString(intAString(8));
        balas->setPosition(tamPantalla->x/10*9.93, tamPantalla->y/8*7.15);
    }
    //Actualizamos las opacidades
    sf::Vector2<float> pos = p->getSprite()->getPosition();
    actualizarOpacidades(pos);
    setPuntuacion(punt);
    actualizarArrayArmas(p->getArmas());
    actualizarArrayRecursos(p, p->getInventario());
}
    
void HUD::actualizarArmasHUD(){    
    float separacion=80;        
    float posX=tamPantalla->x/10*9.7;// .getPosition().x;
    float posY=tamPantalla->y/8*7.15;
    int j=0;
    float l=1;
    for(int i=0; i<armas.size();i++){
        if(armas[i]->getTipo()==2 ||armas[i]->getTipo()==3)
            l=2;
        else
            l=1.5;
        if(armas[i]->getTipo()!=tipoPrincipal){
            armas[i]->setScale(1);
            
            armas[i]->cambiarPosicion(posX-50*l, (-separacion)+posY-(j*separacion));
            j++;
            if(armas[i]->getMostrarPuntuacion()==false)
                armas[i]->setMostrarPuntuacion(true);
        }else{
            armas[i]->setScale(1.5);
            armas[i]->cambiarPosicion(posX-(tamPantalla->x/5.5)*l/1.5, posY+30);
            armas[i]->setMostrarPuntuacion(false);
        }
    }
}

void HUD::actualizarRecursosHUD(){    
    float separacion=70;  
    
    float posX=50+tamPantalla->x/10*1;// .getPosition().x;
    float posY=-20+tamPantalla->y/8*7;
    int j=0;
    for(int i=0; i<recursos.size();i++){
        recursos[i]->cambiarPosicion(posX+(separacion*i), posY);//(i*separacion));        
    }
}

void HUD::actualizarArrayArmas(std::vector<Arma*> v){
    for(int i=0; i<v.size();i++){
        Arma* aux = v[i];

        //Comprobamos si su municion es mayor a 0 para insertarlo/borrarlo
        if(aux->getMunicion()>0){
            anyadirArma(aux);
        }else{
            eliminarArma(aux);
        }
    }
    actualizarArmasHUD();
} 

void HUD::actualizarArrayRecursos(Protagonista* p, std::vector<Recurso*> v){
    for(int i=0; i<v.size();i++){
        Recurso* aux = v[i];
        if(aux->getEstaEnInventario()==false){
            aux->setEstaEnInventario(true);   
            anyadirRecurso(aux);
        }
        if(aux->getReducirEnInventario()==true){
            std::cout<<"Reduzco en inventario num "<<intAString(i)<<std::endl;
            eliminarGranada(aux, v, i);
            std::cout<<"Eliminado recurso en hud"<<std::endl;
            p->sacarDeInventario(i);
        }
    }
    actualizarRecursosHUD();
}

void HUD::eliminarGranada(Recurso* r, std::vector<Recurso*> v, int i){
    bool reducido = false;
    if(i<recursos.size()){
        for(int j=0;j<recursos.size();j++){
            if(recursos[j]->getTipo()==r->getTipo()&& reducido==false && r->getReducirEnInventario()==true){
                reducido = true;
                recursos[j]->menosNum(); //reduzco el numero de granadas 
                if(recursos[i]->getNum()<=0)
                    recursos.erase(recursos.begin()+j);                
            }
        }
    }
}

void HUD::anyadirArma(Arma* a){
    int tipo = a->getTipo();
    bool esta=false;
    for(int i=0; i<armas.size();i++){
        if(esta==false && armas[i]->getTipo()==tipo){
            armas[i]->cambiarNum(a->getMunicion());
            esta=true;
        }            
    }
    
    if(esta==false){
        RecursoHUD* nuevoRecurso = new RecursoHUD(tipo);
        armas.push_back(nuevoRecurso);        
    }    
}

void HUD::eliminarArma(Arma* a){
    int tipo = a->getTipo();
    bool esta=false;
    RecursoHUD* r;
    for(int i=0; i<armas.size();i++){
        if(esta==false && armas[i]->getTipo()==tipo){
            armas[i]->menosNum();
            if(armas[i]->getNum()<=0)
            {
                r = armas[i];
                armas.erase(armas.begin()+i);
                delete r;
                i--;
                actualizarArmasHUD();
            }
            esta=true;
        }            
    }      
}

void HUD::anyadirRecurso(Recurso* r){
    int tipo = r->getTipo();
    bool esta=false;
    for(int i=0; i<recursos.size();i++){
        if(esta==false && recursos[i]->getTipo()==tipo){
            recursos[i]->masNum();
            esta=true;
        }            
    }
    if(esta==false){
        RecursoHUD* nuevoRecurso = new RecursoHUD(tipo);
        nuevoRecurso->masNum();
        recursos.push_back(nuevoRecurso);
        actualizarRecursosHUD();
    }
}

void HUD::eliminarRecurso(Recurso* r){
    int tipo = r->getTipo();
    bool esta=false;
    RecursoHUD* p;
    
    for(int i=0; i<recursos.size();i++){
        if(esta==false && recursos[i]->getTipo()==tipo){
            recursos[i]->menosNum();
            if(recursos[i]->getNum()<=0)
            {
                p = recursos[i];
                recursos.erase(recursos.begin()+i);
                delete p;
                i--;
                actualizarArmasHUD();
            }
            esta=true;
        }            
    } 
}

void HUD::actualizarOpacidades(sf::Vector2<float> pos){    
    float opacidad = 0.4;
    if(pos.x<tamPantalla->x/4 && pos.y<tamPantalla->y/4){//Cerca de puntuacion
        opacidadPuntuacion = opacidad;
        opacidadMunicion = 1.0; 
        opacidadVida = 1.0;
    }else if(pos.x<tamPantalla->x/2 && pos.y>tamPantalla->y/4*3){//Cerca de vida y recursos
        opacidadPuntuacion = 1.0;
        opacidadMunicion = 1.0; 
        opacidadVida = opacidad;
    }else if(pos.x>tamPantalla->x/6*4 && pos.y>tamPantalla->y/2){//Cerca de municion y armas
        opacidadPuntuacion = 1.0;
        opacidadMunicion = opacidad; 
        opacidadVida = 1.0;
    }else{
        opacidadPuntuacion = 1.0;
        opacidadMunicion = 1.0; 
        opacidadVida = 1.0;
    }
}

void  HUD::cambiarOpacidad(sf::Sprite* &s, float o){
    sf::Color c = s->getColor();
    c.a=255*o;
    s->setColor(c);        
}

void  HUD::cambiarOpacidad(sf::Text* &t, float o){
    sf::Color c=t->getColor();
    c.a=255*o;
    t->setColor(c);     
}

std::string HUD::intAString(int p){
    std::string devuelve;
    
    std::stringstream aux;
    aux << p;

    aux >> devuelve;
    
    return devuelve;
}

void HUD::crearMensaje(std::string s, int t, int cont, int p){
    mensaje = new sf::Text();
    int tam;
    if(t>0)
        tam=t;
    else
        tam=60;
    
    mensaje->setFont(*fuente);
    mensaje->setCharacterSize(tam);
    if(p == 0)
        mensaje->setPosition(tamPantalla->x/4+((tamPantalla->x/20)), tamPantalla->y/2-(tamPantalla->y/10));
    else
        mensaje->setPosition(100, 100);

    mensaje->setString(s);
    
    if(cont>25)
        tiempoMensaje=cont;
    else
        tiempoMensaje=60;
    contMensaje=1;
}
    
void HUD::pintarHUD(sf::RenderWindow &window){
    for(int i=0; i<armas.size(); i++){
        armas[i]->setOpacity(opacidadMunicion);
        armas[i]->pintarRecurso(window);       
    }
    sf::Text auxTexto;
    auxTexto.setFont(*fuente);
    auxTexto.setCharacterSize(10);
    for(int j=0; j<recursos.size(); j++){
        recursos[j]->setOpacity(opacidadVida);
        recursos[j]->pintarRecurso(window);        
    }

    cambiarOpacidad(spriteVida, opacidadVida);
    window.draw(*spriteVida);
    
    cambiarOpacidad(municion, opacidadMunicion);
    window.draw(*municion);
        
    balas->setColor(sf::Color::White);
    cambiarOpacidad(balas, opacidadMunicion);
    balas->setScale(1.05,1.05);
    window.draw(*balas);
    balas->setColor(sf::Color::Black);
    cambiarOpacidad(balas, opacidadMunicion);
    balas->setScale(1.0,1.0);
    window.draw(*balas);
    
    if(sprint){
        cambiarOpacidad(sprintDisponible, opacidadVida);
        window.draw(*sprintDisponible);
    }
    puntuacion->setColor(sf::Color::White);
    cambiarOpacidad(puntuacion, opacidadPuntuacion);
    puntuacion->setScale(1.05,1.05);
    window.draw(*puntuacion);
    puntuacion->setColor(sf::Color::Black);
    cambiarOpacidad(puntuacion, opacidadPuntuacion);
    puntuacion->setScale(1.0,1.0);
    window.draw(*puntuacion);
    
    if(contMensaje>0 && contMensaje<=tiempoMensaje){        
        window.draw(*mensaje);
        contMensaje++;
    }else if(contMensaje>tiempoMensaje)
        contMensaje=0;
}
