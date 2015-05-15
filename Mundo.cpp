#include "Mundo.h"
#define UPDATE_TIME 1000/15
#define RENDER_TIME 1000/60

Mundo::Mundo(sf::RenderWindow &w) {
    window=&w;
    tamPantalla=(sf::Vector2<int>) window->getSize();
    
    fabricaPersonaje=new PersonajeFactory();

    sf::Vector2<float> pos;
    pos.x=tamPantalla.x/2;
    pos.y=tamPantalla.y/2;

    protagonista=fabricaPersonaje->crearProtagonista(pos);
       
    fabricaNivel=new NivelFactory();
    nivel = fabricaNivel->crearNivel(1, protagonista, tamPantalla);
    window->setMouseCursorVisible(false);
    
    relojUpdate.restart();
    relojRender.restart();    
       
    sf::Texture texAux;
    if (!texAux.loadFromFile("resources/sprite_general.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    
    tex = new sf::Texture(texAux);
    //Y creo el spritesheet a partir de la imagen anterior    
    apuntar = new sf::Sprite();
    apuntar->setTexture(*tex);    
    
    apuntar->setOrigin(75/2,75/2);
    apuntar->setTextureRect(sf::IntRect(1*75, 4*75, 75, 75));
    apuntar->setPosition((sf::Vector2f)posicionCursor());
    
}



bool Mundo::capturarCierre()
{
    bool captura=false;
    //Bucle de obtencion de eventos
    sf::Event event;
    while(window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            captura=true;
        }
    }
    return captura;
}

Protagonista* Mundo::getProtagonista(){
    return protagonista;
}

int Mundo::getPuntuacionMundo(){
    return nivel->getPuntuacion();
}

int Mundo::setPuntuacionMundo(int p){
    nivel->setPuntuacion(p);
}

void Mundo::cambiarNivel(int i){
    protagonista->getSprite()->setPosition(tamPantalla.x/2, tamPantalla.y/2);
    nivel = fabricaNivel->crearNivel(i,protagonista, (sf::Vector2<int>)window->getSize());
}

bool Mundo::capturarPausa()
{
    bool pausa = false;
    //Bucle de obtencion de eventos
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        pausa=true;
    }

    return pausa;
}

Mundo::Mundo(const Mundo& orig) {
}

Mundo::~Mundo() {
}

sf::Vector2<int> Mundo::posicionCursor(){
    sf::Vector2<int> pos;
    sf::Mouse raton;
    pos.x = raton.getPosition(*window).x;
    pos.y = raton.getPosition(*window).y;
    
    return pos;
}

void Mundo::reiniciarMundo(){
    reiniciarProtagonista();

    //delete nivel;
    nivel = fabricaNivel->crearNivel(1,protagonista, (sf::Vector2<int>)window->getSize());
}

void Mundo::siguienteNivel(){
    //delete nivel;
    protagonista->getSprite()->setPosition(tamPantalla.x/2, tamPantalla.y/2);
    nivel = fabricaNivel->crearNivel(nivel->getId()+1,protagonista, (sf::Vector2<int>)window->getSize());
}

Nivel* Mundo::getNivel(){
    return nivel;
}

//Empezamos con las mejoras, en el nivel y con la puntuacion que tenia el usuario
void Mundo::cargarPartida(std::vector<int> v){
    //Los cuatro primeros enteros son el valor de mejora de las cuatro primeras armas
    for(int i=0; i<4; i++)
        setMejoraArma(i, v[i]);
    //El siguiente es el nivel
    protagonista->getSprite()->setPosition(tamPantalla.x/2, tamPantalla.y/2);    
    nivel = fabricaNivel->crearNivel(v[4], protagonista, (sf::Vector2<int>)window->getSize());
    //El siguiente es la puntuacion
    nivel->setPuntuacion(v[5]);
}

void Mundo::setMejoraArma(int i, int m){
    Arma* c = protagonista->getArmas()[i];
    c->setMejora(m);
}

void Mundo::reiniciarProtagonista(){
    //delete protagonista;
    
    sf::Vector2<float> pos = (sf::Vector2<float>) window->getSize();
    pos.x = pos.x/2;
    pos.y = pos.y/2;
    
    protagonista = fabricaPersonaje->crearProtagonista(pos);        
}

void Mundo::reiniciarNivel(){
    reiniciarProtagonista();
    nivel = fabricaNivel->crearNivel(nivel->getId(),protagonista, (sf::Vector2<int>)window->getSize());
}

int Mundo::ejecutarMundo(){    
    int estado=0;   //estado 0: Sigue en juego; estado 1: Menu de pausa; estado 2: Menu de "Has muerto"; estado 3: Nivel finalizado; estado 4: Juego finalizado
    bool nivelAcabado=false;  
    bool existePersonaje=false;    
    
    //Bucle del juego    
    while (window->isOpen() && estado==0)
    {
        //Controlamos la frecuencia a la que se ejecuta el programa
        frecuencia = relojUpdate.getElapsedTime().asMilliseconds();
        //Actualizamos 15 veces por segundo
        if(frecuencia>UPDATE_TIME){ 
            
            //Bucle de obtencion de eventos
            sf::Event event;                                             
                        
            protagonista->update(posicionCursor(),nivel->getZombies(), nivel->getMapa(), nivel->getRecursos());
            existePersonaje=protagonista->Existe();
            
            //1: Menu Inicio ; 2: Menu Pausa ; 3: Menu Fin de nivel ; 4: Menu muerte ; 5: Menu ¿Desea Salir?
            if(existePersonaje==false)
                estado=4;
            
            int impactos = 0;
            std::vector<Arma*> arm = protagonista->getArmas();
            std::vector<Zombie*> zombies = nivel->getZombies();
            for(int j = 0; j < zombies.size(); j++)
            {
                if(zombies[j]->colisionConBalas(arm))
                {
                    impactos++;
                }
                if(zombies[j]->colisionConGranadas(arm))
                {
                    impactos += 8;
                }
            }
            
            nivelAcabado = nivel->actualizarNivel(protagonista, impactos,0);
            if(nivelAcabado==true){//Nivel finalizado                
                nivel->calcularPuntuacionTotal();
                pintarMundo();
                sf::Time delayTime = sf::seconds(10);
                sf::sleep(delayTime);
                estado=3;
            }
            relojUpdate.restart();
        }
        
        frecuencia = relojRender.getElapsedTime().asMilliseconds();
        //Pintamos e interpolamos 60 veces por segundo
        if(frecuencia>RENDER_TIME){
            interpolarMundo();
            pintarMundo();
            relojRender.restart();
        }
        if(capturarCierre())
            estado=5;
        if(capturarPausa())
            estado=2;
    }
    window->clear();
    return estado;
}

void Mundo::setPuntuacionNivel(int p){
    nivel->setPuntuacion(p);
}
    
int Mundo::getPuntuacionNivel(){
    return nivel->getPuntuacion();
}

void Mundo::interpolarMundo(){
    //SE INTERPOLA: PERSONAJE - ZOMBIES - GRANADAS - PROYECTILES
    if(contInterpolacion==4)
        contInterpolacion=0;
    
    sf::Vector2<float> mov;
    mov.x= protagonista->getPosActual().x-protagonista->getPosAnterior().x;
    mov.y= protagonista->getPosActual().y-protagonista->getPosAnterior().y;
    
    mov.x = mov.x*contInterpolacion*0.25;
    mov.y = mov.y*contInterpolacion*0.25;
    //protagonista->getSprite()->setPosition(protagonista->getPosActual().x+mov.x, protagonista->getPosActual().y+mov.y);
    protagonista->mover(mov.x, mov.y);
    
    std::vector<Zombie*> zom = nivel->getZombies();
    for(int i=0; i<zom.size(); i++){
        mov.x= zom[i]->getPosActual().x-zom[i]->getPosAnterior().x;
        mov.y= zom[i]->getPosActual().y-zom[i]->getPosAnterior().y;
        
        mov.x = mov.x*contInterpolacion*0.25;
        mov.y = mov.y*contInterpolacion*0.25;
        zom[i]->mover(mov.x, mov.y);
    }
    
    std::vector<Proyectil*> bal = protagonista->getArma()->getCargador();
    for(int i=0; i<bal.size(); i++){
        mov.x= bal[i]->getPosActual().x-bal[i]->getPosActual().x;
        mov.y= bal[i]->getPosActual().y-bal[i]->getPosActual().y;
        
        mov.x = mov.x*contInterpolacion*0.25;
        mov.y = mov.y*contInterpolacion*0.25;
        bal[i]->mover(mov.x, mov.y);
    }
    
    std::vector<Granada*> gra = protagonista->getArma()->getSecundaria();
    for(int i=0; i<gra.size(); i++){
        mov.x= gra[i]->getPosActual().x-gra[i]->getPosAnterior().x;
        mov.y= gra[i]->getPosActual().y-gra[i]->getPosAnterior().y;
        
        mov.x = mov.x*contInterpolacion*0.25;
        mov.y = mov.y*contInterpolacion*0.25;
        gra[i]->mover(mov.x, mov.y);
    }
}

void Mundo::pintarMundo(){
    window->clear();
    nivel->pintarMapa(*window,0);//map->Draw(window);
    //Actualizamos la posicion de las balas
    protagonista->pintarProtagonista(*window);
    protagonista->getArma()->pintarProyectiles(*window);
    //window->draw(*(protagonista->getSprite()));
    nivel->pintarMapa(*window,2);//map->Draw(window);
    nivel->pintarNivel(*window);//hud.pintarHUD(window);
    apuntar->setPosition(posicionCursor().x, posicionCursor().y);
    window->draw(*apuntar);                                    
    window->display();
}