#include "Juego.h"

Juego::Juego() {

}

Juego::Juego(const Juego& orig) {
}

Juego::~Juego() {    
    
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
                if(armas[armaMejorada]->getMejora()<11 && mundo->getPuntuacionNivel() >= (50000*(armas[armaMejorada]->getMejora()+1))){//Comprobar que el usuario puede pagar
                    mundo->setPuntuacionNivel(-(50000*(armas[armaMejorada]->getMejora()+1)));//Retirar el coste de la puntuacion
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
        mundo->cambiarNivel(1);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        mundo->cambiarNivel(2);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        mundo->cambiarNivel(3);
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
void Juego::reiniciarJuego(){
    mundo->reiniciarMundo();
}

void Juego::siguienteNivel(){
    mundo->siguienteNivel();
}

void Juego::repetirNivel(){
    mundo->reiniciarNivel();
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

    //1: Menu Inicio ; 2: Menu Pausa ; 3: Menu Fin de nivel ; 4: Menu muerte ; 5: Menu ¿Desea Salir?            
    //MENU DE INICIO
    while(salir!=true){
        
        estadoMenu = ejecutarMenu(1);    
        if(estadoMenu==-2){
            if(menuSalirDelJuego())
                exit(0);
        }else{
            while(salirJuego!=true){
                estadoMundo = mundo->ejecutarMundo(); 
                while(salirMenu!=true){
                    //MENU DE PAUSA-FIN DE NIVEL-MUERTE
                    estadoMenu = ejecutarMenu(estadoMundo);
                   
                    //-2: Salir ; -3: Jugar ; -4: Continuar ; -5: Mejoras ; -6: Siguiente nivel ; -7: Reiniciar juego; -8: Opciones ; -9: Volver a inicio      
                    switch(estadoMenu){
                        case -2: if(menuSalirDelJuego()){
                                    salir=true;salirJuego=true;salirMenu=true;
                                 }break; //Salir
                        case -3: /*salir=true;*/break; //Jugar
                        case -4: salirMenu=true; break;            //Continuar
                        case -5: menuMejoras();break;           //Mejoras
                        case -6: siguienteNivel(); salirMenu=true;break; //Siguiente nivel                    
                        case -7: salirMenu=true; repetirNivel();break; //Reiniciar juego 
                        case -8: /*salir=true;*/break; //Opciones
                        case -9: salirMenu=true; salirJuego=true;reiniciarJuego();break; //Volver a inicio 
                        case -10: salir=true;salirJuego=true;salirMenu=true; break; //Salir del juego
                        case -11: salirMenu=true; break;                    //No salir
                        case -12: estadoMundo=2; break;                     //Atras
                    }
                }
                salirMenu=false;
            }
            salirJuego=false;
        }
    }
    return 0;
}