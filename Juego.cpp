#include "Juego.h"
#include <SFML/Audio.hpp>

Juego::Juego() 
{
    gestionPartida=new GuardarCargarPartida();
    audios = Sonidos::Instance();
}

Juego::Juego(const Juego& orig) {
    
}

Juego::~Juego() {    
    delete gestionPartida;
}

std::string intAString(int f){
    std::string devuelve;
    
    std::stringstream aux;
    aux << f;

    aux >> devuelve;
    
    return devuelve;
}

bool Juego::menuSalirDelJuego(){
    bool salir=false;
    
    int estadoMenu = ejecutarMenu(5);
    switch(estadoMenu){
        case -10: salir=true; break;
        case -11: salir=false; break;
    }
    return salir;    
}

int Juego::menuFinDelJuego(){
//1: Menu Inicio ; 2: Menu Pausa ; 3: Menu Fin de nivel ; 4: Menu muerte ; 5: Salir
    sf::Clock reloj;
    reloj.restart();    
    MenuFactory* fab = new MenuFactory();
    Menu* menu;        
    menu=fab->hacerMenu(window->getSize().x, window->getSize().y, 8);
    
    sf::Texture tex;
    if (!tex.loadFromFile("resources/final.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    //sf::Vector2<int> tam = (sf::Vector2<int>) w.getSize();
    sf::Texture* textura=new sf::Texture(tex);

    sf::Sprite* aux = new sf::Sprite();
    aux->setTexture(*textura);
    aux->setPosition(0,0);    
    
    /**************************************************************BUCLE DE MENU**************************************************************************/
    int estadoMenu = -1;    
    while(estadoMenu!=-9){                              
        if(reloj.getElapsedTime().asMilliseconds()>UPDATE_TIME){
            estadoMenu = menu->update(*window);                                    
            window->clear();            
            menu->draw(*window);
            window->draw(*aux);
            window->display();
            reloj.restart();
            capturarCierre();
         }
    }
    
    delete aux;
    delete textura;
    
    return estadoMenu;
}


void Juego::menuPuntuaciones(){
    //1: Menu Inicio ; 2: Menu Pausa ; 3: Menu Fin de nivel ; 4: Menu muerte ; 5: Salir
    sf::Clock reloj;
    reloj.restart();    
    MenuFactory* fab = new MenuFactory();
    Menu* menu;        
    menu=fab->hacerMenu(window->getSize().x, window->getSize().y, 7);
    std::vector<int> punt = gestionPartida->cargarPuntuaciones();
    /**************************************************************MOSTRAR PUNTUACION DISPONIBLE*********************************************************/
    // Load it from a file
    sf::Font font;
    if (!font.loadFromFile("fonts/ZOMBIE.ttf"))
    {
        // error...
    }               
    
    std::vector<sf::Text*> puntuacionesNivel1;
    sf::Text* aux;
    sf::Vector2<int> pos(window->getSize().x/8*2, window->getSize().y/8);
    int ampX=window->getSize().x/8*0.7;
    int ampY=window->getSize().y/6*2;
    
    sf::Text* tex = new sf::Text();
    tex->setFont(font);
    tex->setCharacterSize(60);
    tex->setString("MAXIMAS PUNTUACIONES");
    tex->setPosition(pos.x+ampX*0.75, pos.y*(-1.5)+ampY);
    tex->setColor(sf::Color::Yellow);
    
    sf::Text* niv1 = new sf::Text();
    niv1->setFont(font);
    niv1->setCharacterSize(50);
    niv1->setString("NIVEL 1");
    niv1->setPosition(pos.x+(0.5*ampX), pos.y*(-0.5)+ampY);
    niv1->setColor(sf::Color::Yellow);
    
    sf::Text* niv2 = new sf::Text();
    niv2->setFont(font);
    niv2->setCharacterSize(50);
    niv2->setString("NIVEL 2");
    niv2->setPosition(pos.x*2+(0.5*ampX), pos.y*(-0.5)+ampY);
    niv2->setColor(sf::Color::Yellow);
    
    sf::Text* niv3 = new sf::Text();
    niv3->setFont(font);
    niv3->setCharacterSize(50);
    niv3->setString("NIVEL 3");
    niv3->setPosition(pos.x*3+(0.5*ampX), pos.y*(-0.5)+ampY);
    niv3->setColor(sf::Color::Yellow);
    
    for(int i=0; i<punt.size()/3; i++){
        aux = new sf::Text();
        aux->setFont(font);
        aux->setCharacterSize(45);
        aux->setString(intAString(punt[i]));
        aux->setPosition(pos.x+ampX, pos.y*i+ampY);
        aux->setColor(sf::Color::White);
        puntuacionesNivel1.push_back(aux);
    }    
    std::vector<sf::Text*> puntuacionesNivel2;
    for(int i=0; i<punt.size()/3; i++){
        aux = new sf::Text();
        aux->setFont(font);
        aux->setCharacterSize(45);
        aux->setString(intAString(punt[i+5]));
        aux->setPosition(pos.x*2+ampX, pos.y*i+ampY);
        aux->setColor(sf::Color::White);
        puntuacionesNivel1.push_back(aux);
    }
    std::vector<sf::Text*> puntuacionesNivel3;
    for(int i=0; i<punt.size()/3; i++){
        aux = new sf::Text();
        aux->setFont(font);
        aux->setCharacterSize(45);
        aux->setString(intAString(punt[i+10]));
        aux->setPosition(pos.x*3+ampX, pos.y*i+ampY);
        aux->setColor(sf::Color::White);
        puntuacionesNivel1.push_back(aux);
    }
    
    /**************************************************************BUCLE DE MENU**************************************************************************/
    int estadoMenu = -1;    
    while(estadoMenu!=-12){                              
        if(reloj.getElapsedTime().asMilliseconds()>UPDATE_TIME){
            estadoMenu = menu->update(*window);                                    
            window->clear();            
            menu->draw(*window);
            window->draw(*tex);
            window->draw(*niv1);
            window->draw(*niv2);
            window->draw(*niv3);
            for(int j=0; j<puntuacionesNivel1.size(); j++)
                window->draw(*puntuacionesNivel1[j]);
            for(int k=0; k<puntuacionesNivel1.size(); k++)
                window->draw(*puntuacionesNivel1[k]);
            for(int l=0; l<puntuacionesNivel1.size(); l++)
                window->draw(*puntuacionesNivel1[l]);
            window->display();
            reloj.restart();
            capturarCierre();
         }
    }
    
    delete tex;
    delete niv1;
    //delete niv2;
    //delete niv3;
    /*for(int j=0; j<puntuacionesNivel1.size(); j++)                
        delete puntuacionesNivel1[j];
        
    for(int k=0; k<puntuacionesNivel1.size(); k++)
        delete puntuacionesNivel1[k];
        
    for(int l=0; l<puntuacionesNivel1.size(); l++)
        delete puntuacionesNivel1[l];*/
    
}

bool subirPuntuacion(){
    bool subir=false;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
        subir=true;
    }
    return subir;
}

int Juego::menuMejoras(){
    //1: Menu Inicio ; 2: Menu Pausa ; 3: Menu Fin de nivel ; 4: Menu muerte ; 5: Salir
    sf::Clock reloj;
    reloj.restart();    
    MenuFactory* fab = new MenuFactory();
    Menu* menu;        
    menu=fab->hacerMenu(window->getSize().x, window->getSize().y, 6);
    /**************************************************************MOSTRAR NIVEL DE MEJORAS*********************************************************/
    std::vector<sf::Sprite*> mejoras;        
    sf::Texture tex;
    if (!tex.loadFromFile("resources/HUD.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    //sf::Vector2<int> tam = (sf::Vector2<int>) w.getSize();
    sf::Texture* textura=new sf::Texture(tex);

    sf::Sprite* aux = new sf::Sprite();
    aux->setTexture(*textura);
    std::vector<Arma*> armas = mundo->getProtagonista()->getArmas();
    int nivelMejora=-1;
    for(int i=0; i<4;i++){
        nivelMejora=armas[i]->getMejora();
        aux->setTextureRect(sf::IntRect(0*75*9, (nivelMejora-1)*75/2, 75*8, 75/2));
        aux->setPosition(sf::Vector2f(window->getSize().x/7*4, 250+((i+1)*50)));
        
        mejoras.push_back(new sf::Sprite(*aux));                
    }
    /**************************************************************MOSTRAR PUNTUACION DISPONIBLE*********************************************************/
    // Load it from a file
    sf::Font font;
    if (!font.loadFromFile("fonts/ZOMBIE.ttf"))
    {
        // error...
    }    
    sf::Text* texto = new sf::Text();
    texto->setFont(font);
    texto->setCharacterSize(60);
    texto->setColor(sf::Color::White);
    texto->setPosition(window->getSize().x/10, window->getSize().y/8*0.5);
    texto->setString(intAString(mundo->getPuntuacionNivel()));
    /**************************************************************BUCLE DE MENU**************************************************************************/
    int estadoMenu = -1;
    int armaMejorada=-1;
    int precio = 5000;
    while(estadoMenu!=-12){                              
        if(reloj.getElapsedTime().asMilliseconds()>UPDATE_TIME){
            estadoMenu = menu->update(*window);
            
            switch(estadoMenu){
                case -13: armaMejorada=0;break;
                case -14: armaMejorada=1;break;
                case -15: armaMejorada=2;break;
                case -16: armaMejorada=3;break;
                default: armaMejorada=4;break;
            }            
            
            if(armaMejorada>=0 && armaMejorada<4){//Comprobar que se ha mejorado un arma
                if(armas[armaMejorada]->getMejora()<11 && mundo->getPuntuacionNivel() >= (precio*(armas[armaMejorada]->getMejora()+1))){//Comprobar que el usuario puede pagar
                    mundo->setPuntuacionNivel(-(precio*(armas[armaMejorada]->getMejora()+1)));//Retirar el coste de la puntuacion
                    armas[armaMejorada]->aumentarDanyo();   //Aumentar el danyo
                    armas[armaMejorada]->aumentarMejora();  //Aumentar el nivel de mejora                                                            
                }
            }
            
            //Actualizar la vista de mejora
            for(int i=0; i<4;i++){        
                nivelMejora=armas[i]->getMejora();
                mejoras[i]->setTextureRect(sf::IntRect(0*75*9, (nivelMejora)*75/2, 75*8, 75/2));
                mejoras[i]->setPosition(sf::Vector2f(window->getSize().x/7*4, 250+((i+1)*50)));              
            }   
            if(subirPuntuacion())
                mundo->setPuntuacionNivel(100000);
            //Actualizar puntuacion
            texto->setString(intAString(mundo->getPuntuacionNivel()));
            
            
            window->clear();            
            menu->draw(*window);
            for(int j=0; j<mejoras.size(); j++)
                window->draw(*mejoras[j]);
            window->draw(*texto);
            window->display();
            reloj.restart();
            capturarCierre();
         }
    }
    return estadoMenu;   
}

void Juego::cambiarNivel(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        mundo->cambiarNivel(1, -1);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        mundo->cambiarNivel(2, -1);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        mundo->cambiarNivel(3, -1);
}

bool Juego::capturarCierre()
{
    bool captura=false;
    //Bucle de obtencion de eventos
    sf::Event event;
    while(window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            if(menuSalirDelJuego()==true){
                exit(0);
            }
        }
    }
    return captura;
}

int Juego::ejecutarMenu(int tipo){
    
    //1: Menu Inicio ; 2: Menu Pausa ; 3: Menu Fin de nivel ; 4: Menu muerte ; 5: Salir
    sf::Clock reloj;
    reloj.restart();    
    MenuFactory* fab = new MenuFactory();
    Menu* menu;        
    menu=fab->hacerMenu(window->getSize().x, window->getSize().y, tipo);
    int estadoMenu = -1;
    while(estadoMenu==-1){                              
        if(reloj.getElapsedTime().asMilliseconds()>UPDATE_TIME){
            estadoMenu = menu->update(*window);
            window->clear();
            menu->draw(*window);
            window->display();
            reloj.restart();
            cambiarNivel();
            capturarCierre();
         }
    }
    return estadoMenu;
}
void Juego::reiniciarJuego(int p){
    mundo->reiniciarMundo(p);
}

void Juego::siguienteNivel(int p){
    mundo->siguienteNivel(p);
}

void Juego::repetirNivel(int p){
    mundo->reiniciarNivel(p);
}

int Juego::ejecutarJuego()
{            
    sf::RenderWindow w(sf::VideoMode(1300, 750), "Fight or Die");    
    window=&w;
    mundo = new Mundo(*window);
    bool salir = false; bool salirJuego = false; bool salirMenu = false;
    int estadoMundo = -1;
    int estadoMenu = -1;
    sf::Clock reloj;
    reloj.restart();   
    
   
    
    audios->inicio.play();

    //1: Menu Inicio ; 2: Menu Pausa ; 3: Menu Fin de nivel ; 4: Menu muerte ; 5: Menu ¿Desea Salir?
    //MENU DE INICIO
    while(salir!=true)
    {
        
        estadoMenu = ejecutarMenu(1);    
        if(estadoMenu==-2)
        {            
            if(menuSalirDelJuego())
                exit(0);
        }else if(estadoMenu==-20){
            menuPuntuaciones();
        }
        else if(estadoMenu==-21){
            menuControles();
        }
        else if(estadoMenu==-19 && gestionPartida->cargarPartida().size()<=0){
        
        }else
        {
            if(estadoMenu==-19)
            {//Cargar partida
                mundo->cargarPartida(gestionPartida->cargarPartida(), gestionPartida->cargarPuntuacionSimple());                
            }
            audios->inicio.stop();
            
            while(salirJuego!=true)
            {
                estadoMundo = mundo->ejecutarMundo();   
                
                while(salirMenu!=true)
                {
                    audios->inicio.play();
                    //MENU DE PAUSA-FIN DE NIVEL-MUERTE
                    //CAMBIO DE NIVEL
                    if(estadoMundo==3){
                        gestionPartida->guardarPuntuacion(mundo->getNivel());
                        gestionPartida->guardarPuntuacionSimple(mundo->getNivel());
                        siguienteNivel(mundo->getNivel()->getPuntuacion());
                        gestionPartida->guardarPartida(mundo->getNivel(),mundo->getProtagonista());
                    }
                    
                    if(estadoMundo!=8)
                        estadoMenu = ejecutarMenu(estadoMundo);
                    else{
                        gestionPartida->guardarPuntuacion(mundo->getNivel());
                        estadoMenu = menuFinDelJuego();
                    }
                    //-2: Salir ; -3: Jugar ; -4: Continuar ; -5: Mejoras ; -6: Siguiente nivel ; -7: Reiniciar juego; -8: Opciones ; -9: Volver a inicio      
                    switch(estadoMenu){
                        case -2: if(menuSalirDelJuego()){
                                    salir=true;salirJuego=true;salirMenu=true;
                                 }break; //Salir
                        case -3: /*salir=true;*/break; //Jugar
                        case -4: salirMenu=true; break;            //Continuar
                        case -5: menuMejoras();break;           //Mejoras
                        case -6: salirMenu=true;gestionPartida->guardarPartida(mundo->getNivel(),mundo->getProtagonista());break; //Siguiente nivel                    
                        case -7: salirMenu=true; 
                                 if(mundo->getNivel()->getId()==1)
                                     repetirNivel(0);
                                 else{
                                     mundo->cargarPartida(gestionPartida->cargarPartida(), gestionPartida->cargarPuntuacionSimple());
                                 }
                                 break; //Reiniciar juego 
                        case -8: break; //Opciones
                        case -9: salirMenu=true; salirJuego=true;reiniciarJuego(0);break; //Volver a inicio 
                        case -10: salir=true;salirJuego=true;salirMenu=true; break; //Salir del juego
                        case -11: salirMenu=true; break;                    //No salir
                        case -12: estadoMundo=2; break;                     //Atras
                        case -18: gestionPartida->guardarPartida(mundo->getNivel(),mundo->getProtagonista());estadoMundo=2;estadoMundo=2;  break;//Guardar partida
                    }
                }
                if(estadoMenu!=-9)
                    audios->inicio.stop();
                salirMenu=false;
                
            }
            salirJuego=false;
        }
    }
    return 0;
}

int Juego::menuControles(){
//1: Menu Inicio ; 2: Menu Pausa ; 3: Menu Fin de nivel ; 4: Menu muerte ; 5: Salir
    sf::Clock reloj, relojAux;
    reloj.restart();    
    relojAux.restart();
    MenuFactory* fab = new MenuFactory();
    Menu* menu;        
    menu=fab->hacerMenu(window->getSize().x, window->getSize().y, 7);
    
    sf::Texture tex;
    if (!tex.loadFromFile("resources/controles.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    //sf::Vector2<int> tam = (sf::Vector2<int>) w.getSize();
    sf::Texture* textura=new sf::Texture(tex);
    sf::Sprite* aux = new sf::Sprite();
    aux->setTexture(*textura);
    aux->setPosition(0,0);    
    
    /**************************************************************BUCLE DE MENU**************************************************************************/
    int estadoMenu = -1;    
    while(estadoMenu!=-12){                              
        if(reloj.getElapsedTime().asMilliseconds()>UPDATE_TIME){
            estadoMenu = menu->update(*window);                                    
            window->clear();                        
            window->draw(*aux);
            window->display();
            reloj.restart();
            capturarCierre();
        }
        if(relojAux.getElapsedTime().asMilliseconds()<500)
            estadoMenu=-1;
    }
    
    
    delete aux;
    delete textura;
    
    return estadoMenu;
}